#include <string>

template<typename T>
class SpreadsheetCell
{
public:
	SpreadsheetCell(const T& t) : _Content(t) {}

	const T& getContent() const { return _Content;  }

private:
	T	_Content;
};

// 아래와 같이 템플릿 추론 방식을 사용자가 직접 지정할 수도 있음.
explicit SpreadsheetCell(const char*) -> SpreadsheetCell<std::string>;

int main()
{
	// 가장 예전 방법
	std::pair<int, double> pair1(1, 2.3);
	
	// auto 를 이용해서 선언을 조금 더 간단히
	auto pair2 = std::make_pair(1, 2.3);

	// c++17 부터는 타입 추론을 통해 더 간단히.
	std::pair pair3(1, 2.3);

	std::string	myString = "Hello World!";
	SpreadsheetCell cell1(myString);

	SpreadsheetCell cell2("Hello World!");
}
