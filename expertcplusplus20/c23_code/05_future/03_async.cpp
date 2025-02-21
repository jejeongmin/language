#include <iostream>
#include <future>

using namespace std;

int calculate()
{
	return 123;
}

/*
	������ �Լ��� async() �� �����ϴ� ����� �� ������.

		- �Լ��� ������� ����� �񵿱�� �����Ѵ�.
		- �����带 ���� ������ �ʰ�, ���ϵ� future �� ���� get() �� ȣ���� �� ��������� �Լ��� �����Ѵ�.

	async() �μ��� ���� ����� �Ʒ� 3���� �� �ϳ��� ����ȴ�.

		- launch::async : �־��� �Լ��� �ٸ� �����忡�� �����Ѵ�.
		- launch::deferred : get()�� ȣ���� �� �־��� �Լ��� ���� ������� ��������� �����Ų��.
		- launch::async | launch::deferred : c++ ��Ÿ���� �����Ѵ�. ���� ���� �������� �� �⺻ ����
*/
int main()
{
	auto myFuture = async(calculate);
	//auto myFuture = async(launch::async, calculate);
	//auto myFuture = async(launch::deferred, calculate);

	// �ʿ��� �۾��� �����Ѵ�.

	// ����� �����´�.
	int result = myFuture.get();
	cout << result << endl;

	return 0;
}
