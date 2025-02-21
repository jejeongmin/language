#include <iostream>
#include <limits>

using namespace std;

/*
	부동소수점수의 최소값(min)은 시스템에서 표현할 수있는 가장 작은 양수값인 반면
	최저값(lowest)는 시스템에서 표현할 수 있는 가장 작은 음수값이다.
*/
int main()
{
	cout << "int:" << endl;
	cout << "Max int value: " << numeric_limits<int>::max() << endl;
	cout << "Min int value: " << numeric_limits<int>::min() << endl;
	cout << "Lowest int value: " << numeric_limits<int>::lowest() << endl;

	cout << endl << "double:" << endl;
	cout << "Max double value: " << numeric_limits<double>::max() << endl;
	cout << "Min double value: " << numeric_limits<double>::min() << endl;
	cout << "Lowest double value: " << numeric_limits<double>::lowest() << endl;

	return 0;
}