#include <iostream>

using namespace std;

constexpr unsigned long long factorial(unsigned char f)
{
	if (f == 0) {
		return 1;
	} else {
		return f * factorial(f - 1);
	}
}

/*
	auto f1 = factorial(6);

	위와 constexpr 을 빼고 호출하면, 컴파일 타임이 아닌, 런타임에 팩토리얼을 계산하게 된다.
	컴파일 타임 계산을 하려는 의도로 일반 함수 호출에서 상수 표현식을 사용해서 호출할 때는
	실수를 할 여지가 있다.
	처음부터 아예 템플릿 메타 프로그래밍을 하게 되면 이런 실수를 할 여지가 아예 없다.
*/
int main()
{
	constexpr auto f1 = factorial(6);
	cout << f1 << endl;

	return 0;
}
