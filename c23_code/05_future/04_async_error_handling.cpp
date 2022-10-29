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
	future 의 가장 큰 장점은 스레드까리 익셉션을 주고 받는 데 활용할 수 있다는 것이다.
	future 에 대해 get 을 호출해서 계산된 결과를 리턴하거나, 이 future 에 연결된 promise 에 저장된 익셉션을 다시 던질 수 있다.
	package_task 나 async() 를 사용하면 구동된 함수에서 던진 익셉션이 자동으로 promise 에 저장된다.
*/

int main()
{
	// 강제로 비동기식으로 실행하도록 launch::async policy를 사용한다.
	auto myFuture = async(launch::async, calculate);

	// 필요한 작업을 수행한다.

	// 결과를 가져온다.
	try {
		int result = myFuture.get();
		cout << result << endl;
	} catch (const exception& ex) {
		cout << "Caught exception: " << ex.what() << endl;
	}

	return 0;
}
