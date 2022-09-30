#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	sregex_token_iterator 는 토큰화 작업에 유리하다.
	c 의 strtok 함수를 사용하는 것보다 안전하고 유연하다.
	sregex_token_iterator 의 반복할 캡쳐 그룹 인덱스를 -1 로 지정하면
	토큰화 모드로 작동한다.
*/
int main()
{
	regex reg(R"(\s*[,;]\s*)");
	while (true) {
		cout << "Enter a string to split on ',' and ';' (q=quit): ";
		string str;
		if (!getline(cin, str) || str == "q")
			break;
		
		const sregex_token_iterator end;
		for (sregex_token_iterator iter(cbegin(str), cend(str), reg, -1);
			iter != end; ++iter) {
			cout << "\"" << *iter << "\"" << endl;
		}
	}

	return 0;
}