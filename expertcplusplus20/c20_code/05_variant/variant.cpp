#include <variant>
#include <string>
#include <iostream>

using namespace std;

/*
	visitor pattern
	https://brownbears.tistory.com/575
	https://thecodinglog.github.io/design/2019/10/29/visitor-pattern.html
	https://johngrib.github.io/wiki/pattern/visitor/
	https://johngrib.github.io/wiki/pattern/visitor/
*/

class MyVisitor
{
public:
	void operator()(int i) { cout << "int " << i << endl; }
	void operator()(const string& s) { cout << "string " << s << endl; }
	void operator()(float f) { cout << "float " << f << endl; }
};

int main()
{
	variant<int, string, float> v;
	v = 12;
	v = 12.5f;
	v = "An std::string"s;

	cout << "Type index: " << v.index() << endl;
	cout << "Contains an int: " << holds_alternative<int>(v) << endl;	// variant 가 인수로 지정한 타입의 값을 담고 있는지 확인할 수 있다.

	cout << std::get<string>(v) << endl;
	try {
		cout << std::get<0>(v) << endl;
	} catch (const bad_variant_access& ex) {
		cout << "Exception: " << ex.what() << endl;
	}

	string* theString = std::get_if<string>(&v);
	int* theInt = std::get_if<int>(&v);
	cout << "retrieved string: " << (theString ? *theString : "null") << endl;
	cout << "retrieved int: " << (theInt ? *theInt : 0) << endl;

	// variant 에 대한 비지터 패턴을 적용할 때 사용한다. 함수 호출 연산자가 다양한 버전으로 오버로딩되어 있을 때 각 타입을 variant 로 표현할 수 있다.
	std::visit(MyVisitor(), v);

	return 0;
}
