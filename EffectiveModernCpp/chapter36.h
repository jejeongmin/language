#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
	TLS ( Thread Local Storage ) ��.

	thread �� ������ �̾߱��ϴ� ���� �ƴϴ�.
	���� thread �� ����, ����, ���� ���� ���� �����͸� �����ϴ� ��ġ�� �Ҵ��ϴ� ����� ���Ѵ�
	
	https://msdn.microsoft.com/en-us/library/windows/desktop/ms686749(v=vs.85).aspx
**********************************************************/

using namespace std;

class chapter36 : public chapter
{
	class Widget
	{};

	static int	doAsyncWork()
	{
		std::this_thread::sleep_for(100ms);
		return 0;
	}

	/*
		fut ��  �⺻ �õ� ��å���� ���� deferred ������ �����ϴ�.
		�ٷ� �Ʒ� ���ѷ��������� fut �� �ּ��� �ѹ��� ����� ���̶�� ( �׸��� ����� ���̶�� )
		������ ��� �ۼ��� �����̴�.
		���� fut �� ������� �ʴ´ٸ� �� �ڵ�� ���ѷ����� ������.
	*/
	void infinity_loop_example()
	{
		auto fut = std::async(doAsyncWork);

		while (std::future_status::ready != fut.wait_for(100ms))
		{
			// to do something
		}
	}

	/*
		wait_for(0s) ȣ���� ����, task �� deferred �Ӽ��� �˾Ƴ� ��,
		���ѷ����� ������ �ʵ��� �ʿ��� ó���� �Ѵ�.
	*/
	void fixed_infinity_loop_example_01()
	{
		auto fut = std::async(doAsyncWork);

		if (std::future_status::deferred == fut.wait_for(0s))
		{
			// fut �� get �̳� wait �� ȣ���ؼ� doAyncWork �� ���������� ȣ���Ѵ�.
		}
		else
		{
			while (std::future_status::ready != fut.wait_for(100ms))
			{
				// to do something
			}
		}
	}

	/*
		������ ���� ����ϰ�, �׸��� ���� �ذ��ϴ� ���� �õ� ��å�� aync �� ����ϴ� ���̴�.
		future ��ü�� ���� ����ȣ���� �ƿ� ��å������ �����ع����� �Ʒ� �ڵ尡 ���ѷ����� ������
		���� ���� �� �ִ�.
	*/
	void fixed_infinity_loop_example_02()
	{
		auto fut = std::async(std::launch::async, doAsyncWork);

		while (std::future_status::ready != fut.wait_for(100ms))
		{
			// to do something
		}
	}

	/*
		��ı ���̾�� ���� �ϴ� �ڵ� ������... Ȥ�� å �ȾƸԱ� ���� ������ �ø���...
		�׳� �⺻��å �ڵ� ���� ª�� Ÿ���� �� ���̸� �Ǵµ�, ���ø��� �̵� �� ���°�...
	*/
	template<typename F, typename... Ts>
	inline auto reallyAsync(F&& f, Ts&&... params)
	{
		return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
	}
	
	virtual int chapterMain()
	{
		// default launch polity �� async �� deferred �� ��� �����ϴ� ���̴�.
		// �Ʒ� �� ȣ���� ������ �õ� ��å�� ������.
		auto fut1 = std::async(doAsyncWork);
		auto fut2 = std::async(std::launch::async | std::launch::deferred,  doAsyncWork);

		return 0;
	}
};

/*
	std::async �� �⺻ �õ� ��ħ�� ������ �񵿱��� ����� ������ ������ ��� ����Ѵ�.

	�׷��� �̷��� ������ ������ thread_local ������ ��Ȯ�Ǽ��� �߻��ϰ�, ������ ����� ������� ���� ���� �ְ�,
	�ð� ���� ��� wait ȣ�⿡ ���� ���α׷� ������ ������ ��ģ��.

	������ �ݵ�� �񵿱������� �����ؾ� �Ѵٸ� std::launch::async �� �����϶�.
*/