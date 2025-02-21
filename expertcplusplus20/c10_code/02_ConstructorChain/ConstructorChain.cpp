#include <iostream>

using namespace std;

class StaticObj
{
public:
	StaticObj() { cout << "static"; }
	virtual ~StaticObj() = default;
};

class Something
{
public:
	Something() { cout << "2"; }
	virtual ~Something() { cout << "2"; }

	inline static StaticObj	mStaticOj;
};

class Base
{
public:
	Base() { cout << "1"; }
	virtual ~Base() { cout << "1"; }

	inline static StaticObj	mStaticOj;
};

class Derived : public Base
{
public:
	Derived() { cout << "3"; }
	virtual ~Derived() { cout << "3"; }

private:
	Something	mDataMember;
	inline static StaticObj	mStaticOj;
};

int main()
{
	Derived myDerived;
	return 0;
}
