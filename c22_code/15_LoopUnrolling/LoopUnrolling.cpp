#include <iostream>
#include <string>
#include <functional>

using namespace std;

template<int i>
class Loop
{
public:
	template <typename FuncType>
	static inline void Do(FuncType func) {
		Loop<i - 1>::Do(func);
		func(i);
	}
};

template<>
class Loop<0>
{
public:
	template <typename FuncType>
	static inline void Do(FuncType /* func */) { }
};

void DoWork(int i)
{
	cout << "DoWork(" << i << ")" << endl;
}

void DoWork2(string str, int i)
{
	cout << "DoWork2(" << str << ", " << i << ")" << endl;
}

/*
	템플릿 메타 프로그래밍의 두번째 예로 반복문을 실행 시간에 처리하지 않고, 컴파일 시간에 일렬로 펼쳐놓는 방식으로
	처리하는 루프 언롤링, loop unrolling 이란 기법이 있다. 
	참고로 loop unrolling 은 꼭 필요한 경우에만 사용하는 게 좋다.
	굳이 언롤링하도록 작성하지 않아도, 컴파일러의 최적화 판단에 따라 자동으로 언롤링 하기 때문이다.
*/
int main()
{
	Loop<3>::Do(DoWork);
	cout << endl;

	Loop<2>::Do([](int i) { DoWork2("TestStr", i); });
	cout << endl;

	return 0;
}
