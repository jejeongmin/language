// 02_00_unnamed_pipe.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain(int argc, LPTSTR argv[])
{
	HANDLE hReadPipe, hWritePipe; //pipe handle
	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];
	DWORD bytesWritten;
	DWORD bytesRead;

	/* pipe 생성 */
	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);

	/* 이름없는 파이프는 단방향성이기에 함수를 호출하면 파이프의 쓰는 부분과 읽는 부분을 반환받는다. */
	/* pipe의 한쪽 끝을 이용한 데이터 송신 */
	WriteFile(hWritePipe, sendString, lstrlen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);

	_tprintf(_T("string send: %s \n"), sendString);


	/* pipe의 다른 한쪽 끝을 이용한 데이터 수신 */
	ReadFile(hReadPipe, recvString, bytesWritten, &bytesRead, NULL);
	recvString[bytesRead / sizeof(TCHAR)] = 0;

	_tprintf(_T("string recv: %s \n"), recvString);

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);

	return 0;
}