#include <type_traits>
#include <iostream>

using namespace std;

/*
	conjunction, 논리곱 &
	disjunction, 논리합 |
	negation, 부정 !
*/
int main()
{
	cout << conjunction_v<is_integral<int>, is_integral<short>> << " ";
	cout << conjunction_v<is_integral<int>, is_integral<double>> << " ";

	cout << disjunction_v<is_integral<int>, is_integral<double>, is_integral<short>> << " ";

	cout << negation_v<is_integral<int>> << " ";

	return 0;
}
