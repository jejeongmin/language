// 01_01_pipe_client.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <conio.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR *argv[])
{
	HANDLE hPipe;
	TCHAR readDataBuf[BUF_SIZE + 1];
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");

	std::wcout << _T("pipe client starting...") << std::endl;

	while (1)
	{
		hPipe = CreateFile(
			pipeName,						// 파이프 이름
			GENERIC_READ | GENERIC_WRITE,	// 읽기 쓰기 모드 동시 지정
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		int error = GetLastError();
		if (error != ERROR_PIPE_BUSY)
		{
			std::wcout << _T("pipe open fail - error : ") << error << std::endl;
		}

		// 파이프가 꽉 차있을 경우, 더 기다리겠다...
		if (!WaitNamedPipe(pipeName, 20000))
		{
			std::wcout << _T("pipe open fail - WaitNamePipe") << std::endl;
			return -1;
		}
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE; // 메세지 기반으로 모드 변경
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe, // 파이프 핸들
		&pipeMode, // 변경할 모드 정보,
		NULL,
		NULL);

	if (!isSuccess)
	{
		std::wcout << _T("pipe open fail - SetNamedPipeHandleState") << std::endl;
		return -1;
	}

	while (1)
	{
		TCHAR	sendbuf[BUF_SIZE];

		std::wcout << _T("Cmd >");
		std::wcin >> sendbuf;

		if (0 == _tcscmp(sendbuf, _T("bye")))
		{
			std::wcout << _T("press any key to exit ") << sendbuf << std::endl;
			break;
		}

		DWORD bytesWritten = 0;
		DWORD bytesRead = 0;

		isSuccess = WriteFile(
			hPipe,                // 파이프 핸들
			&sendbuf,             // 전송할 메시지 
			(lstrlen(sendbuf) + 1) * sizeof(TCHAR), // 메시지 길이 
			&bytesWritten,             // 전송된 바이트 수
			NULL);

		if (!isSuccess)
		{
			std::wcout << _T("WriteFile failed : ") << sendbuf << std::endl;
			break;
		}

		std::wcout << _T("WriteFile success : ") << sendbuf << std::endl;

		isSuccess = ReadFile(
			hPipe,						// 파이프 핸들
			readDataBuf,				// 데이터 수신할 버퍼
			BUF_SIZE * sizeof(TCHAR),	// 버퍼 사이즈
			&bytesRead,					// 수신한 바이트 수
			NULL);

		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
		{
			std::wcout << _T("ReadFile failed : ") << readDataBuf << std::endl;
			break;
		}

		readDataBuf[bytesRead] = 0;

		std::wcout << _T("ReadFile success : ") << readDataBuf << std::endl;
	}

	CloseHandle(hPipe);

	_getch();

	return 0;
}