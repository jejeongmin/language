// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PipeClient.h"
#include <locale.h>
#include <strsafe.h>


int _tmain(int argc, _TCHAR* argv[])
{
	INT    i              = 0;
	BYTE   dummy		  = 1;
	TCHAR  szIn[MAX_PATH] = {0,};
	DWORD  dwRtnValue     = 0;
	LPBYTE pData		  = NULL;
	size_t dwCbSize		  = 0;
	CPipeData cOut;

	// �ܼ� �ѱ� ���
	_tsetlocale(LC_ALL, TEXT("korean"));

	for (i=0; i<100; i++)
	{
		CPipeClient cPipeClient;

		// Input �Ķ���͸� ����Ѵ�.
		StringCchPrintf(szIn, MAX_PATH, TEXT("TO_SERVER_SEND:call_pid=%d"), ::GetCurrentProcessId());

		// Input �Ķ���͸� �߰��ϰ�,
		if (ERROR_SUCCESS != cPipeClient.AddParam(TEXT("foobar"), 
												  &dummy, 
												  sizeof(dummy)))
		{
			_tprintf(TEXT("[ERROR] Fail to AddParam\r\n"));
			continue;
		}

		if (ERROR_SUCCESS != cPipeClient.AddParam(TEXT("input_param"),
												  (LPBYTE)szIn,
												  (_tcslen(szIn)+1)*sizeof(TCHAR))) // ���� \0 �߰��� ���� +1��
		{
			_tprintf(TEXT("[ERROR] Fail to AddParam\r\n"));
			continue;
		}

		// ȣ������. ���� timeout�� 5��
		dwRtnValue = cPipeClient.CallService(TEXT("mychannel"), cOut, 5);
		if (ERROR_SUCCESS != dwRtnValue)
		{
			_tprintf(TEXT("[ERROR] Fail to CallService, %d\r\n"), dwRtnValue);
			continue;
		}

		// Server�� ���Ϳ� ������ �������.
		// cOut.GetParamPtr(...)���� ���� ���� �� �ִ�.
		cOut.DUMP();

		if (TRUE == cOut.GetParamPtr(TEXT("hello"), &pData, &dwCbSize))
		{
			_tprintf(TEXT("[RESPONSE] %s\r\n"), (LPCTSTR)pData);
		}

		// �ٸ� Caller process�� ���� �׽�Ʈ�� ���� Sleep
		::Sleep(100);
	}

	return 0;
}

