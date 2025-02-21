#include <iostream>
#include <stdexcept>

using namespace std;

/*
	��� ������ �߻��ϴ� ���� �پ��ϴ�.
	���� ���
	�������� �ʴ� ������ ���ų�, ��ũ�� �� ���� ���� ������ ó���� �� ���� �� ������ �߻��Ѵ�.
*/
int main()
{
	cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
	try {
		cout << "Hello World." << endl;
	} catch (const ios_base::failure& ex) {
		cerr << "Caught exception: " << ex.what()
			<< ", error code = " << ex.code() << endl;
	}
	return 0;
}
