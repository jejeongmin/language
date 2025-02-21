#include "stdafx.h"
#include <iostream>

/*
	dll 컴파일 할 때, [공용 언어 런타임 지원] 설정을 활성화한다. /clr
*/

using namespace std;

extern "C"
{
	__declspec(dllexport) int FunctionInDLL(const wchar_t* p)
	{
		wcout << L"The following string was received by C++:\n    '";
		wcout << p << L"'" << endl;
		return 42;    // 값을 리턴한다...
	}
}
