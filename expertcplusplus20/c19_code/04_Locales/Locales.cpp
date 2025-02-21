#include <iostream>
#include <string>
#include <locale>

using namespace std;

/*
	특정한 데이터를 문화적 배경에 따라 그룹으로 묶는 방식을 C++ 에서는 로케일이라고 한다.
*/
int main()
{
	locale loc("");
	
	if (loc.name().find("en_US") == string::npos &&
		loc.name().find("en-US") == string::npos) {
		wcout << L"Welcome non-U.S. English speaker!" << endl;
	} else {
		wcout << L"Welcome U.S. English speaker!" << endl;
	}

	return 0;
}
