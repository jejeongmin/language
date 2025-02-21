#include <iostream>

#define	ADD_3

#ifdef ADD_1
/*
C++14: �Լ��� ���� Ÿ�� �ڵ� ���� ��� ����
�ٸ� �̷��� �����ϸ� ���ø��� const �� & ���� �Ӽ��� ���� ���, auto �� �� �Ӽ��� �����ع�����.
const auto �� auto& ó�� ��������� �Ӽ� ������ ����� �ϴµ� �׷��� auto �� ����ϴ� ������ �ݰ��ع�����.
*/
template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2)
{
	return t1 + t2;
}
#endif

#ifdef ADD_2
/*
C++14: decltype(auto) ��� ����
���� ������ decltype Ȱ������ �ذ��� �� �ִ�.
*/
template<typename T1, typename T2>
decltype(auto) add(const T1& t1, const T2& t2)
{
	return t1 + t2;
}
#endif

#ifdef ADD_3
/*
	��ü �Լ� ���� ����
	���� Ÿ���� ���� ����Ǿ� �ִ�.

	�� ���� ���� Ÿ���� �Լ� �̸� �������� ��ġ�� �� ���� ��..
	���α׷��Ӱ� ��������� ���ø��� ���� Ÿ���� �������� �ʰ�, ���ø��� �Ű����� �߷��� �ؾ� �� ���
	�����Ϸ��� �ǹ� �м��Ⱑ �Ű� ���� ����� ������ �f� �ڿ��� t1 �� t2 �� Ÿ���� ��Ȯ�� �� �� �ִ�.

	�� �Լ� ���� Ÿ�� ���� ó���� �ܼ��� �ڵ� ��Ÿ���� ������� �����ߴµ� �̷� �������� ������ �ذ��� �� �־���..
*/
template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2) -> decltype(t1 + t2)
{
	return t1 + t2;
}
#endif

int main()
{
	std::cout << add(2, 4) << std::endl;

	return 0;
}
