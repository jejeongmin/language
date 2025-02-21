#include "pch.h"
#include "PipeServer.h"
#include <atlenc.h>
#include <assert.h>
#include <strsafe.h>

// PIPETRACELOG�� stdafx.h�� ������ ������ Log�� �� �� ����.
#ifndef PIPETRACELOG
#define PIPETRACELOG(...) ((void)(0))
#endif

// ������� stdafx.h��,
/*
#ifndef PIPETRACELOG
#define PIPETRACELOG(...) _tprintf(__VA_ARGS__);_tprintf(TEXT("\r\n"));
#endif
*/
// �� ���� ������ ������, ���� �α׸� �ܼ� stdout�� Ȯ���� �����ϴ�.

// ThreadId�� üũ�Ѵ�.
// Valid���� �ʴ� ��� (Class instance ���� ThreadId�� �ٸ� ���)
// v ������ ���ϰ��� �����, goto FINAL �Ѵ�.
#define CheckValidThreadId_dw(v)	if (m_dwThreadId != ::GetCurrentThreadId()) {dwRtnValue = v;assert(FALSE);goto FINAL;}
#define CheckValidThreadId_bool(v)	if (m_dwThreadId != ::GetCurrentThreadId()) {bRtnValue = v;assert(FALSE);goto FINAL;}

CPipeServer::CPipeServer(void)
{
	m_dwThreadId		 = ::GetCurrentThreadId();
	m_bRunning			 = FALSE;
	m_hPipe				 = INVALID_HANDLE_VALUE;
	m_hRegisterWait		 = NULL;
	m_hMutex			 = NULL;	// pipe�� ����/�Ҹ�/����� lock�� �ɴ�.
	m_pfnOnRequest		 = NULL;
	ZeroMemory(&m_stOverlapConn, sizeof(m_stOverlapConn));
	ZeroMemory(&m_szChannelName, sizeof(m_szChannelName));
	::InitializeCriticalSection(&m_cs);

	m_pSD = NULL;
	m_pSA = NULL;
	ZeroMemory(&m_sa, sizeof(m_sa));

	// Default Security Descriptor�� �����. (m_pSA)
	m_pSD = (PSECURITY_DESCRIPTOR)::LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	::InitializeSecurityDescriptor(m_pSD, SECURITY_DESCRIPTOR_REVISION);
	if (!::SetSecurityDescriptorDacl(m_pSD, TRUE, (PACL)NULL, FALSE))
	{
		PIPETRACELOG(TEXT("[ERROR] Fail to make dsa, %d"), ::GetLastError());
		assert(FALSE);
	}
	else
	{
		m_sa.nLength = sizeof(m_sa);
		m_sa.lpSecurityDescriptor = m_pSD;
		m_sa.bInheritHandle = TRUE;
		m_pSA = &m_sa;
	}
}

CPipeServer::~CPipeServer(void)
{
	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	// Service�� Stop ��Ű��.
	StopService();

	if (NULL != m_pSD)
	{
		::LocalFree((HLOCAL)m_pSD);
		m_pSD = NULL;
		m_pSA = NULL;
	}

	if (NULL != m_hMutex)
	{
		::CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}

	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////

	::DeleteCriticalSection(&m_cs);
}

