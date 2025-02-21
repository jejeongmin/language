#include <cstddef>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
	int* ptr = nullptr;
	size_t integerCount = numeric_limits<size_t>::max();
	cout << "Trying to allocate memory for " << integerCount << " integers." << endl;

	try {
		ptr = new int[integerCount];	// 감당할 수 없는 메모리 할당
	} catch (const bad_alloc& e) {		// 메모리 할당 실패할 경우 new 는 bad_alloc 예외를 던진다.
		cerr << __FILE__ << "(" << __LINE__ << "): Unable to allocate memory: " << e.what() << endl;
		// 메모리 할당 에러를 처리한다.
		return 1;
	}
	// 메모리 할당에 성공했다면 함수를 정상적으로 진행한다.

	return 0;
}
