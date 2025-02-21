#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	regex_replace() �˰����� ����ǥ���İ� ��ġ�� ���꽺Ʈ���� ��ü�� ���� ��Ʈ���� �μ��� �޴´�.

	$n : n��° ĸ�� �׷쿡 ��ġ�Ǵ� ��Ʈ��
	$& : ����ǥ���� ��ü�� ��ġ�Ǵ� ��Ʈ��
	$` : ���� ǥ���Ŀ� ��ġ�� ���꽺Ʈ���� ���ʿ� ���� �Է� �������� �Ϻ�
	$' : ���� ǥ���Ŀ� ��ġ�� ���꽺Ʈ���� �����ʿ� ���� �Է� �������� �Ϻ�
	$$ : $ ��ȣ

	�� ������ �Ʒ��� �������ڸ�

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
