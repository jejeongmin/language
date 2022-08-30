#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

const size_t kBufferSize = 1024;

/*
	getline 이 호출되면 입력 스트림에서 EOL(EndOfLine) 이 나올 때까지 문자 한 줄을 읽는다.
	EOL 문자는 스트링에 담기지 않는다.
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
