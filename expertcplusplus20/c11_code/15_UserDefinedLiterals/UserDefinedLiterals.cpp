#include <cstddef>
#include <complex>

/*
	c++ 은 literal 을 직접 정의하는 기능도 제공한다.
	이러한 사용자 정의 literal 은 반드시 _ 로 시작해야 한다.
	그리고 _ 다음에 나오는 글자는 반드시 소문자여야 한다.
*/

// 숫자 값을 처리하려면 타입이 ull, unsigned double, char, wchar_t, char16_t, char32_t 중 하나로 된 매개변수가 필요하다.
// Cooked _i literal
std::complex<long double> operator"" _i(long double d)
{  
	return std::complex<long double>(0, d);  
}

// 로 _i 리터럴
//std::complex<long double> operator"" _i(const char* p)
//{
//    // 구현 코드 생략. C-스타일 스트링을 파싱하고 복소수로 변환해야 한다.
//}


// 스트링을 처리하려면 매개변수가 두 개 있어야 한다. 첫번째는 문자 배열을, 두번째는그 배열의 길이를 지정한다.
// 가공 모드 _s 리터럴
std::string operator"" _s(const char* str, size_t len)
{
	return std::string(str, len);
}

int main()
{
	// 가공 모드 _i 리터럴
	std::complex<long double> c1 = 9.634_i;
	auto c2 = 1.23_i;         // c2 타입은 std::complex<long double>

	// 가공 모드 _s 리터럴
	std::string str1 = "Hello World"_s;
	auto str2 = "Hello World"_s;   // str2의 타입은 std::string
	auto str3 = "Hello World";     // str3의 타입은 const char*;

	return 0;
}
