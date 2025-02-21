// 01_00_pipe_server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <namedpipeapi.h>
#include <conio.h>

#define BUF_SIZE 1024

int CommToClient(HANDLE hPipe)
{
	while (1)
	{
		TCHAR recvBuf[BUF_SIZE];
		DWORD recvBufSize;
		DWORD bytesWritten = 0;

		BOOL isSuccess = ReadFile(
			hPipe,						// 파이프 핸들
			recvBuf,					// read 버퍼 지정
			MAX_PATH * sizeof(TCHAR),	// READ 버퍼 사이즈
			&recvBufSize,				// 수신한 데이터 크기
			NULL);

		if (!isSuccess || recvBufSize == 0)
		{
			std::wcout << _T("pipe read message error") << std::endl;
			break;
		}

		std::wcout << recvBuf << std::endl;

		if (0 == _tcscmp(recvBuf, _T("disconnect")))
		{
			std::wcout << _T("current client shutdown") << std::endl;
			break;
		}

		WriteFile(
			hPipe,			// 파이프 핸들
			recvBuf,		// 전송할 데이터 버퍼
			recvBufSize,	// 전송할 데이터 크기
			&bytesWritten,	// 전송된 데이터 크기
			NULL
		);

		if (recvBufSize != bytesWritten)
		{
			std::wcout << _T("send uncomplete") << std::endl;
			break;
		}
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 1;
}

int _tmain(int argc, TCHAR* argv[])
{
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	std::wcout << _T("pipe server starting...") << std::endl;

	while (1)
	{
		hPipe = CreateNamedPipe(
			pipeName,					// 파이프 이름
			PIPE_ACCESS_DUPLEX,			// 읽기, 쓰기 모드 지정
			PIPE_TYPE_MESSAGE |
			PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,	// 최대 인스턴스 개수
			BUF_SIZE,					// 출력 버퍼 사이즈
			BUF_SIZE,					// 입력 버퍼 사이즈
			20000,						// 클라이언트 타임-아웃, 설정된 pipe 개수가 꽉차서 더 연결을 할 수 없는 경우
			NULL						// 디폴트 보안 속성
		);								// <- 파이프 한개를 여러 파이프 클라이언트가 다중화해서 쓰려면 CreateNamedPipe 코드가 루프 바깥으로 나가 있어야 하지 않나? 2021.12.30

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			std::wcout << _T("CreatePipeFailed") << std::endl;
			return -1;
		}

		std::wcout << _T("create pipe success") << std::endl;

		BOOL isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess)
		{
			std::wcout << _T("connecting client...") << std::endl;
			CommToClient(hPipe);
		}
		else
		{
			std::wcout << _T("closing connected client...") << std::endl;
			CloseHandle(hPipe);
		}
	}

	_getch();

	return 1;
}