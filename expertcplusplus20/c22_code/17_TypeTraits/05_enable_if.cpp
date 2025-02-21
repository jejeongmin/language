#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

/*
	�����ε��� �Լ��� ���� �� ���� �� enable_if �� �̿��Ͽ� Ư���� Ÿ�� Ʈ����Ʈ�� ���� �����ε��� �Լ� �� �Ϻθ� �� �� �ִ�.
	enable_if Ʈ����Ʈ�� �����ε��� �Լ��鿡 ���� ���� Ÿ���� �������� �б��� �� �ַ� ����Ѵ�
*/

template<typename T1, typename T2>
enable_if_t<is_same_v<T1, T2>, bool>
	check_type(const T1& t1, const T2& t2)
{
	cout << "'" << t1 << "' and '" << t2 << "' ";
	cout << "are the same types." << endl;
	return true;
}

template<typename T1, typename T2>
enable_if_t<!is_same_v<T1, T2>, bool>
	check_type(const T1& t1, const T2& t2)
{
	cout << "'" << t1 << "' and '" << t2 << "' ";
	cout << "are different types." << endl;
	return false;
}

int main()
{
	check_type(1, 32);
	check_type(1, 3.01);
	check_type(3.01, "Test"s);

	return 0;
}
