#include <functional>
#include <iostream>
#include <string_view>
#include <string>

using namespace std;

void printMessage(string_view message)
{
	cout << message << endl;
}

/*
	c++17 에 추가된 invoke 의 기능만 보면 그리 유용하지 않아 보일 수 있다.
	그냥 함수나 람다 표현식을 직접 호출해도 되기 때문이다.
	하지만 임의의 호출 가능한 객체를 호출하는 템플릿 코드를 작성할 때는
	굉장히 유용한 순간이 올 수 있다. 알아는 두자.
*/

int main()
{
	invoke(printMessage, "Hello invoke.");
	invoke([](const auto& msg) { cout << msg << endl; }, "Hello invoke.");
	string msg = "Hello invoke.";
	cout << invoke(&string::size, msg) << endl;

	return 0;
}
