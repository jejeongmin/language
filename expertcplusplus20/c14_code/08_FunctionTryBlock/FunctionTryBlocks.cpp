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
	������ �̴ϼȶ��������� ���ܰ� �߻��� ����
	�Ʒ��� ���� �Լ� try block �̶�� Ư���� ������ ���� ó���� �� �ִ�.
*/
MyClass::MyClass()
try
	: mData(new int[42]{ 1, 2, 3 }), mTestInt(6), mTestString("here?"), mSubObject(42)
{
	/* ... ������ �ٵ� ... */
}
catch (const exception& e)
{
	// �޸� ����.
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
