#include <functional>
#include <algorithm>
#include <cctype>
#include <string_view>
#include <iostream>

using namespace std;

/*
	펑터로 지정할 때 함수 호출 연산자()는 const 로 지정해야 한다.
	그래야 여러번 호출해도 객체의 내부 상태를 일관성 있게 유지할 수 있다.
*/
class myIsDigit
{
public:
	bool operator()(char c) const { return ::isdigit(c) != 0; }
};

bool isNumber(string_view str)
{
	auto endIter = end(str);
	auto it = find_if(begin(str), endIter, not_fn(myIsDigit()));
	return (it == endIter);
}

int main()
{
	cout << isNumber("12345") << endl;
	cout << isNumber("hello") << endl;
	cout << isNumber("1234a") << endl;

	return 0;
}
