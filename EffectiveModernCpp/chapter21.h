#pragma once

#include <functional>
#include <memory>


/*********************************************************
**********************************************************/

using namespace std;

class chapter21 : public chapter
{
	class Widget
	{
	};

	void processedWidgets(std::shared_ptr<Widget> spw, int priority)
	{
	}

	int computePriority()
	{
		// occur exception
		return 0;
	}

	virtual int chapterMain()
	{
		std::shared_ptr<Widget> spw2(new Widget);	// Widget Ÿ���� �� �� ����ؾ� �ϰ�, Ÿ���� �絵 �� ����.
		auto spw1(make_shared<Widget>());			// �� ��Ŀ� ���� �ξ� ª�� ����ϴ�.

		processedWidgets(std::shared_ptr<Widget>(new Widget), computePriority());	// �Ҵ��� ����Ǿ����� ���� shared_ptr ������ ���� �ʾ��� ��, ���ܰ� �߻��ϸ� �ڿ� ����
		processedWidgets(std::make_shared<Widget>(), computePriority());			// �ڿ� ���� ������ ����.

		return 0;
	}
};

/*
new �� ���� ��뿡 ����, make �Լ��� ����ϸ� �ҽ� �ڵ� �ߺ��� ������ ��������, ���� �������� ���ǰ�, std::make_shared �� std::allocate_shared �� ��� �� �۰� ���� �ڵ尡 ����ȴ�.

make �Լ��� ����� �Ұ��� �Ǵ� �������� ���δ� Ŀ���� �����ڸ� �����ؾ� �ϴ� ���� �߰�ȣ �ʱ�ġ�� �����ؾ� �ϴ� ��찡 �ִ�.

std::shared_ptr �� ���ؼ� make �Լ��� ������ ��찡 �� �ִµ�, �� ���� ���� ���ڸ�
	1) Ŀ���� �޸� ���� ����� ���� Ŭ������ �ٷ�� ����
	2) �޸𸮰� �˳����� ���� �ý��ۿ��� ū ��ü�� ���� �ٷ��� �ϰ� std::weak_ptr �麸�� ���� ��Ƴ��� ����̴�.
*/