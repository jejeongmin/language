#include <string>
#include <iostream>

using namespace std;

const char* return_const_string_ptr();

int main()
{
	string myString = "hello";

	myString += ", there";

	string myOtherString = myString;

	if (myString == myOtherString) {
		myOtherString[0] = 'H';
	}

	cout << myString << endl;
	cout << myOtherString << endl;

	const char* invalid_ptr = return_const_string_ptr();
	cout << invalid_ptr << endl;

	auto	string1 = "hello world";
	auto	string2 = "hello world"s;

	return 0;
}

/*
	tempstring 은 지역 변수인데, 그 지역 변수에 대한 const char* 를 반환하면 호출한 쪽에서 받을 때는
	당연히 접근하면 안되는 쓰레기 값이 들어있지. 이런 식으로 코드 짤 일은 드물겠지만, 눈에 잘 안보일 수 있으니 주의.
*/
const char* return_const_string_ptr()
{
	std::string		tempstring = "valid in return_const_string_ptr()";

	return tempstring.c_str();
}