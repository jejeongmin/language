#pragma once

#include "stdafx.h"
#include <array>

/*********************************************
param type �� ������ �Ǵ� ���� ���������� ���� ������ �ƴ�
*********************************************/
template<typename T>
void f1(T& param)
{
	// decltype �� �� �״�� type declaration �� ����ϴ� ������,
	// Ÿ�� üŷ�̳� Ÿ�� Ȯ���� ���� ����ϴ� ���� �ƴϴ�.
	decltype(param)	temp = param;

	// ���� ���� �ǵ� �ߴ� compile time ������ Ÿ�� Ȯ���� ���ؼ��� typeid �� ����ؾ� �Ѵ�.
	// �׷��� �� �ҽ��� ����� �����ֵ���, ���� typeid �� ���� ����� ���ø� ���� ��ȯ�� ����
	// ��Ȯ�� ����� �������� �ʴ´�. premitive type �� �ݿ��� ���̴�.
	std::cout << typeid(temp).name() << " : " << temp << std::endl;
}

/*********************************************
param type �� ���� ������
*********************************************/
template<typename T>
void f2(T&& param)
{
	std::cout << typeid(param).name() << " : " << param << std::endl;
}

/*********************************************
param type �� �����͵� �ƴϰ� ���������� �ƴ�
*********************************************/
template<typename T>
void f3(T param)
{
	std::cout << typeid(param).name() << " : " << param << std::endl;
}

/*********************************************
�迭 ������ ũ�⸦ ������ ���� ����μ� �����ִ� ���ø� �Լ�
�迭 �Ű������� �̸��� ������ ���� ����, �� ���ø���
�ʿ��� ���� �迭�� ��� ������ �������̱� �����̴�.
*********************************************/
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept
{
	return N;
}

class chapter01 : public chapter
{
	virtual int chapterMain()
	{
		int	x = 27;
		const int	cx = x;
		const int&	rx = x;

		f1(x);
		f1(cx);
		f1(rx);

		f2(x);
		f2(cx);
		f2(rx);
		f2(27);

		f3(x);
		f3(cx);
		f3(rx);

		const char	name[] = "Je, JeongMin";

		// �迭 �Ű����� ������ ������ �Ű�����ó�� ��޵ǹǷ�, ���ø� �Լ��� ������ ���޵Ǵ�
		// �迭�� ������ ������ �������� �����ȴ�.
		f3(name);

		// �Լ��� �Ű������� ��¥ �迭�� ������ �� �� ������, �迭�� ���� ������ ������ ���� �ִ�.
		// ���ʸ� �Լ��� �μ��� ������ �޵��� �ϰ�, �Լ��� �迭�� �����ϸ�, T �� ���� ������ ������
		// �迭�� ���� ������ �ȴ�. �� ������ ���� �迭�� ũ�⸦ �����Ѵ�.
		f1(name);

		// �迭�� ũ�⸦ ������ Ÿ�ӿ� �˾Ƴ� ������ �� �ִ�.
		int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
		int	mappedVals[arraySize(keyVals)];
		int	arraySize = sizeof(mappedVals) / sizeof(int);
		memset(mappedVals, 0, sizeof(mappedVals));

		std::cout << "array size : " << arraySize << std::endl;

		arrayTest();

		return 0;
	}

	/*
		MSDN : https://msdn.microsoft.com/ko-kr/library/bb983093.
		std::array �� ���� ����� ���� : https://duragon.gitbooks.io/c-11/content/chapter6.html
	*/
	void arrayTest()
	{
		std::array<int, 4> values = { 1, 2, 3 };

		for each(auto itor in values)
		{
			std::cout << itor << std::endl;
		}
	}

};
// std::array

/*
	����� �� ���׵�

	���ø� ���� ���� ���߿� ���� ������ �μ����� �������� ��޵ȴ�.
	��, �������� ���õȴ�.

	���� ���� �Ű������� ���� ���� ���� �������� �ް� �μ����� Ư���ϰ� ��޵ȴ�.

	�� ���� ����� �Ű������� ���� ���� ���� �������� const �Ǵ� volatile( �Ǵ� �� �� ���� )
	�μ��� �� const, �� volatile �μ��� ��޵ȴ�.

	���ø� ���� ���� �������� �迭�̳� �Լ� �̸��� �ش��ϴ� �μ��� �����ͷ� �ر��Ѵ�.
	��, �׷� �μ��� ������ �ʱ�ȭ�ϴ� �� ���̴� ��쿡�� �����ͷ� �ر����� �ʴ´�.
*/