#include <iostream>
#include <type_traits>

using namespace std;

class IsDoable
{
public:
	void doit() const { cout << "IsDoable::doit()" << endl; }
};

class Derived : public IsDoable
{
};

/*
	is_invocable_v 는 주어진 함수가 주어진 인수 집합에 대해 호출되는지 검사한다.
*/
template<typename T>
void call_doit(const T& [[maybe_unused]] t)
{
	if constexpr(is_invocable_v<decltype(&IsDoable::doit), T>) {
		t.doit();
	} else {
		cout << "Cannot call doit()!" << endl;
	}
}

int main()
{
	Derived d;
	call_doit(d);
	call_doit(123);

	return 0;
}
