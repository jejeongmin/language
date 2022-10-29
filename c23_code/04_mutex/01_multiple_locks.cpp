#include <mutex>

using namespace std;

mutex mut1;
mutex mut2;

/*
	시간 제약이 없는 뮤텍스 함수 : lock(), unlock(), try_lock()
	시간 제약이 있는 뮤텍스 함수 : try_lock_for(), try_lock_until()

	mutex class
		- mutex
		- recursive_mutix
		- shared_mutex

	lock class
		- lock_guard
		- unique_lock
		- shared_lock
*/

void process()
{
	// c++17 supported
	unique_lock lock1(mut1, defer_lock);  
	unique_lock lock2(mut2, defer_lock);

	// before c++17
	// unique_lock<mutex> lock1(mut1, defer_lock);	
	// unique_lock<mutex> lock2(mut2, defer_lock);

	// lock 2개를 데드락 발생 걱정 없이 여러 개의 mutex 를 한 번에 거는데 사용된다.
	lock(lock1, lock2);
	// 락을 얻은 경우
} // 블록을 벗어나면 락이 자동으로 해제된다.

int main()
{
	process();
	
	return 0;
}
