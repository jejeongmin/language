#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>

using namespace std;

void increment(int& counter)
{
	for (int i = 0; i < 100; ++i) {
		++counter;
		this_thread::sleep_for(1ms);
	}
}

int main()
{
	int counter = 0;	
	vector<thread> threads;

	for (int i = 0; i < 10; ++i) {
		threads.push_back(thread{ increment, ref(counter) });
	}

	for (auto& t : threads) {
		t.join();
	}

	// count 에 대한 데이터 경쟁이 발생해 기대값인 1,000 이 나오지 않음
	cout << "Result = " << counter << endl;

	return 0;
}
