#include <mutex>

using namespace std;

mutex mut1;
mutex mut2;

/*
	�ռ��� 01_multiple_locks �������� �ξ� ������ �ڵ�� lock �� �� �� �ִ�.
*/

void process()
{
	// c++17 supported
	scoped_lock locks(mut1, mut2);
	// before c++17
	//scoped_lock<mutex, mutex> locks(mut1, mut2);

	// ���� ���� ���
} // ����� ����� ���� �ڵ����� �����ȴ�.

int main()
{
	process();
	
	return 0;
}
