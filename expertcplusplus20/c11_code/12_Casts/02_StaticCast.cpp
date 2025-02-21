//#define MAIN_2

#ifdef MAIN_2
class Base
{
public:
	virtual ~Base() = default;
};

class Derived : public Base
{
public:
	virtual ~Derived() = default;
};

/*
	static_cast 는 변환 가능한지 타입 검사를 수행하지 않는다.
	type 검사를 수행하려면 dynamic_cast 를 사용해야 한다.
*/
int main()
{
	int i = 3;
	int j = 4;
	double result = static_cast<double>(i) / j;


	Base* b;
	Derived* d = new Derived();

	b = d; // 상속 계층을 올라갈 때는 캐스팅할 필요 없다.
	d = static_cast<Derived*>(b); // 상속 계층을 내려갈 때는 캐스팅해야 한다.

	Base base;
	Derived derived;

	Base& br = derived;
	Derived& dr = static_cast<Derived&>(br);

	return 0;
}
#endif