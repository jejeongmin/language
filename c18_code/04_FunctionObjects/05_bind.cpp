#include <iostream>
#include <string>
#include <string_view>
#include <functional>

using namespace std;

void func(int num, string_view str)
{
	cout << "func(" << num << ", " << str << ")" << endl;
}

int main()
{
	// 두 번째 인수를 고정된 값에 바인딩한다.
	string myString = "abc";
	auto f1 = bind(func, placeholders::_1, myString);
	f1(16);		// placeholders::_1 를 가변인자로 했고, 두번째 인자는 위에서 값을 고정했다.

	// 인수의 순서를 바꾼다.
	auto f2 = bind(func, placeholders::_2, placeholders::_1);
	f2("Test", 32);
	
	return 0;
}

