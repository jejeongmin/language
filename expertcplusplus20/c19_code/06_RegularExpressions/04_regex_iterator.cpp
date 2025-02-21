#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	�� �� �̻��� �ܾ �˻��ϴ� [\w]+ ���� ǥ������ �����ߴ�.

	sregex_iterator �� �������ϸ� smatch ��ü�� ���� �� �ִ�.
	�� smatch ��ü�� ù ��° ������ [0]�� �����ϸ� ��ġ�� �κ� ��Ʈ���� ���� �� �ִ�.

	sregex_iterator iter(cbegin(str), cend(str), regex("[\\w]+")) �� ���� ��������
	������� �ʵ��� �����Ѵ�.
	 �ֳ��ϸ� iterator �� ���������� ���� ǥ���Ŀ� ���� �����͸� ������ 
	������ ���� ǥ������ �μ��� �޴� �����ڸ� ��������� delete �ϱ� ������
	�ӽ� regex ��ü�� ������ �� ����.
*/
int main()
{
	regex reg("[\\w]+");
	while (true) {
		cout << "Enter a string to split (q=quit): ";
		string str;
		if (!getline(cin, str) || str == "q")
			break;
		
		const sregex_iterator end;
		for (sregex_iterator iter(cbegin(str), cend(str), reg); iter != end; ++iter) {
			cout << "\"" << (*iter)[0] << "\"" << endl;
		}
	}

	return 0;
}