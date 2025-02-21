#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	c++ regex 는 ECMAScript 가 default 임
	basic(posix), extended, awk, grep, egrep 등 다른 옵션도 지원 가능 

	d{4}						숫자 4개
	(?:							캡쳐식 아님.
	0?[1-9]|1[0-2]				01~12 or 1~12
	0?[1-9]|[1-2][0-9]|3[0-1]	01~31 or 1~31

	이 예제로는 윤달 검증이 어려움. 윤달 처리 하려면 조건을 완화해서 아래와 같이 처리
	
	regex r("(\\d{4})/(\\d{1,2})/(\\d{1,2})");
*/
int main()
{
	regex r("\\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])");
	while (true) {
		cout << "Enter a date (year/month/day) (q=quit): ";
		string str;
		if (!getline(cin, str) || str == "q")
			break;

		if (regex_match(str, r))
			cout << "  Valid date." << endl;
		else
			cout << "  Invalid date!" << endl;
	}

	return 0;
}
