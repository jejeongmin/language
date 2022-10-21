#include <iostream>

using namespace std;

/*
	폴딩 연산은 템플릿에서만 지원한다.
	일반 함수로 사용하려고 해봤더니 안되네.

void printValuesTemp(const int&... values)
{
	((cout << values << endl), ...);
}
*/


template<typename... Values>
void printValues(const Values&... values)
{
	((cout << values << endl), ...);
}

int main()
{
	printValues(1, "test", 2.34);

	return 0;
}