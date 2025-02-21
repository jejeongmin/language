// 03_03_callnamed_pipe_client.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#define BUFSIZE 512

int _tmain(int argc, TCHAR *argv[])
{
	LPCTSTR lpszWrite = TEXT("Default message from client");
	TCHAR chReadBuf[BUFSIZE];
	BOOL fSuccess;
	DWORD cbRead;
	LPCTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");

	if (argc > 1)
	{
		lpszWrite = argv[1];
	}

	fSuccess = CallNamedPipe(
		lpszPipename,        // pipe name 
		const_cast<LPTSTR>(lpszWrite),           // message to server 
		(lstrlen(lpszWrite) + 1) * sizeof(TCHAR), // message length 
		chReadBuf,              // buffer to receive reply 
		BUFSIZE * sizeof(TCHAR),  // size of read buffer 
		&cbRead,                // number of bytes read 
		20000);                 // waits for 20 seconds 

	if (fSuccess || GetLastError() == ERROR_MORE_DATA)
	{
		_tprintf(TEXT("%s\n"), chReadBuf);

		// The pipe is closed; no more data can be read. 

		if (!fSuccess)
		{
			printf("\nExtra data in message was lost\n");
		}
	}

	_getch();

	return 0;
}
