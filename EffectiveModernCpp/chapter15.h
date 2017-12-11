#pragma once

#include <functional>
#include <memory>

/*********************************************************

**********************************************************/

using namespace std;

class chapter15 : public chapter
{
	// c++11 ������ ���� ���� ������ �ϳ����� �Ѵ�. �׸��� �ݵ�� void �� ������ literal ������ ��ȯ�ؾ� �Ѵ�.
	// �Ʒ� �Լ��� ���� ? �����ڿ� ��͸� �̿��� return �� �� �ٷ� �Լ��� ���������� �� �� �ִ�.
	constexpr int pow(int base, int exp) noexcept
	{
		return (exp == 0 ? 1 : base * pow(base, exp - 1));
	}

	// c++ 14 ������ c++11 ������ ������ ��� �������ٰ� å�� �Ǿ� �ִµ�,
	// ����� ������ vs2015 ������ �����ϵ��� �ʴ´�.
	/*
	constexpr int pow(int base, int exp) noexcept
	{
		int result = 1;
		for (int i = 0; i < exp; i++)	result *= base;
		return result;
	}
	*/

	class Point
	{
	public:
		constexpr Point(double x = 0, double y = 0) noexcept
			: _x(x), _y(y)
		{}

		constexpr double x() const noexcept { return _x; }
		constexpr double y() const noexcept { return _y; }

		// c++14 ������ constexpr �� void ��ȯ�� �����ϴٰ� �Ǿ� �ִµ�, vs2015 ���� �ȵǳ�.
		/*
		constexpr void x(double x) noexcept { _x = x; }
		constexpr void y(double y) noexcept { _y = y; }
		*/

		constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
		{
			return{ (p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2 };
		}

	private:
		double	_x, _y;
	};

	virtual int chapterMain()
	{
		constexpr auto arraySize = 10;	// OK, 10�� Ȯ���� ������ ���� ���
		std::array<int, arraySize> data;

		constexpr Point p1(9.4, 27.7);

		return 0;
	}
};

/*
	constexpr ��ü�� const �̸�, ������ ���߿� �˷����� ����� �ʱ�ȭ�ȴ�.

	constexpr �Լ��� �� ���� ������ ���߿� �˷����� �μ���� ȣ���ϴ� ��쿡�� ������ ���� ����� �����Ѵ�.

	constexpr ��ü�� �Լ��� ��constexpr ��ü�� �Լ����� �������� ���ƿ��� ����� �� �ִ�.

	constexpr �� ��ü�� �Լ� �������̽��� �Ϻ��̴�.
*/