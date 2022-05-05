// NOTE: 대다수의 컴파일러는 초기화되지 않은 변수를 사용하면 경고나 에러를 발생한다.
// 일부 컴파일러는 런타임에 프로그램에서 에러를 발생시키는 코드를 생성한다.

#include <iostream>

using namespace std;

int main()
{
	int uninitializedInt;
	int initializedInt = 7;

	cout << uninitializedInt << " is a random value" << endl;	// 최신 컴파일러는 초기화되지 않은 변수 사용에 대해서 컴파일 에러를 기본으로 한다.
	cout << initializedInt << " was assigned an initial value" << endl;

	return 0;
}
