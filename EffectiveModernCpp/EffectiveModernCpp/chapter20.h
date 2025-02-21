#pragma once

#include <functional>
#include <memory>


/*********************************************************
weak_ptr �� �ڽ��� �����ϴ� �� ���� std::shared_ptr �� ����Ű�� �Ͱ� ������ ��ü��
����Ű��, �� ��ü�� ���� Ƚ������ ������ ���� �ʴ´�.


ȿ���� �鿡�� std::weak_ptr �� std::shared_ptr �� ���������� �����ϴ�.
std::weak_ptr ��ü�� �� ũ�Ⱑ std::shared_ptr ��ü�� ������, std::shared_ptr �� ����ϴ� �Ͱ� ����
������� ����ϸ�, �����̳� �ı�, ���� ���� ���꿡 ������ ���� Ƚ�� ������ �����Ѵ�.
�տ��� ����ߵ���, ���� ��Ͽ��� '�� ����' ���� Ƚ���� ������ �װ��� �ٷ� std::weak_ptr �� �����ϴ� ����Ƚ���̴�.
**********************************************************/

using namespace std;

class chapter20 : public chapter
{
	class Widget
	{
	};

	virtual int chapterMain()
	{
		auto spw = std::make_shared<Widget>();	// ref count of spw is 1
		std::weak_ptr<Widget> wpw(spw);			// ref count of spw is still 1

		cout << "weak pointer expired : " << wpw.expired() << endl;

		auto spw1 = wpw.lock();					// ���� expired �̸� null �� ��ȯ
		std::shared_ptr<Widget> spw3(wpw);		// ���� expired �̸� ���ܸ� ��ȯ

		spw = nullptr;							// ref count of spw is 0

		cout << "weak pointer expired : " << wpw.expired() << endl;

		return 0;
	}
};

/*
	std::shared_ptr ó�� �۵��ϵ�, ����� ���� ���� �ִ� �����Ͱ� �ʿ��ϸ� std::weak_ptr �� ����϶�

	std::weak_ptr �� �������� �뵵�δ� ĳ��, ������ ���, �׸��� std::shared_ptr ��ȯ �� ������ �ִ�.
*/