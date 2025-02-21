#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>

using namespace std;

void increment(atomic<int>& counter)
{
	// ++counter ������ �����ϸ鼭 �ʿ��� load, save �� �ϳ��� ����� Ʈ��������� ó��
	for (int i = 0; i < 100; ++i) {
		++counter;
		this_thread::sleep_for(1ms);
	}
}

int main()
{
	atomic<int> counter(0);
	vector<thread> threads;

	for (int i = 0; i < 10; ++i) {
		threads.push_back(thread{ increment, ref(counter) });
	}

	for (auto& t : threads) {
		t.join();
	}
	
	// ��밪�� 1,000 ���, �׷��� atomic ����ȭ�������� ���� ���� �ս��� ���� �� ����
	cout << "Result = " << counter << endl;

	return 0;
}
