#include <iostream>

using namespace std;

/*
	현지화에서 가장 중요한 원칙은 소스에서 사용자에게 노출되는 특정 언어로 된 스트링을
	절대로 넣으면 안되다는 것이다.

	c++ 에서는 wchar_t 로 확장 문자를 사용하면 되나, 표준에서 구체적인 크기는 정의하지 않았다.
*/
int main()
{
	// wstring literal 은 L 로 지정한다.
	wcout << L"I am a wide-character string literal." << endl;

	return 0;
}
