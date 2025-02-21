#include <cstdlib>
#include <memory>

using namespace std;

class Foo
{
public:
	Foo(unique_ptr<int> data) : mData(move(data)) { }

private:
	unique_ptr<int> mData;
};


int* malloc_int(int value)
{
	int* p = (int*)malloc(sizeof(int));
	*p = value;

	return p;
}

int main()
{
	auto myIntSmartPtr = make_unique<int>(42);
	Foo f(move(myIntSmartPtr));

	unique_ptr<int, decltype(free)*> myIntSmartPtr2(malloc_int(42), free);

    return 0;
}
