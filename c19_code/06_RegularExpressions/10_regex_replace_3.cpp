#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	가장 먼저 각 단어를 매치하는 정규 표현식을 생성하고,
	이 표현식에 매치되는 결과마다 $1\n 으로 교체한다.
	여기서 $1 자리에는 매치된 단어가 들어간다.
	여기서도 format_no_copy 플래그를 지정했다.
	공백이나 비단어 문자가 결과에 복제되지 않게 하기 위해서다.
*/
int main()
{
	regex reg("([\\w]+)");
	const string format("$1\n");
	while (true) {
		cout << "Enter a string to split over multiple lines (q=quit): ";
		string str;
		if (!getline(cin, str) || str == "q")
			break;
		
		cout << regex_replace(str, reg, format, regex_constants::format_no_copy) << endl;
	}

	return 0;
}
