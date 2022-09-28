#include <algorithm>
#include <iostream>

using namespace std;

/*
	std::swap은 가능하다면 이동 의미론을 적용해서 효율적으로 맞바꾼다.
*/
int main()
{
	int a = 11;
	int b = 22;

	cout << "Before swap(): a = " << a << ", b = " << b << endl;

	swap(a, b);

	cout << "After swap():  a = " << a << ", b = " << b << endl;

	return 0;
}