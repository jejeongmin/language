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
	���ø� ��Ÿ ���α׷����� �ι�° ���� �ݺ����� ���� �ð��� ó������ �ʰ�, ������ �ð��� �Ϸķ� ���ĳ��� �������
	ó���ϴ� ���� ��Ѹ�, loop unrolling �̶� ����� �ִ�. 
	����� loop unrolling �� �� �ʿ��� ��쿡�� ����ϴ� �� ����.
	���� ��Ѹ��ϵ��� �ۼ����� �ʾƵ�, �����Ϸ��� ����ȭ �Ǵܿ� ���� �ڵ����� ��Ѹ� �ϱ� �����̴�.
*/
int main()
{
	Loop<3>::Do(DoWork);
	cout << endl;

	Loop<2>::Do([](int i) { DoWork2("TestStr", i); });
	cout << endl;

	return 0;
}
