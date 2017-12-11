#pragma once

#include <functional>
#include <memory>
#include <mutex>


/*********************************************************
���� �ڵ忡�� ������ lockAndCall ���ø� �Լ��� ���� �Լ��� ����
�ּҰ� �ʿ��ϱ� ������ f1, f2, f3 �� static ���� �����Ͽ���.
**********************************************************/

template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
{
	using MuxGuard = std::lock_guard<MuxType>;

	MuxGuard	g(mutex);

	return func(ptr);
}

class chapter08 : public chapter
{
	class Widget
	{
	};

	static int f1(std::shared_ptr<Widget> spw)
	{
		return 0;
	}

	static double f2(std::unique_ptr<Widget> upw)
	{
		return 0.f;
	}

	static bool	f3(Widget* pw)
	{
		return true;
	}

	virtual int chapterMain()
	{
		std::mutex	f1m, f2m, f3m;

		using MuxGuard = std::lock_guard<std::mutex>;

		{
			MuxGuard	g(f1m);
			auto result = f1(0);		// 0 �� �� �����ͷν� f1 �� ����

			//auto result1 = lockAndCall(f1, f1m, 0);	// 0�� shared_ptr<Widget> �� ������ �� ����.
		}

		{
			MuxGuard	g(f2m);
			auto result = f2(NULL);		// NULL �� �� �����ͷν� f1 �� ����
		
			//auto result2 = lockAndCall(f2, f2m, NULL); // NULL �� unique_ptr<Widget> �� ������ �� ����.
		}

		{
			MuxGuard	g(f3m);
			auto result = f3(nullptr);	// nullptr �� �� �����ͷν� f1 �� ����

			auto result3 = lockAndCall(f3, f3m, nullptr);
		}

		return 0;
	}
};

/*
	0 �� NULL ���� nullptr �� ��ȣ�϶�
	
	�������İ� ������ ���Ŀ� ���� �ߺ����縦 ���϶�.
*/