#include <iostream>
#include <ratio>

using namespace std;

/*
	...
	using atto = ratio<1, 1'000'000'000'000'000'000>;
	...
	using milli = ratio<1, 1'000>;
	...
	using exa = ratio<1'000'000'000'000'000'000, 1>;
	...

	위와 같이 유리수 표현의 편의를 위해 SI(Systeme International, 국제 단위계) type alias 도 제공한다.
*/
int main()
{
	// 컴파일 시간 유리수 정의
	using r1 = ratio<1, 60>;
	cout << "1) " << r1::num << "/" << r1::den << endl;

	// 분자와 분모 생성
	intmax_t num = r1::num;
	intmax_t den = r1::den;
	cout << "2) " << num << "/" << den << endl;

	// 두 유리수를 더한다.
	using r2 = ratio<1, 30>;
	cout << "3) " << r2::num << "/" << r2::den << endl;
	/*
		ratio_add, ratio_subtract, ratio_muliply, ratio_divide 등 산술용 템플릿들은 계산 결과를 새로운 ratio 타입으로 표현한다.
		이 타입은 c++ 에 정의된 type 이라는 type alias 로 접근한다.
	*/
	using result = ratio_add<r1, r2>::type;
	cout << "4) " << result::num << "/" << result::den << endl;

	// 두 유리수를 비교한다.
	using res = ratio_less<r2, r1>;
	cout << "5) " << boolalpha << res::value << endl;

	return 0;
}
