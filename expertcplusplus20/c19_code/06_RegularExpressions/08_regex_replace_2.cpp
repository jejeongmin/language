#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	format_default		: 패턴에 매치되는 항목은 모두 교체하고, 매치되지 않는 항목은 출력에 복제한다.
	format_no_copy		: 패턴에 매치되는 항목은 모두 교체하고, 매치되지 않는 항목은 출력에 복제하지 않는다.
	format_first_only	: 패턴에 첫번째 매치되는 항목만 교체한다. 
*/
int main()
{
	const string str("<body><h1>Header</h1><p>Some text</p></body>");
	regex r("<h1>(.*)</h1><p>(.*)</p>");

	const string format("H1=$1 and P=$2");
	string result = regex_replace(str, r, format, regex_constants::format_no_copy);
	
	cout << "Original string: '" << str << "'" << endl;
	cout << "New string     : '" << result << "'" << endl;

	return 0;
}
