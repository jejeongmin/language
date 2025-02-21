#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>

using namespace std;

void initializeSharedResources()
{
	// ... ���� ���ҽ��� ���� �����尡 ����� �� �ֵ��� �ʱ�ȭ�Ѵ�.

	cout << "Shared resources initialized." << endl;
}

atomic<bool> gInitialized(false);
mutex gMutex;

/*
	���� �˻� �� ����(double-checked locking pattern)�� ��� anti-patter(���� ����)�̶� ������� �ʴ� ���� ����.
	�̰ͺ��ٴ� �⺻ ��, ����򺯼�, call_once, �Լ� ���� static �ν��Ͻ��� Ȱ���ϴ� ���� ����
*/
void processingFunction()
{
	if (!gInitialized) {
		unique_lock lock(gMutex);  // C++17
		//unique_lock<mutex> lock(gMutex);
		if (!gInitialized) {
			initializeSharedResources();
			gInitialized = true;
		}
	}
	cout << "OK" << endl;
}

int main()
{
	vector<thread> threads;

	for (int i = 0; i < 5; ++i) {
		threads.push_back(thread{ processingFunction });
	}

	for (auto& t : threads) {
		t.join();
	}

	return 0;
}
