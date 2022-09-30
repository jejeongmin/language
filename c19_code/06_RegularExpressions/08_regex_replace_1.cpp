#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	regex_replace() 알고리즘은 정규표현식과 매치된 서브스트링을 대체할 포맷 스트링을 인수로 받는다.

	$n : n번째 캡쳐 그룹에 매치되는 스트링
	$& : 정규표현식 전체에 매치되는 스트링
	$` : 정규 표현식에 매치된 서브스트링의 왼쪽에 나온 입력 시퀀스의 일부
	$' : 정규 표현식에 매치된 서브스트링의 오른쪽에 나온 입력 시퀀스의 일부
	$$ : $ 기호

	위 내용을 아래에 적용하자면

	$1	: Header
	$2	: Some text
	$&	: <h1>Header</h1><p>Some text</p>
	$`	: <body>
	$'	: </body>
*/

int main()
{
	const string str("<body><h1>Header</h1><p>Some text</p></body>");
	regex r("<h1>(.*)</h1><p>(.*)</p>");

	const string format("H1=$1 and P=$2");
	string result = regex_replace(str, r, format);
	
	cout << "Original string: '" << str << "'" << endl;
	cout << "New string     : '" << result << "'" << endl;

	return 0;
}
