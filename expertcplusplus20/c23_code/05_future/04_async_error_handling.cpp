#include <iostream>
#include <future>
#include <exception>
#include <stdexcept>

using namespace std;

int calculate()
{
	throw runtime_error("Exception thrown from calculate().");
}

/*
	future �� ���� ū ������ ������ �ͼ����� �ְ� �޴� �� Ȱ���� �� �ִٴ� ���̴�.
	future �� ���� get �� ȣ���ؼ� ���� ����� �����ϰų�, �� future �� ����� promise �� ����� �ͼ����� �ٽ� ���� �� �ִ�.
	package_task �� async() �� ����ϸ� ������ �Լ����� ���� �ͼ����� �ڵ����� promise �� ����ȴ�.
*/

int main()
{
	// ������ �񵿱������ �����ϵ��� launch::async policy�� ����Ѵ�.
	auto myFuture = async(launch::async, calculate);

	// �ʿ��� �۾��� �����Ѵ�.

	// ����� �����´�.
	try {
		int result = myFuture.get();
		cout << result << endl;
	} catch (const exception& ex) {
		cout << "Caught exception: " << ex.what() << endl;
	}

	return 0;
}
