#pragma once

//////////////////////////////////////////////////////////////////////////
//
// Asyncronous PIPE IPC(LPC) Server
//
// - 본 class instance의 thread간 공유를 금지한다.
//   즉, 생성한 Thread에서 public method함수를 호출해야 한다.
//	 공유되는 경우, ERROR_BAD_THREADID_ADDR가 리턴된다.
//	 이는 최대한 caller에서 발생될 있는 동기화 버그를 제거하기 위한 제약사항이다.
//	 (물론, 본 class는 process간 thread-safe가 보장된다)
//
// - StartService는 non-block 함수이다.
//	 서비스 유지 기간은 Class instance의 life-time이 된다.
//	 물론, StopService 호출로도 가능하다.
//
//////////////////////////////////////////////////////////////////////////

#include "PipeData.h"

class CPipeServer
{
public:
	CPipeServer(void);
	~CPipeServer(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// callback function prototype
	typedef VOID (__cdecl *PFN_OnRequest)(IN CPipeData& cInPipeData, OUT CPipeData& cOutPipeData, IN LPVOID pContext);

public:
	//////////////////////////////////////////////////////////////////////////
	// Server Main Operation
	DWORD StartService(IN LPCTSTR lpszChannelId, IN PFN_OnRequest pfnOnRequest, OPTIONAL IN LPVOID pContext);
	VOID  StopService(VOID);

protected:
	//////////////////////////////////////////////////////////////////////////
	// OnConnected Server side Callback
	static VOID CALLBACK OnConnectCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired);

protected:
	//////////////////////////////////////////////////////////////////////////
	// Name Operation
	DWORD GetChannelName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszChannelName, IN size_t dwCchLength);
	DWORD GetMutexName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszMutexName, IN size_t dwCchLength);

protected:
	DWORD					m_dwThreadId;
	BOOL					m_bRunning;
	HANDLE					m_hRegisterWait;
	PSECURITY_DESCRIPTOR	m_pSD;
	SECURITY_ATTRIBUTES		m_sa;
	PFN_OnRequest			m_pfnOnRequest;

protected:
	//////////////////////////////////////////////////////////////////////////
	// Sharing Context with OnConnectCallback
	CRITICAL_SECTION		m_cs;
	HANDLE					m_hPipe;
	HANDLE					m_hMutex;
	PSECURITY_ATTRIBUTES	m_pSA;
	OVERLAPPED				m_stOverlapConn;
	LPVOID					m_pContext;
	TCHAR					m_szChannelName[MAX_PATH];
};
