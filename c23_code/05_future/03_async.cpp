#include <iostream>
#include <future>

using namespace std;

int calculate()
{
	return 123;
}

/*
	지정한 함수를 async() 로 구동하는 방법은 두 가지다.

		- 함수를 스레드로 만들어 비동기로 구동한다.
		- 스레드를 따로 만들지 않고, 리턴된 future 에 대해 get() 을 호출할 때 동기식으로 함수를 실행한다.

	async() 인수의 동작 방식은 아래 3가지 중 하나로 실행된다.

		- launch::async : 주어진 함수를 다른 스레드에서 실행한다.
		- launch::deferred : get()을 호출할 때 주어진 함수를 현재 스레드와 동기식으로 실행시킨다.
		- launch::async | launch::deferred : c++ 런타임이 결정한다. 인자 값을 생략했을 때 기본 동작
*/
int main()
{
	auto myFuture = async(calculate);
	//auto myFuture = async(launch::async, calculate);
	//auto myFuture = async(launch::deferred, calculate);

	// 필요한 작업을 수행한다.

	// 결과를 가져온다.
	int result = myFuture.get();
	cout << result << endl;

	return 0;
}
