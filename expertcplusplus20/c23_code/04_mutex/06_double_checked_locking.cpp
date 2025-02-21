#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>

using namespace std;

void initializeSharedResources()
{
	// ... 공유 리소스를 여러 스레드가 사용할 수 있도록 초기화한다.

	cout << "Shared resources initialized." << endl;
}

atomic<bool> gInitialized(false);
mutex gMutex;

/*
	이중 검사 락 패턴(double-checked locking pattern)은 사실 anti-patter(나쁜 패턴)이라서 사용하지 않는 것이 좋다.
	이것보다는 기본 락, 아토빅변수, call_once, 함수 로컬 static 인스턴스를 활용하는 것이 좋다
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
