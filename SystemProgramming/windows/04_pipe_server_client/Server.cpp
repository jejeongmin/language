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

	// _DEBUG일때 출력된다.
	cIn.DUMP();

	// Input Parameter 분석 가능
	if (TRUE == cIn.GetParamPtr(TEXT("input_param"), &pData, &dwCbData))
	{
		// pData가 dwCbData 크기 만큼 들어온다.
		// 물론, pData의 내용을 건드려서는 안된다.
		//
		// 여기서는 문장을 찍짜!!
		// 끝에 \0이 포함된 스트링이다~!!! 라고 가정한다.
		_tprintf(TEXT("[INPUT] %s\r\n"), pData);
	}

	/*
		LPC 요청의 처리 함수가 들어갈 것이다.
	*/

	// 오래 걸리는 작업이 있을 것이다.
	::Sleep(1000);

	// Response 전달 준비!
	StringCchPrintf(szResponse, MAX_PATH, TEXT("my resoponse : %d"), ::GetCurrentProcessId());

	// Response Data 전달 세팅~!!!
	cOut.SetParam(TEXT("hello"), (LPBYTE)szResponse, (_tcslen(szResponse)+1)*sizeof(TCHAR));

	_tprintf(TEXT("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\r\n"));
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD		dwRtnValue	= 0;
	HANDLE		hEvent		= ::CreateEvent(NULL, TRUE, FALSE, TEXT("Global\\stop_evnt"));
	CPipeServer	cPipeServer;

	// 콘솔 한글 출력
	_tsetlocale(LC_ALL, TEXT("korean"));

	// 서비스를 시작한다.
	// 바로 리턴된다.
	dwRtnValue = cPipeServer.StartService(TEXT("mychannel"),
										  OnRequest, 
										  (LPVOID)1);
	if (ERROR_SUCCESS != dwRtnValue)
	{
		_tprintf(TEXT("[ERROR] Fail to Start Service, %d"), dwRtnValue);
		goto FINAL;
	}

	// 종료 이벤트를 기다리자.
	// _kill.bat가 실행되면 중단된다.
	::WaitForSingleObject(hEvent, INFINITE);

FINAL:
	return 0;
}

