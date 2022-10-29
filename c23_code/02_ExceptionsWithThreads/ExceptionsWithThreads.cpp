#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

void doSomeWork()
{
	for (int i = 0; i < 5; ++i) {
		cout << i << endl;
	}
	cout << "Thread throwing a runtime_error exception..." << endl;
	throw runtime_error("Exception from thread");
}

void threadFunc(exception_ptr& err)
{
	try {
		doSomeWork();
	} catch (...) {
		cout << "Thread caught exception, returning exception..." << endl;
		err = current_exception();	// 만약 처리하는 익셉션이 없으면 null exception_ptr 객체를 리턴한다.
	}
}

void doWorkInThread()
{
	exception_ptr error;
	// 스레드 시작
	thread t{ threadFunc, ref(error) };
	// 스레드가 종료할 때까지 기다린다.
	t.join();
	// 스레드에 익셉션이 발생했는지 검사한다. exception_ptr 은 nullablepointer 타입이기 때문에 if 문으로 간단히 검사할 수 있다.
	if (error) {
		cout << "Main thread received exception, rethrowing it..." << endl;
		rethrow_exception(error);	// 매개변수가 참조하는 익셉셥을 다시 던진다. 그래서 여러 스레드에서 발생한 익셉션을 처리하는 용도로 딱 맞다.
	} else {
		cout << "Main thread did not receive any exception." << endl;
	}
}

/*
	스레드가 던진 익셉션은 그 스레드 안에서 처리해야 한다.
	던진 익셉션을 스레드 안에서 잡지 못하면 c++ 런타임은 std::terminate()를 호출해서 애플리케이션 전체를 종료시킨다.
*/
int main()
{
	try {
		doWorkInThread();
	} catch (const exception& e) {
		cout << "Main function caught: '" << e.what() << "'" << endl;
	}
	return 0;
}
