#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>

using namespace std;

/*
	c++ 은 <utility> 헤더 파일에 정의된 std::integer_sequence 를 이용한 컴파일 시간 정수 시퀀스를 제공한다.
	이 기능은 템플릿 메타 프로그래밍에서 인덱스의 시퀀스, 즉 size_t 타입에 대한 정수 시퀀스를 컴파일 시간에 생성하는데 주로 사용된다.
	이를 위해 std::index_sequence 도 제공한다.
	주어진 매개변수 팩과 같은 길이의 인덱스 시퀀스를 생성할 때는 std::index_sequence_for 를 사용하면 된다.
*/

template<typename Tuple, size_t... Indices>
void tuple_print_helper(const Tuple& t, index_sequence<Indices...>)
{
	((cout << get<Indices>(t) << endl), ...);
}

template<typename... Args>
void tuple_print(const tuple<Args...>& t)
{
	tuple_print_helper(t, index_sequence_for<Args...>());
}

int main()
{
	auto t1 = make_tuple(167, "Testing", false, 2.3);
	tuple_print(t1);
}