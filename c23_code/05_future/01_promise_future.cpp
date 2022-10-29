#include <iostream>
#include <thread>
#include <future>

using namespace std;

/*
	set_value 를 호출해 결과를 저장하거나, set_exception 을 호출해 익셉션을 promise에 저장한다.
	참고로 특정 promise 에 대해 set_value 나 set_exception 은 단 한 번만 호출할 수 있다.
	여러 번 호출하면 std::future_error 익셉션이 발생한다.
*/
void DoWork(promise<int> thePromise)
{
	thePromise.set_value(42);
}

/*
	스레드의 실행 결과를 promise 에 담으면 future 로 그 값을 가져올 수 있다.
	채널에 비유하면 promise 는 입력포트고, future 는 출력 포트인 셈이다.
*/
int main()
{
	// 스레드에 전달할 promise를 생성한다.
	promise<int> myPromise;
	// 이 promise에 대한 future를 가져온다.
	auto theFuture = myPromise.get_future();
	// 스레드를 생성하고 앞에서 만든 promise를 인수로 전달한다. promise 는 복제될 수 없고 이동만 가능하다.
	thread theThread{ DoWork, std::move(myPromise) };

	// 필요한 작업을 수행한다.

	// 결과를 가져온다.
	int result = theFuture.get();
	cout << "Result: " << result << endl;

	// 스레드를 조인한다.
	theThread.join();

	return 0;
}
