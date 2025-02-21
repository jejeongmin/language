#include <tuple>
#include <iostream>

using namespace std;

int add(int a, int b)
{
	return a + b;
}

/*
	템플릿으로 메타 프로그래밍할 때나 유용할 듯, invoke 랑 비슷하네.
*/

int main()
{
	cout << apply(add, std::make_tuple(39, 3)) << endl;

	return 0;
}