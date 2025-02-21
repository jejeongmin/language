#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

/*
	오버로딩된 함수가 여러 개 있을 때 enable_if 를 이용하여 특정한 타입 트레이트에 따라 오버로딩된 함수 중 일부를 끌 수 있다.
	enable_if 트레이트는 오버로딩된 함수들에 대한 리턴 타입을 기준으로 분기할 때 주로 사용한다
*/

template<typename T1, typename T2>
enable_if_t<is_same_v<T1, T2>, bool>
	check_type(const T1& t1, const T2& t2)
{
	cout << "'" << t1 << "' and '" << t2 << "' ";
	cout << "are the same types." << endl;
	return true;
}

template<typename T1, typename T2>
enable_if_t<!is_same_v<T1, T2>, bool>
	check_type(const T1& t1, const T2& t2)
{
	cout << "'" << t1 << "' and '" << t2 << "' ";
	cout << "are different types." << endl;
	return false;
}

int main()
{
	check_type(1, 32);
	check_type(1, 3.01);
	check_type(3.01, "Test"s);

	return 0;
}
