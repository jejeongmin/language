#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
	std::thread �� �շ� ���ɼ��� �߿��� ���� �ϳ���, ���� �շ� ������ ��������
	�Ҹ��ڰ� ȣ��Ǹ� ���α׷� ������ ����ȴٴ� ���̴�.
**********************************************************/

using namespace std;

constexpr auto tenMillion = 1'000'000;	// c++14 ������ ����ǥ�� �νĵ�

class chapter37 : public chapter
{
	bool conditionalAreSatisfied() { return true;  }
	void performComputation(std::vector<int>&) {}

	bool doWork1(std::function<bool(int)> filter, int maxVal = tenMillion)
	{
		std::vector<int> goodVals;

		std::thread t([&filter, maxVal, &goodVals]
		{
			for (auto i = 0; i <= maxVal; ++i)
			{
				if (filter(i))
					goodVals.push_back(i);
			}
		});

		// t �� �ڵ��� �̿��� �켱 ���� ����
		// task ��ݿ����� thread handle �� ���� �� ����.
		auto nh = t.native_handle();

		if (conditionalAreSatisfied())
		{
			t.join();
			performComputation(goodVals);
			return true;
		}
		
		// ���� ����� ��� ���� ������ü�� t �� �Ҹ��ڰ� �Ҹ���, ���α׷� ������ ����ȴ�.
		// std::thread �� �Ҹ��ڰ� �Ҹ���ٰ� �ؼ�, ���α׷��� ����Ǵ� ���� ���� ������
		// �̻��� �������� ��������, ����� �ո����� ������ �ִ�.
		// ������ �����ϸ� ��� 272~273p �� �о����.
		// ��ư �׷� ������ �ؼ� ǥ�� ����ȸ�� std::thread ��ü�� ����� �� �� ��ü�� ���ǵ�
		// ���� �ٱ��� ��� ��ο��� �շ� �Ұ������� ����� ���� ���α׷����� å������ �Ͽ���.
		return false;
	}

	/*
		scoped ��ü�� Ư���� �̿��� std::thread �� ���� ���ʿ��� �շ� ������ ���·�
		ó���ϱ� ���� ���۸� �����.
		å������ RAII ( Resource Acquisision Is Initialization ) �̶�� �Ұ��ϰ� �ִ�.
	*/
	class ThreadRAII
	{
	public:
		enum class DtorAction { join, detach };

		ThreadRAII(std::thread&& t, DtorAction a) : _action(a), _t(std::move(t)) {}

		~ThreadRAII()
		{
			// t �� ���� ����Լ��� ȣ���ϱ� ���� �ݵ�� join �������� �˻��ؾ� �Ѵ�.
			// �շ� �Ұ����� thread �� ���� join() �̳� detach() �� �����ϸ� ������ �ൿ�� ������ �����̴�.
			if (_t.joinable())	
			{
				if (DtorAction::join == _action)
					_t.join();
				else
					_t.detach();
			}
		}

		std::thread& get() { return _t; }

	private:
		/*
			��� �ʱ�ȭ�� ���� ������ ������.
			std::thread �� ���� �������� ����� ���� �ǵ��� ���̴�.
			std::thread �� �ʱ�ȭ �ǰ� �ٷ� ����� ���� �ִµ�,
			std::thread �� �ٸ� ��� ����� �ʱ�ȭ�� ���Ŀ� �ʱ�ȭ�ϸ�, �ش� �񵿱� �����尡
			�ٸ� ��� ����� �����ϰ� ������ �� �ֱ� �����̴�.
		*/
		DtorAction	_action;
		std::thread	_t;
	};

	/*
		join Action �� ���ϵ��� �ߴ�.
		detach Action �� ���ϸ� ������ �ൿ�� �߻��� �� �ֱ� �����̴�.
		���� join �� �����̻�, �׸��� �ణ�� ������ �ൿ�� ����������
		�Ҹ��� ȣ��� ���� ���α׷� ����, ������ �ص�, ���� �̻� �߿�����
		�׳��� ���� �̻��� ���� ����.
	*/
	bool doWork2(std::function<bool(int)> filter, int maxVal = tenMillion)
	{
		std::vector<int> goodVals;

		ThreadRAII t(
		std::thread([&filter, maxVal, &goodVals]
		{
			for (auto i = 0; i <= maxVal; ++i)
			{
				if (filter(i))
					goodVals.push_back(i);
			}
		}), ThreadRAII::DtorAction::join);

		auto nh = t.get().native_handle();

		if (conditionalAreSatisfied())
		{
			t.get().join();
			performComputation(goodVals);
			return true;
		}

		return false;
	}
	
	virtual int chapterMain()
	{
		return 0;
	}
};

/*
	��� ��ο���  std::thread �� �շ� �Ұ������� ������.
	�Ҹ� �� join ����� ������ϱ� ����� ���� �̻����� �̾��� �� �ִ�.
	�Ҹ� �� detach ����� ������ϱ� ����� ������ �ൿ���� �̾��� �� �ִ�.
	�ڷ� ��� ��Ͽ��� std::thread ��ü�� ���������� �����϶�.
*/