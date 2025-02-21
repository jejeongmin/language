#include <mutex>

using namespace std;

mutex mut1;
mutex mut2;

/*
	앞서의 01_multiple_locks 예제보다 훨씬 간결한 코드로 lock 을 걸 수 있다.
*/

void process()
{
	// c++17 supported
	scoped_lock locks(mut1, mut2);
	// before c++17
	//scoped_lock<mutex, mutex> locks(mut1, mut2);

	// 락을 얻은 경우
} // 블록을 벗어나면 락이 자동으로 해제된다.

int main()
{
	process();
	
	return 0;
}
