#include <mutex>

using namespace std;

mutex mut1;
mutex mut2;

/*
	�ð� ������ ���� ���ؽ� �Լ� : lock(), unlock(), try_lock()
	�ð� ������ �ִ� ���ؽ� �Լ� : try_lock_for(), try_lock_until()

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

	// lock 2���� ����� �߻� ���� ���� ���� ���� mutex �� �� ���� �Ŵµ� ���ȴ�.
	lock(lock1, lock2);
	// ���� ���� ���
} // ����� ����� ���� �ڵ����� �����ȴ�.

int main()
{
	process();
	
	return 0;
}
