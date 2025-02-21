#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
	���� ��� Reactor ������ ������ ��,
	�Ϲ����� event / wait ������� �����ϰ� �ȴ� ( Normalway �Լ� )

	�׷��� future/promise ��Ŀ������ Ȱ���ϸ� 1ȸ�� �ܹ߼� ���� ��Ŀ�
	���ؼ� ������ �� �ִ�.
**********************************************************/

using namespace std;

class chapter39 : public chapter
{
	std::condition_variable cv;
	std::mutex	m;

	bool flag = false;

	void NormalWay()
	{
		// ���⼭ Ư�� �̺�Ʈ�� ĳġ�� ��

		// ó�� �Լ��� �˷��ش�.
		{
			std::lock_guard<std::mutex> g(m);
			flag = true;
		}
		cv.notify_one();

		// ������ ���� ���� �̺�Ʈ�� ó���Ѵ�.
		{
			std::unique_lock<std::mutex>	lk(m);
			cv.wait(lk, [&] { return flag;  });	// std::conditional_variable �� ���� signal �Ȱ��� �˻��� �� �ִ� ������ �����Ѵ�.
		}
	}

	std::promise<void>	p;
	void react() {};
	void NewWay()			// chapter 37 �� RAII ��ü�� Ȱ���ϸ� �� �� �����ϰ� thread ������ ����
	{
		std::thread t([&]
		{
			p.get_future().wait();		// signal �ɶ����� ���
			react();
		});

		p.set_value();		// signal �� �ش�.

		t.join();			// react �� �Ϸ�� ������ ���
	}

	virtual int chapterMain()
	{
		return 0;
	}
};

/*
	������ ��� ����� ������ ��, ���� ���� ��� ���迡�� ������ ���ؽ��� �ʿ��ϰ�,
	���� ������ ���� ������ ���� ������ ������ ������, ����� ������ �߻��ߴ����� ���� ������ �ٽ� Ȯ���ؾ� �Ѵ�.

	�÷��� ��� ���踦 ����ϸ� �׷� �������� ������, ��� �����̾ƴ϶� ������ �Ͼ�ٴ� ������ �ִ�.

	���� ������ �÷��׸� ������ �� ������, �׷� ������ �̿��� ��� ��Ŀ������ �ʿ� �̻����� �����ϴ�.

	std::promise �� �̷� ��ü�� ����ϸ� �̷��� ���������� ���� �� ������, �׷� ���� ����� ���� ���¿�
	�� �޸𸮸� ����ϸ�, �ܹ߼� ��Ÿ� �����ϴ�.
*/