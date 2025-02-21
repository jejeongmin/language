#include <utility>
#include <iostream>

using namespace std;

/*
	���� ���� �� ������ ��ü�� �� ���� ���� �����Ѵ�.
*/
int main()
{
	int a = 11;
	int b = 22;

	cout << "Before exchange(): a = " << a << ", b = " << b << endl;

	int returnedValue = exchange(a, b);

	cout << "After exchange():  a = " << a << ", b = " << b << endl;
	cout << "exchange() returned: " << returnedValue << endl;

	return 0;
}

/*

	exchage() �� �̵� ���� �����ڸ� ������ �� �����ϴ�.
	�̵� ���� �����ڴ� ���� ��ü���� ��� ��ü�� �����͸� �̵��ؾ� �Ѵ�.
	�̶� ���� ��ü�� �ִ� �����͸� ��null �� ������ �� ���� ������,
	�̷� �� exchange �� �ڵ带 �����ϰ� �Ѵ�.

	Foo& operator=(Foo&& rhs) noexcept
	{
		// �ڽ��� �����ϴ� ���� �ƴ��� �˻��Ѵ�.
		if (this == &rhs) return *this;

		// ���� �޸𸮸� �����Ѵ�.
		delete mPtr; mPtr = nullptr;

		// �����͸� �̵��Ѵ�.
		mPtr = rhs.mPtr;	// �����͸� �������� ������� �ű��.
		rhs.mPtr = nullptr;	// ������ �ִ� �����͸� �η� �����.

		return *this;
	}

----->

	Foo& operator=(Foo&& rhs) noexcept
	{
		// �ڽ��� �����ϴ� ���� �ƴ��� �˻��Ѵ�.
		if (this == &rhs) return *this;

		// ���� �޸𸮸� �����Ѵ�.
		delete mPtr; mPtr = nullptr;

		// �����͸� �̵��Ѵ�.
		mPtr = exchange(rhs.mPtr, nullptr);	// �̵� �� �η� �����.

		return *this;
	}
*/