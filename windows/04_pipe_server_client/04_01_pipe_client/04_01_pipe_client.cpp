// 04_01_pipe_client.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include "PipeClient.h"
#include <locale.h>
#include <strsafe.h>


int _tmain(int argc, _TCHAR* argv[])
{
	INT    i = 0;
	BYTE   dummy = 1;
	TCHAR  szIn[MAX_PATH] = { 0, };
	DWORD  dwRtnValue = 0;
	LPBYTE pData = NULL;
	size_t dwCbSize = 0;
	CPipeData cOut;

	// 콘솔 한글 출력
	_tsetlocale(LC_ALL, TEXT("korean"));

	for (i = 0; i < 100; i++)
	{
		CPipeClient cPipeClient;

		// Input 파라미터를 계산한다.
		StringCchPrintf(szIn, MAX_PATH, TEXT("TO_SERVER_SEND:call_pid=%d"), ::GetCurrentProcessId());

		// Input 파라미터를 추가하고,
		if (ERROR_SUCCESS != cPipeClient.AddParam(TEXT("foobar"),
			&dummy,
			sizeof(dummy)))
		{
			_tprintf(TEXT("[ERROR] Fail to AddParam\r\n"));
			continue;
		}

		if (ERROR_SUCCESS != cPipeClient.AddParam(TEXT("input_param"),
			(LPBYTE)szIn,
			(_tcslen(szIn) + 1) * sizeof(TCHAR))) // 끝에 \0 추가를 위해 +1함
		{
			_tprintf(TEXT("[ERROR] Fail to AddParam\r\n"));
			continue;
		}

		// 호출하자. 접속 timeout은 5초
		dwRtnValue = cPipeClient.CallService(TEXT("mychannel"), cOut, 5);
		if (ERROR_SUCCESS != dwRtnValue)
		{
			_tprintf(TEXT("[ERROR] Fail to CallService, %d\r\n"), dwRtnValue);
			continue;
		}

		// Server로 부터온 응답을 출력하자.
		// cOut.GetParamPtr(...)으로 값을 구할 수 있다.
		cOut.DUMP();

		if (TRUE == cOut.GetParamPtr(TEXT("hello"), &pData, &dwCbSize))
		{
			_tprintf(TEXT("[RESPONSE] %s\r\n"), (LPCTSTR)pData);
		}

		// 다른 Caller process와 경쟁 테스트를 위해 Sleep
		::Sleep(100);
	}

	return 0;
}

