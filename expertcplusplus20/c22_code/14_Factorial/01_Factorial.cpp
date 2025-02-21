#include <iostream>

using namespace std;

/*
	템플릿 메타 프로그래밍은 실행 시간이 아닌, 컴파일 시간에 연산을 수행할 목적으로 사용한다.
	기본적으로 C++ 위에 정의된 프로그래밍 언어이다.
*/

template<unsigned char f>
class Factorial
{
public:
	static const unsigned long long val = (f * Factorial<f - 1>::val);
};

template<>
class Factorial<0>
{
public:
	static const unsigned long long val = 1;
};

int main()
{
	cout << Factorial<6>::val << endl;
	return 0;
}
