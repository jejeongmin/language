#include <string>
#include <iostream>

using namespace std;

const char* return_const_string_ptr();

int main()
{
	string myString = "hello";

	myString += ", there";

	string myOtherString = myString;

	if (myString == myOtherString) {
		myOtherString[0] = 'H';
	}

	cout << myString << endl;
	cout << myOtherString << endl;

	const char* invalid_ptr = return_const_string_ptr();
	cout << invalid_ptr << endl;

	auto	string1 = "hello world";
	auto	string2 = "hello world"s;

	return 0;
}

/*
	tempstring �� ���� �����ε�, �� ���� ������ ���� const char* �� ��ȯ�ϸ� ȣ���� �ʿ��� ���� ����
	�翬�� �����ϸ� �ȵǴ� ������ ���� �������. �̷� ������ �ڵ� © ���� �幰������, ���� �� �Ⱥ��� �� ������ ����.
*/
const char* return_const_string_ptr()
{
	std::string		tempstring = "valid in return_const_string_ptr()";

	return tempstring.c_str();
}