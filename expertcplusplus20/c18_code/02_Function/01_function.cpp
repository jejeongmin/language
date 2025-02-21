#include <iostream>
#include <string>
#include <functional>

using namespace std;

void func(int num, const string& str)
{
	cout << "func(" << num << ", " << str << ")" << endl;
}

int main()
{
	// 함수포인터, 함수객체, 람다 표현식을 모두 가르키는 타입을 생성할 수 있다.
	// std::function 을 다형성 함수 래퍼(polymorphic function wrapper)라고 부른다.
	function<void(int, const string&)> f1 = func;

	// 이 경우는 f2는 function warpper 가 아닌 함수 포인터 타입이 된다.
	auto f2 = func;	

	f1(1, "test1");
	f2(2, "test2");
	
	return 0;
}

