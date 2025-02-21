#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

const size_t kBufferSize = 1024;

/*
	getline �� ȣ��Ǹ� �Է� ��Ʈ������ EOL(EndOfLine) �� ���� ������ ���� �� ���� �д´�.
	EOL ���ڴ� ��Ʈ���� ����� �ʴ´�.
*/
int main()
{
	char buffer[kBufferSize] = { 0 };
	cin.getline(buffer, kBufferSize);

	cout << "***" << buffer << "***" << endl;

	string myString;
	std::getline(cin, myString);

	cout << "***" << myString << "***" << endl;

	return 0;
}
