#pragma once

#include <functional>
#include <memory>

/*********************************************************
���� ������ �޴� �ϳ��� ���ø��� �ް� ������ ������ �����鿡 ���� �ߺ������� �� ���� �Լ��� ��ü�ϸ�
��������� �߰� ����� ������ ���ɼ��� ū ��찡 �ִٴ� ���� ����̴�.
�� ū ������ �μ��� ���� ��, ������ ���Ѵ�� �޴� ��� ��ǻ� �ߺ� ���� ������ �������� ���鿡�� ���� ������ �ƴ϶�� ���̴�, Ÿ���� �絵 �׷���.
�ᱹ ������ ����� ���� �����̴�.
**********************************************************/

using namespace std;

class chapter25 : public chapter
{
	class Widget
	{
	public:
		template<typename T>
		void setName(T&& newName)
		{
			_name = std::move(newName);
		}

	private:
		std::string _name;
	};

	/*
		�Լ��� ����� ������ �����شٸ�( return by value ), �׸��� �װ��� ������ ������ ���� ������ ���� ��ü���,
		�ش� ������ �����ִ� return ������ std::move �� std::forward �� ����ϴ� ���� �ٶ����ϴ�.
	*/
	class Matrix
	{
		friend Matrix	operator+(Matrix&& lhs, const Matrix& rhs)
		{
			lhs._x += lhs._x;
			lhs._y += lhs._y;
			return std::move(lhs);
		}

	private:
		int		_x, _y;
	};
	
	/*
		�Ʒ� �Լ� ������ ���� �״�ζ�� ���������� �����ؼ� ��ȯ�ϴ� ��ó�� ���̳�
		�����Ϸ��� ��ȯ�� ����ȭ( RVO :  Return Value Optimazation ) �� ���� ���縦 ���Ѵ�.
		�����Ϸ��� ������ ����ȭ�� �ϴ� ���̴�.
	*/
	Widget makeWidget_right_implementation()
	{
		Widget	w;
		return w;
	}

	/*
		�Ʒ� �Լ��� ���������� ���縦 ���ϱ� ����, ���� ����ȭ�� �õ��� ���̳� �ǵ���� �������� �ʴ´�.
		�����Ϸ��� RVO �� �����ϱ� ���� ���� ������ ��ȯ���� ����������� �ϴµ�, ���α׷����� ����ȭ�� ����
		�ۼ����� �ǵ��� �޸� RVO �� ������ϰ� �ȴ�. RVO �� ���� ����ȭ�� std::move �� ���� �̵� ��뺸�� �� ȿ�����̱� ������
		�������̸�, RVO �� Ȱ���ϴ� ���� �ǰ��Ѵ�.

	*/
	Widget makeWidget_wrong_implementation()
	{
		Widget	w;

		return std::move(w);
	}

	

	virtual int chapterMain()
	{
		Widget	w;
		auto	n = "jeongminje";

		std::cout << "" << n << std::endl;

		w.setName(n);

		std::cout << n << std::endl;

		return 0;
	}
};

/*
	������ ������ ���� ������ ���������� ���̴� ��������, ������ �������� std::move ��, ���� �������� std::forward �� �����϶�

	����� �� ���� ������� �����ִ� �Լ��� ������ ������ ���� ������ ������ ������ ���� std::move �� std::forward �� �����϶�

	��ȯ�� ����ȭ�� ����� �� �� �ִ� ���� ��ü���� ����� std::move �� std::forward �� �������� ���ƾ� �Ѵ�.
*/