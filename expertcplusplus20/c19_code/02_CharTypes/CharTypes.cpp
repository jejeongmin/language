#include <iostream>

using namespace std;

/*
	유니버셜 문자 집합(UCS, Universal Character Set)은 ISO646 이라는 국제 표준이고,
	유니코드도 국제 표준 문자 집합이다.
	둘 다 십만개 이상의 문자를 담고 있으며, 각 문자마다 고유의 이름과 코드 포인트가 정해져있다.
	두 표준에서는 서로 겹치는 문자와 코드 포인트도 있고, 두 표준 모두 인코딩 방식을 따로 두고 있다.

	예를 들어 유니코드는 한 문자를 
	1~4개의 8 bit 로 인코딩하는 UTF-8 방식,
	1~2개의 16 bit 로 인코딩하는 UTF-16 방식,
	1개의 32 bit 로 인코딩하는 UTF-32 방식이 있다.

	using string = basic_string<char>
	using wstring = basic_string<wchar_t>
	using u16string = basic_string<char16_t>
	using u32string = basic_string<char32_t>

	// 유니코드와 세계화를 지원하는 대표적인 라이브러리
	https://github.com/unicode-org/icu
*/
int main()
{
	// u8, L, u, U 은 모두 아래와 같이 일반 스트링 리터럴 접두어인 R 과 조합할 수 있다.
	const char* s1 = u8R"(Raw UTF-8 encoded string literal)";
	const wchar_t* s2 = LR"(Raw wide string literal)";
	const char16_t* s3 = uR"(Raw char16_t string literal)";
	const char32_t* s4 = UR"(Raw char32_t string literal)";

	cout << s1 << endl;
	wcout << s2 << endl;
	// 스트림은 char16_t and char32_t 타입을 지원하지 않으므로 s3과 s4는 스트림에 출력할 수 없다.

	const char* formula = u8"\u03C0 r\u00B2";
	cout << formula << endl;

	return 0;
}
