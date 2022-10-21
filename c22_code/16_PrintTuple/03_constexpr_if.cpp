#include <iostream>
#include <tuple>
#include <string>

using namespace std;

/*
	c++17 부터는 constexpr if 가 추가되었다. 
	constexpr if 는 실행 시간이 아닌, 컴파일 시간에 수행된다.
	constexpr if 의 조건을 만족하지 않으면 컴파일되지 않는다.

	아래 예제에서는 constexpr if 를 사용했기 때문에
	재귀를 멈추기 위한 부분 특수화 코드를 없앨 수 있다.
*/
template<typename TupleType, int n>
class tuple_print_helper
{
public:
	tuple_print_helper(const TupleType& t) {
		if constexpr(n > 1) {
			tuple_print_helper<TupleType, n - 1> tp(t);
		}
		cout << get<n - 1>(t) << endl;
	}
};

template<typename T>
void tuple_print(const T& t)
{
	tuple_print_helper<T, tuple_size<T>::value> tph(t);
}

int main()
{
	auto t1 = make_tuple(167, "Testing", false, 2.3);
	tuple_print(t1);
}
