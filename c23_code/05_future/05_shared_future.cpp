#include <future>

using namespace std;

/*
	future 의 get()을 여러 스레드에 대해 여러 번 호출하고 싶다면 std::shared_future<T> 를 사용한다.
	이때 T는 복제 생성할 수 있어야 한다.
	shared_future 는 std::future::share() 로 생성하거나
	shared_future 생성자에 future 를 전달(이동)하는 방식으로 생성한다.
*/
int main()
{
	promise<void> thread1Started, thread2Started;

	promise<int> signalPromise;
	auto signalFuture = signalPromise.get_future().share();
	//shared_future<int> signalFuture(signalPromise.get_future());

	auto function1 = [&thread1Started, signalFuture] {
		thread1Started.set_value();
		// 매개변수가 설정될 때까지 기다린다.
		int parameter = signalFuture.get();
		// ...
	};

	auto function2 = [&thread2Started, signalFuture] {
		thread2Started.set_value();
		// 매개변수가 설정될 때까지 기다린다.
		int parameter = signalFuture.get();
		// ...
	};

	// 두 람다 표현식을 비동기식으로 실행한다.
	// 이때 반드시 async()가 리턴한 future를 캡처한다.
	auto result1 = async(launch::async, function1);
	auto result2 = async(launch::async, function2);

	// 두 스레드가 구동할 때까지 기다린다.
	thread1Started.get_future().wait();
	thread2Started.get_future().wait();

	// 이제 두 스레드는 매개변수를 기다린다.
	// 매개변수를 설정해서 두 스레드 모두 깨운다.
	signalPromise.set_value(42);
}