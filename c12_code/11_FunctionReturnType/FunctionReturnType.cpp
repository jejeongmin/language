#include <iostream>

#define	ADD_3

#ifdef ADD_1
/*
C++14: 함수의 리턴 타입 자동 유추 기능 적용
다만 이렇게 선언하면 템플릿에 const 나 & 참조 속성이 있을 경우, auto 가 그 속성을 생략해버린다.
const auto 나 auto& 처럼 명시적으로 속성 지정을 해줘야 하는데 그러면 auto 를 사용하는 장점이 반감해버린다.
*/
template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2)
{
	return t1 + t2;
}
#endif

#ifdef ADD_2
/*
C++14: decltype(auto) 기능 적용
위의 문제를 decltype 활용으로 해결할 수 있다.
*/
template<typename T1, typename T2>
decltype(auto) add(const T1& t1, const T2& t2)
{
	return t1 + t2;
}
#endif

#ifdef ADD_3
/*
	대체 함수 구문 적용
	리턴 타입이 후행 선언되어 있다.

	이 경우는 리턴 타입을 함수 이름 앞쪽으로 배치할 수 없는 게..
	프로그래머가 명시적으로 템플릿의 변수 타입을 지정하지 않고, 템플릿의 매개변수 추론을 해야 할 경우
	컴파일러의 의미 분석기가 매개 변수 목록을 끝까지 훓어본 뒤에야 t1 과 t2 의 타입을 정확히 알 수 있다.

	난 함수 리턴 타입 후행 처리가 단순한 코딩 스타일의 문제라고 생각했는데 이런 문법적인 문제를 해결할 수 있었네..
*/
template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2) -> decltype(t1 + t2)
{
	return t1 + t2;
}
#endif

int main()
{
	std::cout << add(2, 4) << std::endl;

	return 0;
}
