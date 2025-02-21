#include <thread>
#include <iostream>

using namespace std;

class Counter
{
public:
	Counter(int id, int numIterations)
		: mId(id), mNumIterations(numIterations)
	{
	}

	void operator()() const
	{
		for (int i = 0; i < mNumIterations; ++i) {
			cout << "Counter " << mId << " has value " << i << endl;
		}
	}

private:
	int mId;
	int mNumIterations;
};

/*
	함수 객체는 항상 스레드의 내부 저장소에 복제된다. 
	함수 객체의 인스턴스를 복제하지 않고 그 인스턴스에 대해 operator()를 호출하려면 std::ref 나 std::cref 를 사용해서
	인스턴스를 레퍼런스로 전달해야 한다. 예를 들면 다음과 같다.

	Counter c(2, 12);
	thread t2(std::ref(c));
*/
int main()
{
	// 유니폼 초기화 구문을 적용한다.
	thread t1{ Counter{ 1, 20 } };

	// 이름 있는 변수를 사용한다.
	Counter c(2, 12);
	thread t2(c);

	// 임시 객체를 사용한다.
	thread t3(Counter(3, 10));

	// 세 스레드가 모두 마칠 때까지 기다린다.
	t1.join();
	t2.join();
	t3.join();

	return 0;
}