// non-block���� �����Ѵ�.
// client�� wait-timeout���� �����Ѵ�. 0�� �����ϸ�, 5���� �����Ѵ�. (millisecond)
DWORD CPipeServer::StartService(IN LPCTSTR lpszChannelId, IN PFN_OnRequest pfnOnRequest, OPTIONAL IN LPVOID pContext)
{
	DWORD dwRtnValue			= ERROR_SUCCESS;
	DWORD dwResult				= 0;
	BOOL  bMutexLocked			= FALSE;
	TCHAR szMutexName[MAX_PATH]	= {0,};

	//////////////////////////////////////////////////////////////////////////
	// 
	::EnterCriticalSection(&m_cs);

	// ThreadId üũ
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	if (TRUE == m_bRunning)
	{
		// �̹� Running?
		dwRtnValue = ERROR_SERVICE_ALREADY_RUNNING;
		PIPETRACELOG(TEXT("[ERROR] Fail to Already running"));
		assert(FALSE);
		goto FINAL;
	}

	if (NULL == lpszChannelId)
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		assert(FALSE);
		goto FINAL;
	}

	// Channel �̸��� ������.
	dwRtnValue = GetChannelName(lpszChannelId, m_szChannelName, MAX_PATH);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		PIPETRACELOG(TEXT("[ERROR] Fail to GetChannelName, %d"), dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// ������ ȣ���� ���� �ִ���?
	if ((INVALID_HANDLE_VALUE != m_hPipe) || (NULL != m_stOverlapConn.hEvent) || (NULL != m_pfnOnRequest))
	{
		dwRtnValue = ERROR_ALREADY_EXISTS;
		PIPETRACELOG(TEXT("[ERROR] Fail to Already exists"));
		assert(FALSE);
		goto FINAL;
	}

	if (NULL != m_hMutex)
	{
		dwRtnValue = ERROR_ALREADY_EXISTS;
		PIPETRACELOG(TEXT("[ERROR] Fail to exist last mutex"));
		assert(FALSE);
		goto FINAL;
	}

	// callback �Լ��� �������.
	m_pfnOnRequest = pfnOnRequest;
	m_pContext     = pContext;

	// Mutex �̸��� ������.
	dwRtnValue = GetMutexName(lpszChannelId, szMutexName, MAX_PATH);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		PIPETRACELOG(TEXT("[ERROR] Fail to get mutex name, %d"), dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// Mutex�� ��������.
	m_hMutex = ::CreateMutex(m_pSA, FALSE, szMutexName);
	if (NULL == m_hMutex)
	{
		dwRtnValue = ::GetLastError();
		PIPETRACELOG(TEXT("[ERROR] Fail to create mutex, %d, %s"), dwRtnValue, szMutexName);
		assert(FALSE);
		goto FINAL;
	}

	//////////////////////////////////////////////////////////////////////////
	// LOCK
	dwResult = ::WaitForSingleObject(m_hMutex, INFINITE);
	if ((WAIT_OBJECT_0 == dwResult) || (WAIT_ABANDONED == dwResult))
	{
		bMutexLocked = TRUE;
	}

	// Pipe�� ��������.
	// �ش� pipe�̸����δ� 1���� instance�� �����ϴ�.
	m_hPipe = ::CreateNamedPipe(m_szChannelName,
								PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
								PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
								1,
								4096,
								4096,
								0,
								m_pSA);
	if (NULL == m_hPipe)
	{
		dwRtnValue = ::GetLastError();
		PIPETRACELOG(TEXT("[ERROR] Fail to new pipe, %d, %s"), m_szChannelName, dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// Connect�ɶ� Overlap���� ���Ź��� Event�� �����Ѵ�.
	// �̶� ������ ����, ManualReset�� Off�ؾ� �ϴ� ���̴�. ��, AutoReset�̿��� �Ѵ�.
	// �׷��߸�, RegisterWaitForSingleObject�� callback �Լ���
	// ���~~~~ ȣ����� �ʴ´�.
	m_stOverlapConn.hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == m_stOverlapConn.hEvent)
	{
		dwRtnValue = ::GetLastError();
		PIPETRACELOG(TEXT("[ERROR] Fail to new event, %d"), dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// Connect�� �� Event üũ Callback�� ����Ѵ�.
	// �� �Լ��� Block���� �ʴ´�.
	if (FALSE == ::RegisterWaitForSingleObject(&m_hRegisterWait, 
											   m_stOverlapConn.hEvent, 
											   OnConnectCallback, 
											   this, 
											   INFINITE, 
											   WT_EXECUTEDEFAULT))
	{
		dwRtnValue = ::GetLastError();
		assert(FALSE);
		goto FINAL;
	}

	// Connect�� ��ٸ���.
	// ����, Overlapped ������� ���� non-block�ȴ�.
	if (FALSE == ::ConnectNamedPipe(m_hPipe, &m_stOverlapConn))
	{
		dwRtnValue = ::GetLastError();
		if ((ERROR_IO_PENDING		== dwRtnValue) ||
			(ERROR_PIPE_CONNECTED	== dwRtnValue))
		{
			// good
		}
		else
		{
			PIPETRACELOG(TEXT("[ERROR] Fail to conn pipe, %d, %s"), dwRtnValue, m_szChannelName);
			assert(FALSE);
			goto FINAL;
		}
	}

	// ������� �Դٸ� ����
	dwRtnValue = ERROR_SUCCESS;
	m_bRunning = TRUE;
	PIPETRACELOG(TEXT("[INFO] Success to start service, %s"), m_szChannelName);

FINAL:

	if (TRUE == bMutexLocked)
	{
		::ReleaseMutex(m_hMutex);
		bMutexLocked = FALSE;
	}
	//
	//////////////////////////////////////////////////////////////////////////

	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
	return dwRtnValue;
}

VOID CPipeServer::StopService(VOID)
{
	DWORD   dwRtnValue		= 0;
	HANDLE	hEventFinished  = NULL;

	//////////////////////////////////////////////////////////////////////////
	// 
	::EnterCriticalSection(&m_cs);

	PIPETRACELOG(TEXT("[INFO] Try to finish, %s"), m_szChannelName);

	// ThreadId üũ
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	// �������� �������� ����.
	m_bRunning = FALSE;

	// Callback ���� ����
	m_pfnOnRequest = NULL;
	m_pContext     = NULL;

	if (NULL != m_hRegisterWait)
	{
		hEventFinished = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if (NULL != hEventFinished)
		{
			// ��� callback �Լ��� ����Ǹ� hEventFinished�� trigger�ȴ�.
			PIPETRACELOG(TEXT("[INFO] Try to finish register wait"), m_szChannelName);
			::UnregisterWaitEx(m_hRegisterWait, hEventFinished);
			::WaitForSingleObject(hEventFinished, INFINITE);
			::CloseHandle(hEventFinished);
			PIPETRACELOG(TEXT("[INFI] Finished to finish register wait"));
			hEventFinished  = NULL;
			m_hRegisterWait = NULL;
		}
		else
		{
			::UnregisterWait(m_hRegisterWait);
			m_hRegisterWait = NULL;
		}
	}

	// Pipe�� �ݴ´�.
	if (NULL != m_hMutex)
	{
		::WaitForSingleObject(m_hMutex, INFINITE);
		if (INVALID_HANDLE_VALUE != m_hPipe)
		{
			::CloseHandle(m_hPipe);
			m_hPipe = INVALID_HANDLE_VALUE;
		}
		::ReleaseMutex(m_hMutex);

		::CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}

	if (INVALID_HANDLE_VALUE != m_hPipe)
	{
		::CloseHandle(m_hPipe);
		m_hPipe = INVALID_HANDLE_VALUE;
	}

	if (NULL != m_stOverlapConn.hEvent)
	{
		::CloseHandle(m_stOverlapConn.hEvent);
		ZeroMemory(&m_stOverlapConn, sizeof(m_stOverlapConn));
	}

FINAL:

	PIPETRACELOG(TEXT("[INFO] Finished to finish, %s"), m_szChannelName);
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////

	return;
}

// �� �Լ��� �ٸ��ʿ��� CreateFile(//./pipe/...)�� ȣ��Ǿ��� ��
// ȣ�� �޴´�.
VOID CALLBACK CPipeServer::OnConnectCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	CPipeServer*	pThis				= NULL;
	DWORD			dwRtnValue			= 0;
	LPBYTE			pReadBuf			= NULL;
	BYTE			bufSmall[24]		= {0,};
	DWORD			dwCbReadStreamSize	= 0;
	DWORD			dwCbReaded			= NULL;
	DWORD			dwCbWrite			= 0;
	DWORD			dwResult			= 0;
	BOOL			bMutexLocked		= FALSE;
	LPBYTE			pSendBase64			= NULL;
	size_t			dwCbSendBase64		= 0;
	CPipeData		cParamIn;
	CPipeData		cParamOut;

	pThis = (CPipeServer*)lpParameter;
	if ((NULL == pThis) || (INVALID_HANDLE_VALUE == pThis->m_hPipe) || (NULL == pThis->m_pfnOnRequest))
	{
		// �غ�ȵ�.
		// goto FINAL ���� �ʰ� �ٷ� ������. (LOCK ���� ��ġ�� ����)
		PIPETRACELOG(TEXT("[ERROR] Fail to not ready server"));
		assert(FALSE);
		return;
	}

	if (FALSE == pThis->m_bRunning)
	{
		// �������� �ƴ� ��� exit
		// deadlock �����, CriticalSection �ۿ� �ֵ��� �Ѵ�.
		// ����, CriticalSection �ȿ��� �ִ�.
		PIPETRACELOG(TEXT("[ERROR] not running server, but connected"));
		assert(FALSE);
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&pThis->m_cs);

	// PIPE ������ ����->�����ݹ��Լ�ȣ��->PIPE ������ ����
	// �߰��� ���н� break�Ѵ�.
	// �׷��� ������ Pipe ������ �̷�����.
	// �� do ~ while�� loop�� �ƴ϶�, 1���� ����Ǹ�, �����߻��� break �Ѵ�.
	do
	{
		// PeekNamedPipe(...)�� ���� Read ũ�⸦ ��ť�� �� �� ������,
		// ��쿡���� Block�� ���輺�� �ִٰ� �Ѵ�. (Web MSDN ����)
		// PipeData�� Stream ��ܿ� ���� Field�� �ִµ�, �װ� Ȱ���Ѵ�.
		if (FALSE == ::ReadFile(pThis->m_hPipe, 
								bufSmall, 
								24, 
								&dwCbReaded, 
								NULL))
		{
			dwRtnValue = ::GetLastError();
			if (ERROR_MORE_DATA != dwRtnValue)
			{
				// ���� �߻� !!!
				PIPETRACELOG(TEXT("[ERROR] Fail to read pipe, %d"), dwRtnValue);
				assert(FALSE);
				break;
			}
			else
			{
				// MORE DATA !!!

				if (24 != dwCbReaded)
				{
					dwRtnValue = ERROR_MORE_DATA;
					PIPETRACELOG(TEXT("[ERROR] Fail to mismatch read, %d"), dwCbReaded);
					assert(FALSE);
					break;
				}

				dwCbReadStreamSize = CPipeData::GetSizeBase64Stream(bufSmall, dwCbReaded);
				if (dwCbReadStreamSize <= 24)
				{
					dwRtnValue = ERROR_EMPTY;
					PIPETRACELOG(TEXT("[ERROR] Fail to empty stream"));
					assert(FALSE);
					break;
				}

				pReadBuf = new BYTE[dwCbReadStreamSize];
				if (NULL == pReadBuf)
				{
					dwRtnValue = ERROR_NOT_ENOUGH_MEMORY;
					assert(FALSE);
					break;
				}
				::CopyMemory(pReadBuf, bufSmall, 24);
				if (FALSE == ::ReadFile(pThis->m_hPipe, 
										&pReadBuf[24],
										dwCbReadStreamSize-24, 
										&dwCbReaded, 
										NULL))
				{
					dwRtnValue = ::GetLastError();
					PIPETRACELOG(TEXT("[ERROR] Fail to pipe read, %d"), dwRtnValue);
					assert(FALSE);
					break;
				}
				else
				{
					// ����?
					if (dwCbReaded + 24 != dwCbReadStreamSize)
					{
						// ũ�Ⱑ ���� �ʴ�.
						dwRtnValue = ERROR_MORE_DATA;
						PIPETRACELOG(TEXT("[ERROR] Fail to mismatch read 2nd, %d, %d"), dwCbReaded+24, dwCbReadStreamSize);
						assert(FALSE);
						break;
					}
				}
			}
		}
		else
		{
			// 24byte���� �� ����
			if (dwCbReaded > 24)
			{
				dwRtnValue = ERROR_MORE_DATA;
				assert(FALSE);
				break;
			}

			pReadBuf = new BYTE[dwCbReaded];
			if (NULL == pReadBuf)
			{
				dwRtnValue = ERROR_NOT_ENOUGH_MEMORY;
				assert(FALSE);
				break;
			}
			::CopyMemory(pReadBuf, bufSmall, dwCbReaded);
			dwCbReadStreamSize = dwCbReaded;
		}

		// ������� �Դٸ� Input Parameter �б� ����
		// pReadBuf�� dwCbReadStreamSize��ŭ ���� ���̴�.

		// callback �Լ��� ȣ���ϱ���, Input parameter�� ������.
		if (FALSE == cParamIn.FromBase64(pReadBuf, dwCbReadStreamSize))
		{
			dwRtnValue = ERROR_INVALID_PARAMETER;
			PIPETRACELOG(TEXT("[ERROR] Fail to get param in"));
			assert(FALSE);
			break;
		}

		// callback �Լ��� ȣ������.
		PIPETRACELOG(TEXT("[INFO] Start request, %s"), pThis->m_szChannelName);
		(*(pThis->m_pfnOnRequest))(cParamIn, cParamOut, pThis->m_pContext);
		PIPETRACELOG(TEXT("[INFO] Finished request, %s"), pThis->m_szChannelName);

		// cParamOut ������� ���� �����͸� ������.
		if (FALSE == cParamOut.ToBase64Alloc(&pSendBase64, &dwCbSendBase64))
		{
			dwRtnValue = ERROR_INVALID_PARAMETER;
			PIPETRACELOG(TEXT("[ERROR] Fail to get param out"));
			assert(FALSE);
			break;
		}

		// ���� ��������.
		if (FALSE == ::WriteFile(pThis->m_hPipe, 
								 pSendBase64, 
								 dwCbSendBase64, 
								 &dwCbWrite, 
								 NULL))
		{
			dwRtnValue = ::GetLastError();
			PIPETRACELOG(TEXT("[ERROR] Fail to send pipe, %d"), dwRtnValue);
			assert(FALSE);
			break;
		}
	}
	while (FALSE);	// PIPE ������ ����->�����ݹ��Լ�ȣ��->PIPE ������ ���� ����

	//////////////////////////////////////////////////////////////////////////
	// ���� ���� Pipe connect�� ���� Pipe ��ü�� �ٽ� �����Ѵ�.
	// �̰��� ���� ������, ������ Client���� CreateFile(\\.\pipe\...)�� ȣ���ϸ�,
	// ERROR_PIPE_BUSY�� �߻��Ѵ�.
	// �׷���, Pipe�� �ٽ� �����Ѵ�.
	// ����, ���� ������ Transaction ó�� Server ��: (Disconnect->CloseHandle->CreateNamedPipe->Connect) Client ��: CreateFile
	// �Ǿ�� �ϹǷ� Mutex Lock �ɰ� �Ѵ�.
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//
	dwResult = ::WaitForSingleObject(pThis->m_hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dwResult)
	{
		bMutexLocked = TRUE;
	}
	else if (WAIT_ABANDONED == dwResult)
	{
		bMutexLocked = TRUE;
	}

	// ������ �����Ѵ�.
	::DisconnectNamedPipe(pThis->m_hPipe);
	::CloseHandle(pThis->m_hPipe);

	pThis->m_hPipe = INVALID_HANDLE_VALUE;

	pThis->m_hPipe = ::CreateNamedPipe(pThis->m_szChannelName,
									   PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
									   PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
									   1,
									   4096,
									   4096,
									   NMPWAIT_WAIT_FOREVER,
									   pThis->m_pSA);
	if (INVALID_HANDLE_VALUE == pThis->m_hPipe)
	{
		dwRtnValue = ::GetLastError();
		PIPETRACELOG(TEXT("[ERROR] Fail to new pipe, %s, %d"), pThis->m_szChannelName, dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// Connect�� ��ٸ���.
	// ����, Overlapped ������� ���� non-block�ȴ�.
	if (FALSE == ::ConnectNamedPipe(pThis->m_hPipe, &pThis->m_stOverlapConn))
	{
		dwRtnValue = ::GetLastError();
		if ((ERROR_IO_PENDING		== dwRtnValue) ||
			(ERROR_PIPE_CONNECTED	== dwRtnValue))
		{
			// good
		}
		else
		{
			PIPETRACELOG(TEXT("[ERROR] Fail to conn pipe, %d, %s"), dwRtnValue, pThis->m_szChannelName);
			assert(FALSE);
			goto FINAL;
		}
	}

FINAL:

	if (NULL != pReadBuf)
	{
		delete [] pReadBuf;
		pReadBuf = NULL;
	}

	if (NULL != pSendBase64)
	{
		CPipeData::FreeAlloc(pSendBase64);
		pSendBase64 = NULL;
	}

	if (TRUE == bMutexLocked)
	{
		::ReleaseMutex(pThis->m_hMutex);
		bMutexLocked = FALSE;
	}
	//
	//////////////////////////////////////////////////////////////////////////
	::LeaveCriticalSection(&pThis->m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
}

DWORD CPipeServer::GetMutexName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszMutexName, IN size_t dwCchLength)
{
	DWORD dwRtnValue = ERROR_SUCCESS;

	if ((NULL != lpszMutexName) && (0 > dwCchLength))
	{
		// output clear
		lpszMutexName[0] = TEXT('\0');
	}

	// ThreadId üũ
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	if ((NULL == lpszChannelId)  ||
		(NULL == lpszMutexName)||
		(0    >  dwCchLength))
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		assert(FALSE);
		goto FINAL;
	}

	if ((TEXT('\\') == lpszChannelId[0]) ||
		(TEXT('\0') == lpszChannelId[0]) ||
		(TEXT(' ')  == lpszChannelId[0]))
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		assert(FALSE);
		goto FINAL;
	}

	// �ϴ� channelid�� �׷��� ����.
	StringCchPrintf(lpszMutexName, dwCchLength, TEXT("Global\\%s"), lpszChannelId);

	// ������� �Դٸ� ����
	dwRtnValue = ERROR_SUCCESS;

FINAL:
	return dwRtnValue;
}

DWORD CPipeServer::GetChannelName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszChannelName, IN size_t dwCchLength)
{
	DWORD dwRtnValue = ERROR_SUCCESS;

	if ((NULL != lpszChannelName) && (0 > dwCchLength))
	{
		// output clear
		lpszChannelName[0] = TEXT('\0');
	}

	// ThreadId üũ
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	if ((NULL == lpszChannelId)  ||
		(NULL == lpszChannelName)||
		(0    >  dwCchLength))
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		assert(FALSE);
		goto FINAL;
	}

	if ((TEXT('\\') == lpszChannelId[0]) ||
		(TEXT('\0') == lpszChannelId[0]) ||
		(TEXT(' ')  == lpszChannelId[0]))
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		assert(FALSE);
		goto FINAL;
	}

	// �ϴ� channelid�� �״�� ����.
	StringCchPrintf(lpszChannelName, dwCchLength, TEXT("\\\\.\\pipe\\%s"), lpszChannelId);

	// ������� �Դٸ� ����
	dwRtnValue = ERROR_SUCCESS;

FINAL:
	return dwRtnValue;
}