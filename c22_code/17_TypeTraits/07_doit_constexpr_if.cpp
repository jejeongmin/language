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
	t 를 사용하지 않는 경우, 사용하지 않는 매개변수에 대한 경고 메시지를 차단하기 위해 maybe_unused 사용
*/
template<typename T>
void call_doit(const T& [[maybe_unused]] t)	
{
	if constexpr(is_base_of_v<IsDoable, T>) {
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
