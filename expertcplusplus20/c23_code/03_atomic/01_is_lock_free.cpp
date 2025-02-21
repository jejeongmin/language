#include <atomic>
#include <iostream>
#include <type_traits>

using namespace std;

/*
	������ ����� ������� ó���ϴ� �ν�Ʈ������ Ÿ�� �ϵ���������� �������� ���� �� �ִ�.
	�� ���� ����� Ÿ�Կ� ���� is_lock_free() �޼��带 ȣ���ؼ� ����� �ʾƵ� �Ǵ���(lock-free �ΰ���)
	, �� ��������� ����ȭ ��Ŀ������ ������� �ʰ� ������ �� �ִ��� Ȯ���Ѵ�.
*/

class Foo { private: int mArray[123]; };	// �迭 ���� ���ؼ��� lock free �������� ����
class Bar { private: int mInt; };			// �⺻ Ÿ�Ը� �ֱ� ������ lock free ����

int main()
{
	atomic<Foo> f;
	cout << is_trivially_copyable_v<Foo> << " " << f.is_lock_free() << endl;

	atomic<Bar> b;
	cout << is_trivially_copyable_v<Bar> << " " << b.is_lock_free() << endl;
}
