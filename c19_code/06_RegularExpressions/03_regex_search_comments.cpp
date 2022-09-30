#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	// 로 시작하고
	옵션으로 \s 공백이 나올 수 있고
	(.+) 캡쳐 그룹에 캡쳐된 문자가 하나 이상 나오는 문장을 매치하고
	$ 문자열을 끝을 나타내는 anchor 를 박는다.
*/
int main()
{
	regex r("//\\s*(.+)$");
	while (true) {
		cout << "Enter a string with optional code comments (q=quit): ";
		string str;
		if (!getline(cin, str) || str == "q")
			break;

		smatch m;
		if (regex_search(str, m, r))
			cout << "  Found comment '" << m[1] << "'" << endl;
		else
			cout << "  No comment found!" << endl;
	}

	return 0;
}
