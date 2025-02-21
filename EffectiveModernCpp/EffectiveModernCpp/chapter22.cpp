#include "stdafx.h"
#include <vector>
#include "chapter22.h"

struct chapter22::Widget::Impl
{
	std::string	name;
	std::vector<double>	data;
	int	value;
	// etc custom type..
};

chapter22::Widget::Widget()
{
	_impl = make_unique<Impl>();
}

/*
	�Ҹ��ڸ� �������� ������, �����Ϸ��� �⺻ �Ҹ��ڸ� �����ϰ� �ȴ�.
	�׷��� �Ҹ��� ���� ���� unique_ptr �� �ְ�, �� unique_ptr �� �⺻ �Ҵ��������� ������
	ǰ�� �ִ� raw pointer �� ���� delete �����ε�, 
	chapter22:Widget::impl �� ��� ���� �����ϴ� in-complete type �̴�.
	vs2017 ���������� �̷� ��� �����Ϸ��� �ڵ� ������ ���� �ʰԲ� ������ �� ����.

	���� ������, ���� ������ ��� �������� �� ����.
*/
chapter22::Widget::~Widget() = default;

chapter22::Widget::Widget(chapter22::Widget&& rhs) = default;
chapter22::Widget& chapter22::Widget::operator=(chapter22::Widget&& rhs) = default;

chapter22::Widget::Widget(const chapter22::Widget& rhs) : _impl(nullptr)
{
	if (rhs._impl)
	{
		_impl = std::make_unique<Impl>(*rhs._impl);
	}
}

chapter22::Widget& chapter22::Widget::operator=(const chapter22::Widget& rhs)
{
	if (nullptr == rhs._impl)
	{
		_impl.reset();
	}
	else if (nullptr == _impl)
	{
		_impl = std::make_unique<Impl>(*rhs._impl);
	}
	else
	{
		*_impl = *rhs._impl;
	}

	return *this;
}


int chapter22::chapterMain()
{
	chapter22::Widget	w1,w2;

	w1 = w2;

	return 0;
}


/*
	impl ���뱸�� Ŭ���� ������ Ŭ���� Ŭ���̾�Ʈ ������ ������ �������� �������ν� ���� �ð��� �����Ѵ�.

	std::unique_ptr ������ impl �����͸� ����� ������ Ư�� ��� �Լ����� Ŭ���� ����� �����ϰ� ���� ���Ͽ��� �����ؾ� �Ѵ�.
	�����Ϸ��� �⺻���� �ۼ��ϴ� �Լ� �������� ����ϱ⿡ ������ ��쿡�� �׷��� �ؾ� �Ѵ�.

	���� ������� std::unique_ptr �� ����� ��, std::shared_ptr ���� ������� �ʴ´�.
*/