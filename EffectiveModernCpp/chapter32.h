#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
**********************************************************/

using namespace std;

class chapter32 : public chapter
{
	class Widget
	{
	public:
		bool	isValidated() const	{ return true;  }
		bool	isArchived() const { return true;	}
	};

	virtual int chapterMain()
	{
		auto pw = std::make_unique<Widget>();

		// c++14 ������ �Ʒ��� ���� ������ ��ü�� Ŭ���� ������ �̵� ������ �� �� �ִ�.
		// �ʱ�ȭ ������(init capture) ���� �º��� pw �� Ŭ���� Ŭ���� ���� �ڷ� ����̰�, �캯�� pw �� ���ٰ� ���ǵǴ� ������ �������� pw �̴�.
		auto func = [pw = std::move(pw)]
		{
			return pw->isArchived() && pw->isValidated();
		};

		std::vector<double> data;

		// c++11 ���� bind ��ü�� �̿��� init capture �� �䳻����
		auto func2 = std::bind(
			[](const std::vector<double>& data)
			{ /* to implement function here */},
			std::move(data));

		// c++11 ������ �̵������� ���� ���, c++14 ���ٴ� �ѹ��� ���簡 �Ұ����ϴ�.
		// bind ���� ���ڸ� ���������� �Ѱ�����( std::move(data) )
		// ���ٿ��� �Ű� ������ �ް��̱� ������ �̵������� data �� ���� ���纻�� ���� �� �ۿ� ���� ( std::vector<double>& data )
		auto func3 = std::bind(
			[](std::vector<double>& data) mutable
			{ /* to implement function here */},
			std::move(data));

		return 0;
	}
};

/*
	��ü�� Ŭ���� ������ �̵��� ������ c++14 �� �ʱ�ȭ �������� ����϶�

	c++11 ������ ���� �ۼ��� Ŭ������ std::bind �� �ʱ�ȭ �������� �䳻�� �� �ִ�.
*/