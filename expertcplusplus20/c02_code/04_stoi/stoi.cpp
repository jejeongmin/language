#include <iostream>
#include <string>
#include <cstddef>
#include <charconv>

using namespace std;

int main()
{
	// string to int
	const string toParse = "   123USD";
	size_t index = 0;
	int value = stoi(toParse, &index);
	cout << "Parsed value: " << value << endl;
	cout << "First non-parsed character: '" << toParse[index] << "'" << endl;

	// double to string
	long double d = 3.14L;
	string s = std::to_string(d);
	cout << d << " convert to " << s << endl;

	// low-level converting, c++17
	// �ӵ��� ��û���� �����ٴµ�, ���μ��� Ÿ���� ��κ��� �Ľ̿� ���� ���α׷� �ƴϸ�, ���� �޸�Ʈ�� ���� ��
	std::string out(10, ' ');
	auto [ptr, ec] = to_chars(out.data(), out.data() + out.size(), 12345);
	if(ec == std::errc())
		cout << " convert to " << out << endl;

	return 0;
}