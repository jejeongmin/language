#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

/*
	타입 트레이트를 이용하면 타입에 따라 분기하는 동작을 컴파일 시간에 처리할 수 있다.
	예를 들어 특정한 타입을 상속하는 타입, 특정한 타입으로 변환할 수 있는 타입, 정수 계열의 타입을 요구하는 템플릿을 작성할 수 있다.
*/

int main()
{
	if (is_integral<int>::value) {
		cout << "int is integral" << endl;
	} else {
		cout << "int is not integral" << endl;
	}

	if (is_class<string>::value) {
		cout << "string is a class" << endl;
	} else {
		cout << "string is not a class" << endl;
	}

	// Using C++17 _v helpers.
	if (is_integral_v<int>) {
		cout << "int is integral" << endl;
	} else {
		cout << "int is not integral" << endl;
	}

	if (is_class_v<string>) {
		cout << "string is a class" << endl;
	} else {
		cout << "string is not a class" << endl;
	}

	return 0;
}
