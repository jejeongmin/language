#include <tuple>
#include <string>

using namespace std;

class Foo
{
public:
	Foo(string str, int i) : mStr(str), mInt(i) {}

private:
	string mStr;
	int mInt;
};

/*
	���ø����� ��Ÿ ���α׷����� ���� ������ ��
*/
int main()
{
	auto myTuple = make_tuple("Hello world.", 42);
	auto foo = make_from_tuple<Foo>(myTuple);
	return 0;
}
