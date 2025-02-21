#pragma once

#include <functional>
#include <memory>
#include <mutex>

/*********************************************************
����ȭ�ؾ� �� ���� ��ü�� �ϳ��� ��쿡�� std::atomic �� Ȱ���Ͽ� ����ȭ ����������
�� �̻��̶�� mutex �� ��� �Ѵ�.

mutex �� ����, atomic �� ����, ����ȭ ��ü�� �����ϰ� �Ǹ� ��ü�� �̵�/����� �� �� ���ٴ� ���� �˾Ƶ���. 
**********************************************************/

using namespace std;

class chapter16 : public chapter
{
	class Polynomial
	{
	public:
		using RootsType = std::vector<double>;

		RootsType roots1() const
		{
			if (false == rootsAreValid)
			{
				// calcurate roots values
				// rootVals = ...;
				rootsAreValid = true;
			}

			return rootVals;
		}

		RootsType roots2() const
		{
			std::lock_guard<std::mutex> scopeLock(m);

			if (false == rootsAreValid)
			{
				// calcurate roots values
				// rootVals = ...;
				rootsAreValid = true;
			}

			return rootVals;
		}

	private:
		mutable std::mutex m;
		mutable bool rootsAreValid{ false };
		mutable RootsType rootVals{};
	};

	virtual int chapterMain()
	{
		Polynomial	fomulars;

		// roots �Լ��� const �̱� �ϳ�, ���������� ĳ�� ������ �ϸ鼭 ���� ����� �����Ų��.
		// multi-thread safe ���� �ʴ�.
		Polynomial::RootsType result1 = fomulars.roots1();

		// ���������� mutex �� ����Ͽ� multi-thread safe �ϴ�
		Polynomial::RootsType result2 = fomulars.roots2();

		return 0;
	}
};

/*
	������ ���ƿ��� ������ ���� ���� Ȯ���� ��찡 �ƴ϶��, const ��� �Լ��� �����忡 �����ϰ� �ۼ��϶�.

	std::atomic ������ ���ؽ��� ���� ���ɻ��� ������ ������,. �ϳ��� ���� �Ǵ� �޸� ��Ҹ� �ٷ� ���� �����ϴ�.
*/