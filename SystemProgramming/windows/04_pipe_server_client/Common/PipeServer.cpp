#include "pch.h"
#include "PipeServer.h"
#include <atlenc.h>
#include <assert.h>
#include <strsafe.h>

// PIPETRACELOG를 stdafx.h에 정의해 놓으면 Log를 볼 수 있음.
#ifndef PIPETRACELOG
#define PIPETRACELOG(...) ((void)(0))
#endif

// 예를들어 stdafx.h에,
/*
#ifndef PIPETRACELOG
#define PIPETRACELOG(...) _tprintf(__VA_ARGS__);_tprintf(TEXT("\r\n"));
#endif
*/
// 와 같이 정의해 놓으면, 관련 로그를 콘솔 stdout로 확인이 가능하다.

// ThreadId를 체크한다.
// Valid하지 않는 경우 (Class instance 생성 ThreadId와 다른 경우)
// v 값으로 리턴값을 만들고, goto FINAL 한다.
#define CheckValidThreadId_dw(v)	if (m_dwThreadId != ::GetCurrentThreadId()) {dwRtnValue = v;assert(FALSE);goto FINAL;}
#define CheckValidThreadId_bool(v)	if (m_dwThreadId != ::GetCurrentThreadId()) {bRtnValue = v;assert(FALSE);goto FINAL;}

