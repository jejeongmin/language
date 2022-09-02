#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class SubObject
{
	public:
		SubObject(int i);
};

SubObject::SubObject(int /*i*/)
{
	throw runtime_error("Exception by SubObject ctor");
}

class MyClass
{
	public:
		MyClass();
	private:
		int* mData = nullptr;
		SubObject mSubObject;
		int	mTestInt = 5;
		std::string	mTestString = "hmm?";
};

/*
	생성자 이니셜라이저에서 예외가 발생할 경우는
	아래와 같이 함수 try block 이라는 특수한 문법을 통해 처리할 수 있다.
*/
MyClass::MyClass()
try
	: mData(new int[42]{ 1, 2, 3 }), mTestInt(6), mTestString("here?"), mSubObject(42)
{
	/* ... 생성자 바디 ... */
}
catch (const exception& e)
{
	// 메모리 정리.
	delete[] mData;
	mData = nullptr;
	cout << "mTestInt : " << mTestInt << endl;
	cout << "mTestString : " << mTestString << endl;

	cout << "function-try-block caught: '" << e.what() << "'" << endl;
}

int main()
{
	try {
		MyClass m;
	} catch (const exception& e) {
		cout << "main() caught: '" << e.what() << "'" << endl;
	}
	return 0;
}
