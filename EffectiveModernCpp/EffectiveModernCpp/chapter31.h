#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
**********************************************************/

using namespace std;

class chapter31 : public chapter
{
	using FilterContainer = std::vector<std::function<bool(int)>>;

	FilterContainer	_filters;
	int				_divisor = 5;

	int computeDivisor()
	{
		return 5;	// temporary value
	}

	/*
		�Ʒ� �Լ��� ������ �ִ�.
		���ٴ� �������� divisor �� �����ϴµ�, �� ������ addDivisorFilter �Լ��� ��ȯ�Ǹ� �� �̻� �������� �ʴ´�.
	*/
	void addDivisorFilter1()
	{
		auto divisor = computeDivisor();

		_filters.emplace_back(
			[&](int value) { return value % divisor == 0; }
		);
	}

	/*
		�Ʒ� �Լ��� ���� ���ο��� ����� ������ ��������� ĸ���Ͽ���.
		addDivisorFilter1() �Լ��� ���� ������ ����������, ǥ������ ��ȿ���� divisor �� ���� �����Ѵٴ� ���� ��Ȯ�� ��Ÿ���ٴ� ������ �ִ�.
	*/
	void addDivisorFilter2()
	{
		auto divisor = computeDivisor();

		_filters.emplace_back(
			[&divisor](int value) { return value % divisor == 0; }
		);
	}

	/*
		������ ����ϴ� divisor �� ���� ������ ĸ�ĸ�带 [by reference] �� �ƴ�, [by value]�� �ϸ� �ذ�ȴ�.
	*/
	void addDivisorFilter3()
	{
		auto divisor = computeDivisor();

		_filters.emplace_back(
			[=](int value) { return value % divisor == 0; }
		);
	}

	/*
		ĸ�Ĵ� ���� ���ٰ� ������ ���� �ȿ��� ���̴�, static �� �ƴ� ���� ����(�Ű����� ����)���� ����ȴ�.
		divisor �� ���� ������ �ƴ� Ŭ������ �� �ڷ� ����̹Ƿ� �������� �� ����.
		�� ������ �ڷ� ����� ���ٿ��� ����� ���, this �� �Ϲ������� ���̱� �����̴�.
		���ٰ� Ŭ���� �ȿ� �������ϴ� ���� _divisor �� �ƴ�, Chapter31 �� this �������̴�.
		�� ���� �����Ѵٸ� �� ���ٿ��� ������� Ŭ������ ��ȿ���� �ش� Widget ��ü�� ���� ���� ���ѵȴٴ� ���� ������ �� ���� ���̴�.
	*/
	void addDivisorFilter4()
	{
		/*_filters.emplace_back(	// ������� ����.
			[](int value) { return value % _divisor == 0; }
		);*/

		_filters.emplace_back(
			[=](int value) { return value % _divisor == 0; }
		);

		// �ٷ� ���� �Լ��� �����Ϸ��� ������ ���� �ٶ󺻴�.
		auto currentObjectPtr = this;
		_filters.emplace_back(
			[currentObjectPtr](int value) { return value % currentObjectPtr->_divisor == 0; }
		);
	}

	/*
		addDivisorFilter4 �� ������ ���� ����ϰ� ������ ������ ������ ����.
		�׳� [by value] �� �̿��ϵ��� �ణ�� �����ϸ� �ȴ�.
	*/
	void addDivisorFilter5()
	{
		auto divisor = _divisor;

		_filters.emplace_back(
			[=](int value) { return value % divisor == 0; }
		);
	}

	/*
		�Ʒ� �Լ��� static ���� ����� divisor �� �⺻�� ĸ�� �Ǵ� ���� ���ظ� ��� �Ѵ�.
		�� ���ٴ� ��� �ƹ� �͵� ������ ���� �ʴ´�.
		������ �� ���ٴ� divisor �� ������ �������� �Ͱ� ������ �̴� �⺻�� ���İ� ���ϴ� �ٿ� ���������� ����� �ȴ�.

		�� ��쿡�� �ذ�å�� ����ϴ�.
		���� ������ ���� �����ؼ� �� ���� ������ �⺻�� ĸ�ķ� �ѱ�� �ȴ�.
	*/
	void addDivisorFilter6()
	{
		static auto divisor = computeDivisor();

		_filters.emplace_back(
			[=](int value) { return value % divisor == 0; }
		);

		++divisor;
	}

	virtual int chapterMain()
	{
		return 0;
	}
};

/*
	�⺻ ���� ĸ�Ĵ� ������ ����� ���� ������ �ִ�.

	�⺻ �� ������ ������(Ư�� this)�� ����� ���� �� ������, ���ٰ� �ڱ� �ϰ����̶�� ���ظ� �θ� �� �ִ�.
*/