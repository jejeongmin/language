#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
	�Ϻ� ������ �ܼ��� ��ü���� �����ϴ� �͸��� �ƴ϶�, �� ��ü���� �ֿ� Ư¡, �� �� ����, �ް� �Ǵ� ������ ����,
	const �� volatile ���α����� �����ϴ� ���� ���Ѵ�.

	�Ʒ������� �Ϻ������� �����ϴ� c++ ������ Ư���� ���̽����� �����ְ�, �װ��� ��ȸ�ϴ� ����� �����ش�.
**********************************************************/

using namespace std;

class chapter30 : public chapter
{
	void	f(const std::vector<int>& v) {}

	template <typename T>
	void fwd(T&& param)
	{
		f(std::forward<T>(param));
	}

	class Widget
	{
	public:
		static constexpr size_t MinVals = 32;
	};

	void	f2(size_t val) {}

	template <typename T>
	void fwd2(T&& param)
	{
		f2(std::forward<T>(param));
	}

	void	f3(int pf(int)) {}

	template <typename T>
	void fwd3(T&& param)
	{
		f3(std::forward<T>(param));
	}

	static int	processVal(int value) { return 0;  }
	static int	processVal(int value, int priority) { return 0; }

	struct IPv4Header
	{
		uint32_t	version : 4,
					IHL : 4,
					DSCP : 6,
					ECN : 2,
					totalLength : 16;				
	};
	
	virtual int chapterMain()
	{
		/*
			�߰�ȣ �ʱ�ġ ���� ���

			���ø� ������ �߰�ȣ �ʱ�ġ�� std::initializer_list �� �ν��� �� ����.
			�ݸ� auto �� std::initializer_list ������ �����ϴ� ( chapter2 ���� ���� )
		*/
		//fwd({1, 2, 3});	
		auto il = { 1, 2, 3 };
		fwd(il);

		/*
			�� �����͸� ���ϴ� 0 �Ǵ� NULL

			NULL �� �Ϻ����޵��� �ʴ´�. �翬�� �� ���� 0 �̱� �����̴�.
			0 �̳� NULL ��� nullptr �� ����ϸ� �ȴ� ( chapter 8 ���� ���� )
		*/

		/*
			���� �� ���� static const �� constexpr �ڷ� ���

			������ �����Ѵٴ� �� �ּ� ������ �ǹ��Ѵ�. static MinVals �� ���� ���� ��, ���ǰ� ����. �̷� ��� �������� ������ ��ũ���� �����Ѵ�.
			���� �����Ϸ������� static ������ ���� ���Ǹ� ���� ���Ͽ��� ������ ���־���� ������
			�� �ڵ带 �׽�Ʈ�� vs2017 ������ MinVals �� ���� ���ǰ� ��� �����Ϸ��� �˾Ƽ� ���Ǹ� �ϴ� �� �ϴ�.
		*/
		f2(Widget::MinVals);
		fwd2(Widget::MinVals);
		
		/*
			�ߺ������ �Լ� �̸��� ���ø� �̸�

			�Լ� ���ø������� processVal �� �Ѱ��� �� ���� ���� �Ͼ���� �����ؾ� �Ѵ�.
			processVal �� ���� �����Ϸ����� �ν��ϱ� ���� �̸����� ��, � ������ ���� ���� �ƴϴ�.
			���� ���ø����� �����߷п� ���� ������ �Ͼ�� �ʰ� �����Ѵ�.

			�̸� �ذ��ϴ� ����� ���� �̹� ��޵Ǿ� �ִ�. ������ �˷��ָ� �ȴ�.
		*/
		f3(processVal);
		//fwd3(processVal);
		using ProcessFuncType = int(*)(int);
		fwd3(static_cast<ProcessFuncType>(processVal));

		return 0;

		/*
			��Ʈ�ʵ�

			c++ ǥ���� non-const ������ ����� ��Ʈ�ʵ忡 ������ �ʾƾ� �Ѵٰ� ��õǾ� �ִ�.
			��Ʈ �ʵ�� �ᱹ �����ε�, ������ ��Ʈ�ʵ带 ����Ű�� ������ ���� �����̴�.
			
			�̿� ���� �ذ�å ���� ������ ���� �ִ�.
			������ ��Ʈ�ʵ带 ����Ű�� ������ �����Ƿ� �׳� ��Ʈ�ʵ尪�� ����� ���� ��ü�� �־��ָ� �ȴ�.
		*/
		IPv4Header		header;
		f2(header.totalLength);
		//fwd2(header.totalLength);	

		auto length = static_cast<uint16_t>(header.totalLength);
		fwd2(length);
	}
};

/*
	�Ϻ� ������ ���ø� ���� ������ �����ϰų� Ʋ�� ������ �������� �� �����Ѵ�.

	�μ��� �߰�ȣ �ʱ�ġ�̰ų� 0 �Ǵ� NULL �� ǥ���� �� ������, ���� �� ���� static const �� constexpr �ڷ� ���,
	���ø� �� �ߺ������ �Լ� �̸�, ��Ʈ�ʵ��̸� �Ϻ� ������ �����Ѵ�.
*/