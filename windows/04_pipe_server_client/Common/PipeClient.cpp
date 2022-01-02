#include "pch.h"
#include "PipeClient.h"
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

CPipeClient::CPipeClient(void)
{
	m_dwThreadId	= ::GetCurrentThreadId();
	m_pSendBuf		= NULL;

	m_pSD = NULL;
	m_pSA = NULL;
	ZeroMemory(&m_sa, sizeof(m_sa));
	::InitializeCriticalSection(&m_cs);

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

CPipeClient::~CPipeClient(void)
{
	if (NULL != m_pSD)
	{
		::LocalFree((HLOCAL)m_pSD);
		m_pSD = NULL;
		m_pSA = NULL;
	}

	::DeleteCriticalSection(&m_cs);
}

DWORD CPipeClient::AddParam(IN LPCTSTR lpszParamName, IN LPBYTE pBuf, IN size_t dwCbSize)
{
	DWORD dwRtnValue = ERROR_SUCCESS;

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	// ThreadId 체크
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	if (TRUE == IsRunning())
	{
		dwRtnValue = ERROR_NOT_READY;
		assert(FALSE);
		goto FINAL;
	}

	if ((NULL == lpszParamName) || (NULL == pBuf))
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		assert(FALSE);
		goto FINAL;
	}

	if (FALSE == m_cPipeData.SetParam(lpszParamName, pBuf, dwCbSize))
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		PIPETRACELOG(TEXT("[ERROR] Fail to set param, %s, %d"), lpszParamName, dwCbSize);
		assert(FALSE);
		goto FINAL;
	}

	// 여기까지 왔다면 성공
	dwRtnValue = ERROR_SUCCESS;

FINAL:
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
	return dwRtnValue;
}

