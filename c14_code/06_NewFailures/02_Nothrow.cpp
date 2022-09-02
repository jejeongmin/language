#include <cstddef>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
	size_t integerCount = numeric_limits<size_t>::max();
	cout << "Trying to allocate memory for " << integerCount << " integers." << endl;

	int* ptr = new(nothrow) int[integerCount];	// nothrow 지정할 경우, new 는 bad_alloc 예외를 던지는 대신, 결과로 nullptr 을 반환한다
	if (ptr == nullptr) {
		cerr << __FILE__ << "(" << __LINE__ << "): Unable to allocate memory!" << endl;
		// 메모리 할당 에러를 처리한다.
		return 1;
	}
	// 메모리 할당에 성공했다면 함수를 정상적으로 진행한다.

	return 0;
}
