#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	c++ regex �� ECMAScript �� default ��
	basic(posix), extended, awk, grep, egrep �� �ٸ� �ɼǵ� ���� ���� 

	d{4}						���� 4��
	(?:							ĸ�Ľ� �ƴ�.
	0?[1-9]|1[0-2]				01~12 or 1~12
	0?[1-9]|[1-2][0-9]|3[0-1]	01~31 or 1~31

	�� �����δ� ���� ������ �����. ���� ó�� �Ϸ��� ������ ��ȭ�ؼ� �Ʒ��� ���� ó��
	
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
