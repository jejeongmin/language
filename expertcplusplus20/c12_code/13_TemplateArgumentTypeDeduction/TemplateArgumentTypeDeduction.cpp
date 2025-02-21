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

// �Ʒ��� ���� ���ø� �߷� ����� ����ڰ� ���� ������ ���� ����.
explicit SpreadsheetCell(const char*) -> SpreadsheetCell<std::string>;

int main()
{
	// ���� ���� ���
	std::pair<int, double> pair1(1, 2.3);
	
	// auto �� �̿��ؼ� ������ ���� �� ������
	auto pair2 = std::make_pair(1, 2.3);

	// c++17 ���ʹ� Ÿ�� �߷��� ���� �� ������.
	std::pair pair3(1, 2.3);

	std::string	myString = "Hello World!";
	SpreadsheetCell cell1(myString);

	SpreadsheetCell cell2("Hello World!");
}
