#pragma once

#include <functional>
#include <memory>

/*********************************************************
**********************************************************/

class chapter12 : public chapter
{
	class Widget
	{
		using DataType = std::vector<double>;

		DataType	_values;

	public:
		DataType&	doWork() &		// doWork �� �� ������ *this �� �ް��� ������ ����ȴ�.
		{
			std::cout << "widget::dowork - left reference call" << std::endl;
			return _values;
		}

		DataType&&	doWork() &&		// doWork �� �� ������ *this �� �������� ������ ����ȴ�.
		{
			std::cout << "widget::dowork - right reference call" << std::endl;
			return std::move(_values);
		}

	};

	Widget makeWidget()
	{
		return Widget();
	}

	class Base
	{
	public:
		virtual void mf1() const;
		virtual void mf2(int x);
		virtual void mf3() &;
		void mf4() const;
	};

	// �ۼ����� �ǵ��� mf1~mf4 �� �̸��� ��� �Լ��� �����ǿ�������, �ణ�� ���̷�
	// ������ �� �Լ��� �ϳ��� ����. ������ �����Ϸ��� �ƹ��� ������ ���� �ʴ´�.
	// �̷� �� override �� ���� �ٿ��ָ� �������� ���� �Լ��鿡 ���� ������ ������ �߻���Ų��.
	// �̷��� ��ħ�� ��� Ŭ������ �� ���� �Լ��� ����(����)�� �������� �� �� ������ ��� ��������
	// ���� �����ϰ� ���ش�.
	class Derived : public Base
	{
		virtual void mf1(); // override;
		virtual void mf2(unsigned int x); // override;
		virtual void mf3() &&; // override;
		void mf4() const; // override;

		// final �� �����ϸ� �Ʒ��� �Ļ� Ŭ�������� �� �̻� �� �Լ��� �������� �� ���� �ȴ�.
		virtual void mf3() & final;
	};
	
	virtual int chapterMain()
	{
		Widget	val = makeWidget();
		val.doWork();

		makeWidget().doWork();

		return 0;
	}
};

/*
	������ �Լ��� override �� �����϶�.

	��� �Լ� ���� �����縦 �̿��ϸ� ��� �Լ��� ȣ��Ǵ� ��ü(*this) �� �ް� ������
	������ ������ �ٸ� ������� ó���� �� �ִ�.
*/