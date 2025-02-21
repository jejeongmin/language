#include <iostream>
#include <string>
#include <tuple> 

using namespace std;

/*
	������ ���ε��� �������� �ʰ� tuple �� �и��Ϸ���, std::tie ��� ��ƿ��Ƽ �Լ��� Ȱ���ϸ� �ȴ�.
	�� �Լ��� ���۷����� ������ tuple �� �����Ѵ�.
	
	tie(i, str, b) ��� ȣ���ϸ� i,str,b �� ���� ���۷����� ������ tuple �� �����ȴ�.
	���⿡ ���� �����ڸ� �̿��Ͽ� tuple t1 �� tie()�� ����� ������ ���̴�.

	������ ���ε��� �ξ�����ϱ� ���ϴ�.
	std::ignore �� �ȴٴ� ���� �ܿ��� ���� �� ���� ���� �� �ϴ�.
	������ ���ε��� auto[i, , b] = t1; �� ���� ������� �������ָ� �����ٵ�.
*/
int main()
{
	tuple<int, string, bool> t1(16, "Test", true);

	{
		int i = 0;
		string str;
		bool b = false;
		cout << "Before: i = " << i << ", str = \"" << str << "\", b = " << b << endl;
		tie(i, str, b) = t1;
		cout << "After:  i = " << i << ", str = \"" << str << "\", b = " << b << endl;
	}

	{
		int i = 0;
		bool b = false;
		cout << "Before: i = " << i << ", b = " << b << endl;
		tie(i, std::ignore, b) = t1;
		cout << "After:  i = " << i << ", b = " << b << endl;
	}
	return 0;
}