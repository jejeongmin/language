#include <memory>

#define MAIN_4

using namespace std;

class Foo
{
public:
	Foo(int value) : mData(value) { }
	int mData;
};

#ifdef MAIN_4

/*
	아래와 같이 foo 객체에 포함된 객체의 멤버에 대한 aliasing 을 지원한다.
	이 경우 aliasing 을 포함한 두 shared_ptr 에 대한 참조가 모두 삭제될 때만 Foo 객체가 삭제된다.
*/

int main()
{
	auto foo = make_shared<Foo>(42);
	auto aliasing = shared_ptr<int>(foo, &foo->mData);

	return 0;
}

#endif