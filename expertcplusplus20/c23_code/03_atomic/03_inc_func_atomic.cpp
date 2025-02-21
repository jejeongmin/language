#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>

using namespace std;

void increment(atomic<int>& counter)
{
	// ++counter 연산을 수행하면서 필요한 load, save 를 하나의 아토믹 트랜잭션으로 처리
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
	
	// 기대값인 1,000 출력, 그러나 atomic 동기화연산으로 인해 성능 손실이 있을 수 있음
	cout << "Result = " << counter << endl;

	return 0;
}
