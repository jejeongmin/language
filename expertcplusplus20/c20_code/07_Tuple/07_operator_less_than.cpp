#include <tuple>
#include <string>
#include <iostream>

using namespace std;

/*
	tuple 에 대한 비교 연산은 튜플 내 정의된 객체들에서 모두 비교 연산을 지원해야 한다.
	Foo 에 대한 비교 연산자 구현이 번거로우면, 아래와 같이 tie 로 묶어서 한번에 처리할 수 있다.
	그러나 각 멤버간 의도된 우선 순위 구현이 필요하다면 번거롭더라도 연산자 구현을 해야 한다.
*/
struct Foo
{
	int mInt;
	string mStr;
	bool mBool;
};

bool operator<(const Foo& f1, const Foo& f2)
{
	return tie(f1.mInt, f1.mStr, f1.mBool) <
		tie(f2.mInt, f2.mStr, f2.mBool);
}

int main()
{
	Foo f1{ 42, "Hello", 0 };
	Foo f2{ 32, "World", 0 };
	cout << (f1 < f2) << endl;
	cout << (f2 < f1) << endl;

	return 0;
}
