#pragma once

#include "PipeData.h"

class CPipeClient
{
public:
	CPipeClient(void);
	~CPipeClient(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// Pipe Parameter
	DWORD AddParam(IN LPCTSTR lpszParamName, IN LPBYTE pBuf, IN size_t dwCbSize);

	//////////////////////////////////////////////////////////////////////////
	// Pipe Call
	DWORD CallService(IN LPCTSTR lpszChannelId, OUT CPipeData& cOutPipeData, IN OPTIONAL DWORD dwConnectTimeoutSec);
	BOOL  IsRunning(VOID);

protected:
	DWORD GetChannelName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszChannelName, IN size_t dwCchLength);
	DWORD GetMutexName(IN LPCTSTR lpszChannelId, OUT LPTSTR lpszMutexName, IN size_t dwCchLength);

protected:
	DWORD					m_dwThreadId;
	CPipeData				m_cPipeData;
	PSECURITY_DESCRIPTOR	m_pSD;
	SECURITY_ATTRIBUTES		m_sa;
	PSECURITY_ATTRIBUTES	m_pSA;
	BOOL					m_bRunning;
	CRITICAL_SECTION		m_cs;

protected:
	LPBYTE					m_pSendBuf;
	size_t					m_dwCbSendBuf;
};
