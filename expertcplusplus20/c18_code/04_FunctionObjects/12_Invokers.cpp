#include <functional>
#include <iostream>
#include <string_view>
#include <string>

using namespace std;

void printMessage(string_view message)
{
	cout << message << endl;
}

/*
	c++17 �� �߰��� invoke �� ��ɸ� ���� �׸� �������� �ʾ� ���� �� �ִ�.
	�׳� �Լ��� ���� ǥ������ ���� ȣ���ص� �Ǳ� �����̴�.
	������ ������ ȣ�� ������ ��ü�� ȣ���ϴ� ���ø� �ڵ带 �ۼ��� ����
	������ ������ ������ �� �� �ִ�. �˾ƴ� ����.
*/

int main()
{
	invoke(printMessage, "Hello invoke.");
	invoke([](const auto& msg) { cout << msg << endl; }, "Hello invoke.");
	string msg = "Hello invoke.";
	cout << invoke(&string::size, msg) << endl;

	return 0;
}
