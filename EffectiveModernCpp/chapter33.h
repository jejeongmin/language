#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
**********************************************************/

using namespace std;

class chapter33 : public chapter
{
	class Widget
	{
	public:
		bool	isValidated() const	{ return true;  }
		bool	isArchived() const { return true;	}
	};

	template<typename T>
	T normalize(T x)
	{
		return x;
	}

	virtual int chapterMain()
	{
		// c++14 ���� ���� ������ ����� �Ϲ��� ����, �� �Ű����� ���� auto �� ����ϴ� �����̴�.
		auto f1 = [&](auto x) { return normalize(x); };

		// ���� �ڵ带 ����� �����ϰ� �Ϸ���, ���ٰ� x �� normalize �� �Ϻ��ϰ� �����ؾ� �Ѵ�.
		// �׷����� �ڵ忡�� �ٲ� ���� �� �����ε�, ù°�� x �� ���� �����̾�� �ϰ�, ��°�� x �� std::forward �� ���ؼ� normalize �� �����ؾ� �Ѵ�.
		// auto f2 = [&](auto&& x) { return normalize( std::forward<???>(x)); };

		// �� ���ٿ� �־����μ��� �ް�����, ������������ �Ű����� x �� ������ ������ ���� �� �� �ִ�.
		// �׷��� ���翡 ����� �� �ִ� ������ �ٷ� decltype �̴�.
		auto f3 = [&](auto&& x) { return normalize(std::forward<decltype(x)>(x)); };

		// c++14 �� ���ٴ� �������μ��� �����Ѵ�.
		auto f4 = [&](auto&&... xs) { return normalize(std::forward<decltype(x)>(xs)...); };

		return 0;
	}
};

/*
	std::forward �� ���ؼ� ���޵� auto&& �Ű��������� decltype �� ����϶�
*/