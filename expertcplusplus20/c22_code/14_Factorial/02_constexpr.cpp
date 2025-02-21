#include <iostream>

using namespace std;

constexpr unsigned long long factorial(unsigned char f)
{
	if (f == 0) {
		return 1;
	} else {
		return f * factorial(f - 1);
	}
}

/*
	auto f1 = factorial(6);

	���� constexpr �� ���� ȣ���ϸ�, ������ Ÿ���� �ƴ�, ��Ÿ�ӿ� ���丮���� ����ϰ� �ȴ�.
	������ Ÿ�� ����� �Ϸ��� �ǵ��� �Ϲ� �Լ� ȣ�⿡�� ��� ǥ������ ����ؼ� ȣ���� ����
	�Ǽ��� �� ������ �ִ�.
	ó������ �ƿ� ���ø� ��Ÿ ���α׷����� �ϰ� �Ǹ� �̷� �Ǽ��� �� ������ �ƿ� ����.
*/
int main()
{
	constexpr auto f1 = factorial(6);
	cout << f1 << endl;

	return 0;
}
