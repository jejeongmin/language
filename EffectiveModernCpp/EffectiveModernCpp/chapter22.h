#pragma once

#include <functional>
#include <memory>
#include "chapter.h"


/*********************************************************
	impl ����� Ȱ���ϴ� ����,
	�ʹ� �� ���� �ð��� ���̰ų�,
	���̺귯�� ������ �������̽� �������� ���� ���带 �����ϱ� ���� �ַ� ����Ѵ�.
	impl ��ü ������ unique_ptr �� Ȱ���϶�� ���� chapter22 �� �����̴�.
**********************************************************/

using namespace std;

class chapter22 : public chapter
{
public:
	class Widget
	{
	public:
		Widget();
		~Widget();

		Widget(Widget&& rhs);
		Widget& operator=(Widget&& rhs);

		Widget(const Widget& rhs);
		Widget& operator=(const Widget& rhs);

	private:
		struct Impl;		// ���� �����ϴ� �ҿ��� ����( in-complete type )
		std::unique_ptr<Impl>	_impl;
	};

	virtual int chapterMain();
};

/*

*/