CPipeServer::CPipeServer(void)
{
	m_dwThreadId		 = ::GetCurrentThreadId();
	m_bRunning			 = FALSE;
	m_hPipe				 = INVALID_HANDLE_VALUE;
	m_hRegisterWait		 = NULL;
	m_hMutex			 = NULL;	// pipe의 생성/소멸/연결시 lock을 걸다.
	m_pfnOnRequest		 = NULL;
	ZeroMemory(&m_stOverlapConn, sizeof(m_stOverlapConn));
	ZeroMemory(&m_szChannelName, sizeof(m_szChannelName));
	::InitializeCriticalSection(&m_cs);

	m_pSD = NULL;
	m_pSA = NULL;
	ZeroMemory(&m_sa, sizeof(m_sa));

	// Default Security Descriptor를 만든다. (m_pSA)
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

	// Service를 Stop 시키자.
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

// non-block으로 동작한다.
// client의 wait-timeout값을 지정한다. 0을 전달하면, 5분을 전달한다. (millisecond)
DWORD CPipeServer::StartService(IN LPCTSTR lpszChannelId, IN PFN_OnRequest pfnOnRequest, OPTIONAL IN LPVOID pContext)
{
	DWORD dwRtnValue			= ERROR_SUCCESS;
	DWORD dwResult				= 0;
	BOOL  bMutexLocked			= FALSE;
	TCHAR szMutexName[MAX_PATH]	= {0,};

	//////////////////////////////////////////////////////////////////////////
	// 
	::EnterCriticalSection(&m_cs);

	// ThreadId 체크
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	if (TRUE == m_bRunning)
	{
		// 이미 Running?
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

	// Channel 이름을 구하자.
	dwRtnValue = GetChannelName(lpszChannelId, m_szChannelName, MAX_PATH);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		PIPETRACELOG(TEXT("[ERROR] Fail to GetChannelName, %d"), dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// 이전의 호출이 남아 있느냐?
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

	// callback 함수를 등록하자.
	m_pfnOnRequest = pfnOnRequest;
	m_pContext     = pContext;

	// Mutex 이름을 구하자.
	dwRtnValue = GetMutexName(lpszChannelId, szMutexName, MAX_PATH);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		PIPETRACELOG(TEXT("[ERROR] Fail to get mutex name, %d"), dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// Mutex를 생성하자.
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

	// Pipe를 생성하자.
	// 해당 pipe이름으로는 1개의 instance만 가능하다.
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

	// Connect될때 Overlap으로 수신받을 Event를 생성한다.
	// 이때 주의할 것은, ManualReset을 Off해야 하는 것이다. 즉, AutoReset이여야 한다.
	// 그래야만, RegisterWaitForSingleObject의 callback 함수가
	// 계속~~~~ 호출되지 않는다.
	m_stOverlapConn.hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == m_stOverlapConn.hEvent)
	{
		dwRtnValue = ::GetLastError();
		PIPETRACELOG(TEXT("[ERROR] Fail to new event, %d"), dwRtnValue);
		assert(FALSE);
		goto FINAL;
	}

	// Connect될 때 Event 체크 Callback을 등록한다.
	// 본 함수는 Block되지 않는다.
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

	// Connect를 기다린다.
	// 물론, Overlapped 사용으로 인해 non-block된다.
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

	// 여기까지 왔다면 성공
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

	// ThreadId 체크
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	// 이제부터 동작하지 않음.
	m_bRunning = FALSE;

	// Callback 하지 않음
	m_pfnOnRequest = NULL;
	m_pContext     = NULL;

	if (NULL != m_hRegisterWait)
	{
		hEventFinished = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if (NULL != hEventFinished)
		{
			// 모든 callback 함수가 종료되면 hEventFinished가 trigger된다.
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

	// Pipe를 닫는다.
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

// 본 함수는 다른쪽에서 CreateFile(//./pipe/...)가 호출되었을 때
// 호출 받는다.
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
		// 준비안됨.
		// goto FINAL 하지 않고 바로 나간다. (LOCK 과정 거치지 않음)
		PIPETRACELOG(TEXT("[ERROR] Fail to not ready server"));
		assert(FALSE);
		return;
	}

	if (FALSE == pThis->m_bRunning)
	{
		// 동작중이 아닌 경우 exit
		// deadlock 우려로, CriticalSection 밖에 넣도록 한다.
		// 물론, CriticalSection 안에도 있다.
		PIPETRACELOG(TEXT("[ERROR] not running server, but connected"));
		assert(FALSE);
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&pThis->m_cs);

	// PIPE 데이터 수신->서버콜백함수호출->PIPE 데이터 전송
	// 중간에 실패시 break한다.
	// 그래야 다음번 Pipe 연결이 이뤄진다.
	// 본 do ~ while은 loop가 아니라, 1번만 실행되며, 오류발생시 break 한다.
	do
	{
		// PeekNamedPipe(...)를 통해 Read 크기를 한큐에 알 수 있지만,
		// 경우에따라 Block의 위험성이 있다고 한다. (Web MSDN 참고)
		// PipeData의 Stream 상단에 길이 Field가 있는데, 그걸 활용한다.
		if (FALSE == ::ReadFile(pThis->m_hPipe, 
								bufSmall, 
								24, 
								&dwCbReaded, 
								NULL))
		{
			dwRtnValue = ::GetLastError();
			if (ERROR_MORE_DATA != dwRtnValue)
			{
				// 오류 발생 !!!
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
					// 성공?
					if (dwCbReaded + 24 != dwCbReadStreamSize)
					{
						// 크기가 맞지 않다.
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
			// 24byte만에 다 끝남
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

		// 여기까지 왔다면 Input Parameter 읽기 성공
		// pReadBuf가 dwCbReadStreamSize만큼 읽은 것이다.

		// callback 함수를 호출하기전, Input parameter를 구하자.
		if (FALSE == cParamIn.FromBase64(pReadBuf, dwCbReadStreamSize))
		{
			dwRtnValue = ERROR_INVALID_PARAMETER;
			PIPETRACELOG(TEXT("[ERROR] Fail to get param in"));
			assert(FALSE);
			break;
		}

		// callback 함수를 호출하자.
		PIPETRACELOG(TEXT("[INFO] Start request, %s"), pThis->m_szChannelName);
		(*(pThis->m_pfnOnRequest))(cParamIn, cParamOut, pThis->m_pContext);
		PIPETRACELOG(TEXT("[INFO] Finished request, %s"), pThis->m_szChannelName);

		// cParamOut 기반으로 전송 데이터를 만들자.
		if (FALSE == cParamOut.ToBase64Alloc(&pSendBase64, &dwCbSendBase64))
		{
			dwRtnValue = ERROR_INVALID_PARAMETER;
			PIPETRACELOG(TEXT("[ERROR] Fail to get param out"));
			assert(FALSE);
			break;
		}

		// 이제 전송하자.
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
	while (FALSE);	// PIPE 데이터 수신->서버콜백함수호출->PIPE 데이터 전송 종료

	//////////////////////////////////////////////////////////////////////////
	// 이제 다음 Pipe connect를 위해 Pipe 객체를 다시 생성한다.
	// 이것을 하지 않으면, 다음번 Client에서 CreateFile(\\.\pipe\...)를 호출하면,
	// ERROR_PIPE_BUSY가 발생한다.
	// 그래서, Pipe를 다시 생성한다.
	// 물론, 생성 과정은 Transaction 처리 Server 측: (Disconnect->CloseHandle->CreateNamedPipe->Connect) Client 측: CreateFile
	// 되어야 하므로 Mutex Lock 걸고 한다.
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

	// 연결을 종료한다.
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

	// Connect를 기다린다.
	// 물론, Overlapped 사용으로 인해 non-block된다.
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

	// ThreadId 체크
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

	// 일단 channelid를 그래로 쓴다.
	StringCchPrintf(lpszMutexName, dwCchLength, TEXT("Global\\%s"), lpszChannelId);

	// 여기까지 왔다면 성공
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

	// ThreadId 체크
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

	// 일단 channelid를 그대로 쓴다.
	StringCchPrintf(lpszChannelName, dwCchLength, TEXT("\\\\.\\pipe\\%s"), lpszChannelId);

	// 여기까지 왔다면 성공
	dwRtnValue = ERROR_SUCCESS;

FINAL:
	return dwRtnValue;
}