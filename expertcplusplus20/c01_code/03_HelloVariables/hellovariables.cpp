// NOTE: 대다수의 컴파일러는 초기화되지 않은 변수를 사용하면 경고나 에러를 발생한다.
// 일부 컴파일러는 런타임에 프로그램에서 에러를 발생시키는 코드를 생성한다.

#include <iostream>
#include <initializer_list>

using namespace std;

int main()
{
	int uninitializedInt;
	int initializedInt = 7;

	// 10진수, 8진수, 16진수, 2진수 리터럴 선언 예시
	initializer_list<int> lst{ 123, 0173, 0x7b, 0b1111011 };

	// 자리수 구분 예시
	int	exampleInt = 123'456;
	double exampleDouble = 0.123'456f;

	//cout << uninitializedInt << " is a random value" << endl;	// 최신 컴파일러는 초기화되지 않은 변수 사용에 대해서 컴파일 에러를 기본으로 한다.
	cout << initializedInt << " was assigned an initial value" << endl;

	return 0;
}
