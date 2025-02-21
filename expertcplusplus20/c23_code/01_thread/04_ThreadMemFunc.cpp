#include <thread>
#include <iostream>

using namespace std;

class Request
{
public:
	Request(int id) : mId(id) { }

	void process()
	{
		cout << "Processing request " << mId << endl;
	}

private:
	int mId;
};

/*
	이렇게 하면 특정한 객체에 있는 메서드를 스레드로 분리해서 실행할 수 있다.
	똑같은 객체를 여러 스레드가 접근할 때 데이터 경쟁이 발생하지 않도록 thread-safe 하게 작성해야 한다.
*/
int main()
{
	Request req(100);
	thread t{ &Request::process, &req };

	t.join();

	return 0;
}
