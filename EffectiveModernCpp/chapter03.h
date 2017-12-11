#pragma once

#include <vector>

/*********************************************************
���⼭�� C+11 �� ���� ��ȯ ����(trailing return type) �� ���Ǿ���.
�ٽ� ���ؼ� �Լ��� ��ȯ ������ �� ��ġ�� �ƴ϶� �Ű����� ��� ������
-> ���� ��ġ�� �����ϰڴٰ� ��Ÿ���� ���̴�.
�̷��� ���� ��ȯ ���� �������� ��ȯ ������ �Ű��������� �̿��ؼ�
������ �� �ִٴ� ������ �ִ�.
**********************************************************/
template<typename Container, typename Index>
auto authAndAccess1(Container& c, Index i) -> decltype(c[i])
{
	return c[i];
}

/*********************************************************
C++14 ������ �Ϲ��Լ��� ���� ���� �Լ��� auto ��ȯ ���Ŀ� ����
���� ������ �����Ѵ�. ���� ���� ���� ���� ��ȯ ������ �ʿ� ����.
**********************************************************/
template<typename Container, typename Index>
auto authAndAccess2(Container& c, Index i)
{
	return c[i];
}

/*********************************************************
������ auto ��ȯ ������ Ȱ���� ���� ������ ��������� const ��
���� �������� ���õǴ� �Ӽ����� ���� ���� ����ġ�� ���� �� �ִ�.
�̸� decltype ������ ���� �ذ��Ѵ�.
**********************************************************/
template<typename Container, typename Index>
decltype(auto) authAndAccess3(Container& c, Index i)
{
	return c[i];
}

/*********************************************************
�ش����� ��� �����̱� �ϳ�, ù��° �Ű������� �������� ���,
���޵� �� ����. �̸� ���� ���� ������ - && - �� ���� �ذ��Ѵ�.
**********************************************************/
template<typename Container, typename Index>
decltype(auto) authAndAccess4(Container&& c, Index i)
{
	return c[i];
}

/*********************************************************
���� �������� �ʾ����� chapter25 �� ���뿡 ������
���� ������ std::forward �� �����϶�� �Ѵ�.
**********************************************************/
template<typename Container, typename Index>
decltype(auto) authAndAccess5(Container&& c, Index i)
{
	return std::forward<Container>(c)[i];
}

/*********************************************************
decltype �� �־��� �̸��̳� ǥ������ ����� �˷��ش�.
**********************************************************/
class chapter03 : public chapter
{
	virtual int chapterMain()
	{
		const int	i = 0;
		decltype(i)	di = 0;			// const int
		decltype((di))	rdi = i;	// const int&, �Ұ�ȣ�� ���� �͸����ε� ������ �ƴ� ǥ������ �Ǿ�
									// ���� ��ȯ ����� �޶�����. decltype �� ��ü������ �������� �����
									// ������ ���δ� �̿� ���� ������� ����� �ֱ⵵ �Ѵ�.

		decltype (1 == 1) boolean;	// ǥ������ �� ����� �Ǳ⵵ �Ѵ�.

		struct Point
		{
			int x;
			int y;
		};

		Point	xy;

		decltype(xy)	txy;	// Point
		decltype(Point::x)	tx;	// int

		std::vector<int>		v;
		v.push_back(0);

		decltype(v[0]) tv = xy.x;	// int& �� ��ȯ�ϱ� ������ �ް� ������ �캯�� �� �� ����

		return 0;
	}
};


/*
	����� �� ���׵�

	decltype �� �׻� ������ ǥ������ ������ �ƹ� ���� ���� �����Ѵ�.

	decltype �� ������ T �̰� �̸��� �ƴ� �ް� ǥ���Ŀ� ���ؼ��� �׻� T& ������ �����Ѵ�.

	C++14 �� decltype(auto)�� �����Ѵ�. decltype(auto) �� auto ó�� �ʱ�ġ�κ��� ������ ����������
	�� ���� ���� �������� decltype ��Ģ���� �����Ѵ�.

*/