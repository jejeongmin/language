#include <iostream>
#include <string>
#include <functional>

using namespace std;

void func(int num, const string& str)
{
	cout << "func(" << num << ", " << str << ")" << endl;
}

int main()
{
	// �Լ�������, �Լ���ü, ���� ǥ������ ��� ����Ű�� Ÿ���� ������ �� �ִ�.
	// std::function �� ������ �Լ� ����(polymorphic function wrapper)��� �θ���.
	function<void(int, const string&)> f1 = func;

	// �� ���� f2�� function warpper �� �ƴ� �Լ� ������ Ÿ���� �ȴ�.
	auto f2 = func;	

	f1(1, "test1");
	f2(2, "test2");
	
	return 0;
}

