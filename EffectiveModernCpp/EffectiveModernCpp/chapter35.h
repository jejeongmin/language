#pragma once

#include <iostream>
#include <functional>
#include <future>

/*********************************************************
thread ��� ó�������� ���ܰ� �߻��ϸ� terminate �Ǵ� �Ϳ� ����
task ��� ó�������� ���ܰ� �߻��ϸ� future ��ü�� ���� �޾ƿ� �� �ִ�.
**********************************************************/

using namespace std;

class chapter35 : public chapter
{
	static int	doAsyncWork()
	{
		return 0;
	}
	
	virtual int chapterMain()
	{
		// thread-based
		std::thread	t(doAsyncWork);

		// task-based
		auto fut = std::async(doAsyncWork);

		// get �� ���� ������ �񵿱� �Լ��� ���ϰ��� ���� �� �ִ�.
		// future ��ü�� get(), wait() �� �����ϸ� ����� �ʿ��� �����忡�� async �Լ��� �����ϰ� �ȴ�.
		// �� �� �߻��ϵ�, ������ ���踦 �����ִ� Ư���̴�.
		int result = fut.get();

		return 0;
	}
};

/*
	std::thread API ������ �񵿱������� ����� �Լ��� ��ȯ���� ���� ���� �� ������, ���� �׷� �Լ��� ���ܸ� ������ ���α׷��� ����ȴ�.

	������ ��� ���α׷��ֿ����� ������ ��, ���ٱ���, ���� ����ȭ, �� �÷��������� ������ ���ڰ� ���� ó���ؾ� �Ѵ�.

	std::async �� �⺻ �õ� ��ħ�� �̿��� ���� ��� ���α׷����� �׷� ��κ��� ������ �˾Ƽ� ó�����ش�.
*/