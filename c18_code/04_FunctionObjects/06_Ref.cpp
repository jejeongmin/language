#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

void increment(int& value)
{
	++value;
}

int main()
{
	int index = 0;
	increment(index);

	/*
		bind 하면 index 값이 증가하지 않는다. index의 복제본에 대한 레퍼런스가
		increment 함수의 첫 번째 매개변수로 바인딩 되기 때문이다.
	*/
	auto incr1 = bind(increment, index);
	incr1();

	/*
		std::ref 로 레퍼런스로 제대로 지정하면 index 값이 증가한다.
	*/
	auto incr2 = bind(increment, ref(index));
	incr2();

	return 0;
}
