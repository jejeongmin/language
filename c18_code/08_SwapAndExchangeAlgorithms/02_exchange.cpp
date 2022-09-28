#include <utility>
#include <iostream>

using namespace std;

/*
	기존 값을 새 값으로 교체한 후 기존 값을 리턴한다.
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

	exchage() 는 이동 대입 연산자를 구현할 때 유용하다.
	이동 대입 연산자는 원본 객체에서 대상 객체로 데이터를 이동해야 한다.
	이때 원본 객체에 있던 데이터를 널null 로 만들어야 할 때가 많은데,
	이럴 때 exchange 가 코드를 간결하게 한다.

	Foo& operator=(Foo&& rhs) noexcept
	{
		// 자신을 대입하는 것은 아닌지 검사한다.
		if (this == &rhs) return *this;

		// 예전 메모리를 해제한다.
		delete mPtr; mPtr = nullptr;

		// 데이터를 이동한다.
		mPtr = rhs.mPtr;	// 데이터를 원본에서 대상으로 옮긴다.
		rhs.mPtr = nullptr;	// 원본에 있던 데이터를 널로 만든다.

		return *this;
	}

----->

	Foo& operator=(Foo&& rhs) noexcept
	{
		// 자신을 대입하는 것은 아닌지 검사한다.
		if (this == &rhs) return *this;

		// 예전 메모리를 해제한다.
		delete mPtr; mPtr = nullptr;

		// 데이터를 이동한다.
		mPtr = exchange(rhs.mPtr, nullptr);	// 이동 후 널로 만든다.

		return *this;
	}
*/