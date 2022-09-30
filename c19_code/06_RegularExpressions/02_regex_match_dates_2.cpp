#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	smatch 객체의 첫번째 원소 - m[0] - 는 패턴 전체에 매칭되는 스트링을 담는다. 
*/

int main()
{
	// 3개의 캡쳐그룹 - () - 으로 등록되어 있다. 
	regex r("(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])");
	while (true) {
		cout << "Enter a date (year/month/day) (q=quit): ";
		string str;
		if (!getline(cin, str) || str == "q")
			break;

		smatch m;
		if (regex_match(str, m, r)) {
			int year = stoi(m[1]);
			int month = stoi(m[2]);
			int day = stoi(m[3]);
			cout << "  Valid date: Year=" << year << ", month=" << month << ", day=" << day << endl;
		} else {
			cout << "  Invalid date!" << endl;
		}
	}

	return 0;
}