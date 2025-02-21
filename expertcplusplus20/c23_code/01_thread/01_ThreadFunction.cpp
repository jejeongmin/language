#include <iostream>
#include <thread>

using namespace std;

void counter(int id, int numIterations)
{
	for (int i = 0; i < numIterations; ++i) {
		cout << "Counter " << id << " has value " << i << endl;
	}
}

/*
	������ �Լ��� ������ �μ��� �׻� �� �������� ���� ����ҿ� �����ȴ�.
	�μ��� ���۷����� �����ϰ� �ʹٸ� <functional> �� ���ǵ� std::ref() �� std::cref()�� ����Ѵ�.
*/
int main()
{
	thread t1(counter, 1, 6);
	thread t2(counter, 2, 4);
	t1.join();
	t2.join();

	return 0;
}
