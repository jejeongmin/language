#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std;

class MyException : public exception
{
public:
	MyException(string_view message) : mMessage(message) {}
	virtual const char* what() const noexcept override { return mMessage.c_str(); }

private:
	string mMessage;
};

void doSomething()
{
	try {
		throw runtime_error("Throwing a runtime_error exception");
	} catch (const runtime_error& /*e*/) {
		cout << __func__ << " caught a runtime_error" << endl;
		cout << __func__ << " throwing MyException" << endl;
		throw_with_nested(MyException("MyException with nested runtime_error"));
	}
}

int main()
{
	try {
		doSomething();
	} catch (const MyException& e) {
		cout << __func__ << " caught MyException: " << e.what() << endl;
/*
		원래는 이렇게 좀 복잡하게 nested exception 이 있는지 체크해서 던져야 하는데
		rethrow_if_nested 같은 헬퍼 함수를 이용할 수 있도록 정의해뒀다.

		const auto* pNested = dynamic_cast<const nested_exception*>(&e);
		if (pNested) {
			try {
				pNested->rethrow_nested();
			} catch (const runtime_error& e) {
				// Handle nested exception
				cout << "  Nested exception: " << e.what() << endl;
			}
		}
*/
		try {
			rethrow_if_nested(e);
		} catch (const runtime_error& e) {
			// Handle nested exception
			cout << "  Nested exception: " << e.what() << endl;
		}
	}

	return 0;
}
