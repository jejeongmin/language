#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>

using namespace std;

void increment(atomic<int>& counter)
{
	int result = 0;
	for (int i = 0; i < 100; ++i) {
		++result;
		this_thread::sleep_for(1ms);
	}

	// 스레드 내부 저장소 지역 변수를 이용해 증가 연산을 하고, 그 결과를 counter 레퍼런스에 한 번에 연산해서 atomic 연산을 최소화하는 방식으로 최적화
	counter += result;
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

	cout << "Result = " << counter << endl;

	return 0;
}
