#include <atomic>
#include <iostream>
#include <type_traits>

using namespace std;

/*
	연산을 아토믹 방식으로 처리하는 인스트럭션을 타겟 하드웨에서에서 제공하지 않을 수 있다.
	럴 때는 아토믹 타입에 대해 is_lock_free() 메서드를 호출해서 잠그지 않아도 되는지(lock-free 인건지)
	, 즉 명시적으로 동기화 매커니즘을 사용하지 않고도 수행할 수 있는지 확인한다.
*/

class Foo { private: int mArray[123]; };	// 배열 형에 대해서는 lock free 지원하지 않음
class Bar { private: int mInt; };			// 기본 타입만 있기 때문에 lock free 지원

int main()
{
	atomic<Foo> f;
	cout << is_trivially_copyable_v<Foo> << " " << f.is_lock_free() << endl;

	atomic<Bar> b;
	cout << is_trivially_copyable_v<Bar> << " " << b.is_lock_free() << endl;
}
