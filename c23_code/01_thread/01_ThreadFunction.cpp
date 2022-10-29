#include <iostream>
#include <thread>

using namespace std;

void counter(int id, int numIterations)
{
	for (int i = 0; i < numIterations; ++i) {
		cout << "Counter " << id << " has value " << i << endl;
	}
}

/*
	스레드 함수에 전달한 인수는 항상 그 스레드의 내부 저장소에 복제된다.
	인수를 레퍼런스로 전달하고 싶다면 <functional> 에 정의된 std::ref() 나 std::cref()를 사용한다.
*/
int main()
{
	thread t1(counter, 1, 6);
	thread t2(counter, 2, 4);
	t1.join();
	t2.join();

	return 0;
}
