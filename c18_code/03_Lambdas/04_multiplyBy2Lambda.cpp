#include <iostream>
#include <functional>

using namespace std;

function<int(void)> multiplyBy2Lambda(int x)
{
	return [x]{ return 2 * x; };
}

// 함수 리턴 타입 추론을 적용할 경우
auto multiplyBy2LambdaAuto(int x)
{
	return [x]{ return 2 * x; };
}

int main()
{
	function<int(void)> fn1 = multiplyBy2Lambda(5);
	cout << fn1() << endl;

	auto fn2 = multiplyBy2Lambda(5);
	cout << fn2() << endl;

	auto fn3 = multiplyBy2LambdaAuto(5);
	cout << fn3() << endl;

	return 0;
}