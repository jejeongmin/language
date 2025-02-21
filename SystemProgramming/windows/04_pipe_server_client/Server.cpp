// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PipeServer.h"
#include <locale.h>
#include <strsafe.h>

VOID OnRequest(CPipeData& cIn, CPipeData& cOut, LPVOID pContext)
{
	PBYTE  pData    = NULL;
	size_t dwCbData = 0;
	TCHAR  szResponse[MAX_PATH] = {0,};

	_tprintf(TEXT("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\r\n"));

	// _DEBUG�϶� ��µȴ�.
	cIn.DUMP();

	// Input Parameter �м� ����
	if (TRUE == cIn.GetParamPtr(TEXT("input_param"), &pData, &dwCbData))
	{
		// pData�� dwCbData ũ�� ��ŭ ���´�.
		// ����, pData�� ������ �ǵ������ �ȵȴ�.
		//
		// ���⼭�� ������ ��¥!!
		// ���� \0�� ���Ե� ��Ʈ���̴�~!!! ��� �����Ѵ�.
		_tprintf(TEXT("[INPUT] %s\r\n"), pData);
	}

	/*
		LPC ��û�� ó�� �Լ��� �� ���̴�.
	*/

	// ���� �ɸ��� �۾��� ���� ���̴�.
	::Sleep(1000);

	// Response ���� �غ�!
	StringCchPrintf(szResponse, MAX_PATH, TEXT("my resoponse : %d"), ::GetCurrentProcessId());

	// Response Data ���� ����~!!!
	cOut.SetParam(TEXT("hello"), (LPBYTE)szResponse, (_tcslen(szResponse)+1)*sizeof(TCHAR));

	_tprintf(TEXT("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\r\n"));
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD		dwRtnValue	= 0;
	HANDLE		hEvent		= ::CreateEvent(NULL, TRUE, FALSE, TEXT("Global\\stop_evnt"));
	CPipeServer	cPipeServer;

	// �ܼ� �ѱ� ���
	_tsetlocale(LC_ALL, TEXT("korean"));

	// ���񽺸� �����Ѵ�.
	// �ٷ� ���ϵȴ�.
	dwRtnValue = cPipeServer.StartService(TEXT("mychannel"),
										  OnRequest, 
										  (LPVOID)1);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		_tprintf(TEXT("[ERROR] Fail to Start Service, %d"), dwRtnValue);
		goto FINAL;
	}

	// ���� �̺�Ʈ�� ��ٸ���.
	// _kill.bat�� ����Ǹ� �ߴܵȴ�.
	::WaitForSingleObject(hEvent, INFINITE);

FINAL:
	return 0;
}

