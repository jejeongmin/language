#include <iostream>
#include <thread>
#include <future>

using namespace std;

/*
	set_value �� ȣ���� ����� �����ϰų�, set_exception �� ȣ���� �ͼ����� promise�� �����Ѵ�.
	����� Ư�� promise �� ���� set_value �� set_exception �� �� �� ���� ȣ���� �� �ִ�.
	���� �� ȣ���ϸ� std::future_error �ͼ����� �߻��Ѵ�.
*/
void DoWork(promise<int> thePromise)
{
	thePromise.set_value(42);
}

/*
	�������� ���� ����� promise �� ������ future �� �� ���� ������ �� �ִ�.
	ä�ο� �����ϸ� promise �� �Է���Ʈ��, future �� ��� ��Ʈ�� ���̴�.
*/
int main()
{
	// �����忡 ������ promise�� �����Ѵ�.
	promise<int> myPromise;
	// �� promise�� ���� future�� �����´�.
	auto theFuture = myPromise.get_future();
	// �����带 �����ϰ� �տ��� ���� promise�� �μ��� �����Ѵ�. promise �� ������ �� ���� �̵��� �����ϴ�.
	thread theThread{ DoWork, std::move(myPromise) };

	// �ʿ��� �۾��� �����Ѵ�.

	// ����� �����´�.
	int result = theFuture.get();
	cout << "Result: " << result << endl;

	// �����带 �����Ѵ�.
	theThread.join();

	return 0;
}
