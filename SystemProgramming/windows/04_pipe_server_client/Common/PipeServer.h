#pragma once

//////////////////////////////////////////////////////////////////////////
//
// Asyncronous PIPE IPC(LPC) Server
//
// - �� class instance�� thread�� ������ �����Ѵ�.
//   ��, ������ Thread���� public method�Լ��� ȣ���ؾ� �Ѵ�.
//	 �����Ǵ� ���, ERROR_BAD_THREADID_ADDR�� ���ϵȴ�.
//	 �̴� �ִ��� caller���� �߻��� �ִ� ����ȭ ���׸� �����ϱ� ���� ��������̴�.
//	 (����, �� class�� process�� thread-safe�� ����ȴ�)
//
// - StartService�� non-block �Լ��̴�.
//	 ���� ���� �Ⱓ�� Class instance�� life-time�� �ȴ�.
//	 ����, StopService ȣ��ε� �����ϴ�.
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
