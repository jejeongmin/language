#include <iostream>

using namespace std;

/*
	���� ������ ���ø������� �����Ѵ�.
	�Ϲ� �Լ��� ����Ϸ��� �غô��� �ȵǳ�.

void printValuesTemp(const int&... values)
{
	((cout << values << endl), ...);
}
*/


template<typename... Values>
void printValues(const Values&... values)
{
	((cout << values << endl), ...);
}

int main()
{
	printValues(1, "test", 2.34);

	return 0;
}