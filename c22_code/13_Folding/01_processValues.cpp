#include <iostream>
#include <string>
#include <string_view>

using namespace std;

void handleValue(int value) { cout << "Integer: " << value << endl; }
void handleValue(double value) { cout << "Double: " << value << endl; }
void handleValue(string_view value) { cout << "String: " << value << endl; }

/*
	c++17 부터 지원하는 폴딩 표현식, 가변인수 ... 에 대해
	단항 우측, 단항 좌측, 이항 우측, 이항 좌측 폴드 연산을 지원한다.
*/
template<typename... Tn>
void processValues(const Tn&... args)
{
	(handleValue(args), ...);
}

int main()
{
	processValues(1, 2, 3.56, "test", 1.1f);

	return 0;
}