// connection timeout을 결정한다. (second)
//  ; server가 실행중이지 않을 때에도 실행될 때 가지 기다리는 시간이 포함된다.
//  ; INFINITE를 입력하면 무한대기 시도한다.
DWORD CPipeClient::CallService(IN LPCTSTR lpszChannelId, OUT CPipeData& cOutPipeData, IN OPTIONAL DWORD dwConnectTimeoutSec)
{
	DWORD	dwRtnValue				= ERROR_SUCCESS;
	DWORD	dwMode					= 0;
	DWORD	dwCbReadStreamSize		= 0;
 	DWORD	dwCbReaded				= 0;
	BOOL	bMutexLocked			= FALSE;
	HANDLE	hPipe					= INVALID_HANDLE_VALUE;
	HANDLE	hMutex					= NULL;
	LPBYTE	pReadBuf				= NULL;
	BYTE	bufSmall[24]			= {0,};
	time_t	tStart					= 0;
	TCHAR	szChannelName[MAX_PATH]	= {0,};
	TCHAR	szMutexName[MAX_PATH]	= {0,};

	// 우선 Outdata를 모두 날린다.
	cOutPipeData.ClearAllParam();

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	// ThreadId 체크
	CheckValidThreadId_dw(ERROR_BAD_THREADID_ADDR);

	if (TRUE == m_bRunning)
	{
		dwRtnValue = ERROR_SERVICE_ALREADY_RUNNING;
		PIPETRACELOG(TEXT("[ERROR] Fail to Already calling"));
		assert(FALSE);
		goto FINAL;
	}

	if (NULL != m_pSendBuf)
	{
		dwRtnValue = ERROR_ALREADY_EXISTS;
		PIPETRACELOG(TEXT("[ERROR] Fail to Already calling exists"));
		assert(FALSE);
		goto FINAL;
	}

	if (0 == m_cPipeData.GetCount())
	{
		dwRtnValue = ERROR_EMPTY;
		PIPETRACELOG(TEXT("[ERROR] no data"));
		assert(FALSE);
		goto FINAL;
	}

	if (NULL == lpszChannelId)
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		assert(FALSE);
		goto FINAL;
	}

	dwRtnValue = GetChannelName(lpszChannelId, szChannelName, MAX_PATH);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		PIPETRACELOG(TEXT("[ERROR] Fail to get channel name"));
		assert(FALSE);
		goto FINAL;
	}

	dwRtnValue = GetMutexName(lpszChannelId, szMutexName, MAX_PATH);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		PIPETRACELOG(TEXT("[ERROR] Fail to get mutex name"));
		assert(FALSE);
		goto FINAL;
	}

	// Mutex를 생성한다.
	hMutex = ::CreateMutex(m_pSA, FALSE, szMutexName);
	if (NULL == hMutex)
	{
		dwRtnValue = ::GetLastError();
		PIPETRACELOG(TEXT("[ERROR] Fail to create mutex, %d, %s"), dwRtnValue, szMutexName);
		assert(FALSE);
		goto FINAL;
	}

	// 시작 시각을 측정한다.
	tStart = ::GetTickCount();

	// Pipe connect
	for (;;)
	{
		//////////////////////////////////////////////////////////////////////////
		//
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(hMutex, INFINITE))
		{
			bMutexLocked = TRUE;
		}

		// Pipe를 연결한다.
		// 되도록 아래의 TransactNamedPipe(...)
		// 까지 빨리 호출되도록 한다.
		hPipe = ::CreateFile(szChannelName, 
							 GENERIC_READ | GENERIC_WRITE, 
							 0, 
							 m_pSA, 
							 OPEN_EXISTING, 
							 FILE_ATTRIBUTE_NORMAL, 
							 NULL);
		if (INVALID_HANDLE_VALUE != hPipe)
		{
			// pipe 연결 성공
			break;
		}

		// pipe 연결 실패
		dwRtnValue = ::GetLastError();
		if ((ERROR_PIPE_BUSY == dwRtnValue) ||
			(ERROR_FILE_NOT_FOUND == dwRtnValue))
		{
			// good to retry
		}
		else
		{
			// error
			PIPETRACELOG(TEXT("[ERROR] Fail to conn pipe, %d, %s"), dwRtnValue, szChannelName);
			assert(FALSE);
			goto FINAL;
		}

		if (INFINITE == dwConnectTimeoutSec)
		{
			// 조건 체크 없다. 무한대~
		}
		else
		{
			if (((DOUBLE)(::GetTickCount() - tStart) / 1000) > dwConnectTimeoutSec)
			{
				// timeout
				dwRtnValue = ERROR_TIMEOUT;
				PIPETRACELOG(TEXT("[ERROR] Fail to conn timeout, %d, %s"), dwRtnValue, szChannelName);
				assert(FALSE);
				goto FINAL;
			}
		}

		// 다시 CreateFile을 시도를 위해 Lock을 풀자. (다른 client와 경쟁 발생)
		// 풀어줘야만, Server에서 Lock을 얻어 pipe를 생성할 수 있기 때문이다.
		if (TRUE == bMutexLocked)
		{
			::ReleaseMutex(hMutex);
			bMutexLocked = FALSE;
			//
			//////////////////////////////////////////////////////////////////////////
		}

		// 0.1초 쉬자~ 양보하세요~
		::Sleep(100);
	}

	dwMode = PIPE_READMODE_MESSAGE; 
	::SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);

	// 접속이 완료되고, 그때 Input Parameter 변환을 한다.
	if (FALSE == m_cPipeData.ToBase64Alloc(&m_pSendBuf, &m_dwCbSendBuf))
	{
		// Base64 변환 실패
		dwRtnValue = ERROR_CANNOT_MAKE;
		PIPETRACELOG(TEXT("[ERROR] Fail to param alloc"));
		assert(FALSE);
		goto FINAL;
	}

	// 전송과 수신을 한큐에~~!!! (수신은 우선 쬐끔만~)
 	if (FALSE == ::TransactNamedPipe(hPipe, 
									 m_pSendBuf, 
									 m_dwCbSendBuf, 
									 bufSmall, 
									 24, 
									 &dwCbReaded,
									 NULL))
	{
		dwRtnValue = ::GetLastError();
		if (ERROR_MORE_DATA != dwRtnValue)
		{
			// 진정 실패한 경우,...
			PIPETRACELOG(TEXT("[ERROR] Fail to pipe transact, %d"), dwRtnValue);
			assert(FALSE);
			goto FINAL;
		}
		else
		{
			// MORE DATA !!!

			if (24 != dwCbReaded)
			{
				dwRtnValue = ERROR_MORE_DATA;
				PIPETRACELOG(TEXT("[ERROR] Fail to mismatch read, %d"), dwCbReaded);
				assert(FALSE);
				goto FINAL;
			}

			dwCbReadStreamSize = CPipeData::GetSizeBase64Stream(bufSmall, dwCbReaded);
			if (dwCbReadStreamSize <= 24)
			{
				dwRtnValue = ERROR_EMPTY;
				PIPETRACELOG(TEXT("[ERROR] Fail to empty stream"));
				assert(FALSE);
				goto FINAL;
			}

			pReadBuf = new BYTE[dwCbReadStreamSize];
			if (NULL == pReadBuf)
			{
				dwRtnValue = ERROR_NOT_ENOUGH_MEMORY;
				assert(FALSE);
				goto FINAL;
			}
			::CopyMemory(pReadBuf, bufSmall, 24);
			if (FALSE == ::ReadFile(hPipe, 
									&pReadBuf[24], 
									dwCbReadStreamSize-24, 
									&dwCbReaded, 
									NULL))
			{
				dwRtnValue = ::GetLastError();
				PIPETRACELOG(TEXT("[ERROR] Fail to pipe read, %d"), dwRtnValue);
				assert(FALSE);
				goto FINAL;
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
					goto FINAL;
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
			goto FINAL;
		}

		pReadBuf = new BYTE[dwCbReaded];
		if (NULL == pReadBuf)
		{
			dwRtnValue = ERROR_NOT_ENOUGH_MEMORY;
			assert(FALSE);
			goto FINAL;
		}
		::CopyMemory(pReadBuf, bufSmall, dwCbReaded);
		dwCbReadStreamSize = dwCbReaded;
	}

	// 여기까지 왔다면 성공
	// pReadBuf가 dwCbReadStreamSize 만큼 읽은 것이다.

	// Server의 리턴값을 분석, 전달준비!
	if (FALSE == cOutPipeData.FromBase64(pReadBuf, dwCbReadStreamSize))
	{
		dwRtnValue = ERROR_INVALID_PARAMETER;
		PIPETRACELOG(TEXT("[ERROR] Fail to get param out"));
		assert(FALSE);
		goto FINAL;
	}

	// 여기까지 왔다면 성공
	dwRtnValue = ERROR_SUCCESS;

FINAL:

	if (NULL != m_pSendBuf)
	{
		delete [] m_pSendBuf;
		m_pSendBuf = NULL;
	}

	if (NULL != pReadBuf)
	{
		delete [] pReadBuf;
		pReadBuf = NULL;
	}

	if (INVALID_HANDLE_VALUE != hPipe)
	{
		::CloseHandle(hPipe);
		hPipe = INVALID_HANDLE_VALUE;
	}

	if (TRUE == bMutexLocked)
	{
		::ReleaseMutex(hMutex);
		::CloseHandle(hMutex);
		bMutexLocked = FALSE;
		//
		//////////////////////////////////////////////////////////////////////////
	}

	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////

	return dwRtnValue;
}

BOOL CPipeClient::IsRunning(VOID)
{
	BOOL bRtnValue = FALSE;

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);
	bRtnValue = m_bRunning;
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////

	return bRtnValue;
}

DWORD CPipeClient::GetMutexName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszMutexName, IN size_t dwCchLength)
{
	DWORD dwRtnValue = ERROR_SUCCESS;

	if ((NULL != lpszMutexName) && (0 > dwCchLength))
	{
		// output clear
		lpszMutexName[0] = TEXT('\0');
	}

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

DWORD CPipeClient::GetChannelName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszChannelName, IN size_t dwCchLength)
{
	DWORD dwRtnValue = ERROR_SUCCESS;

	if ((NULL != lpszChannelName) && (0 > dwCchLength))
	{
		// output clear
		lpszChannelName[0] = TEXT('\0');
	}

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