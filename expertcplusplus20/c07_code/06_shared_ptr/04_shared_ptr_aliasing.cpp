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
	�Ʒ��� ���� foo ��ü�� ���Ե� ��ü�� ����� ���� aliasing �� �����Ѵ�.
	�� ��� aliasing �� ������ �� shared_ptr �� ���� ������ ��� ������ ���� Foo ��ü�� �����ȴ�.
*/

int main()
{
	auto foo = make_shared<Foo>(42);
	auto aliasing = shared_ptr<int>(foo, &foo->mData);

	return 0;
}

#endif