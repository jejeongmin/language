#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <vector>

/*********************************************************	
**********************************************************/

using namespace std;

class chapter41 : public chapter
{
	class WidgetForOverload
	{
	public:
		void addName(const std::string& newName)
		{
			names.push_back(newName);
		}

		void addName(const std::string&& newName)
		{
			names.push_back(std::move(newName));
		}

	private:
		std::vector<std::string> names;
	};

	template<typename T>
	class WidgetForGeneralRef
	{
	public:
		void addName(T&& newName)
		{
			names.push_back(std::forward<T>(newName));
		}

	private:
		std::vector<T> names;
	};

	class WidgetForValue
	{
	public:
		void addName(const std::string newName)
		{
			names.push_back(std::move(newName));
		}

		/*
			�� ������ �׻� ����Ǵ� �Ű� ������ ���ؼ��� ����϶�� �̾߱�� ������ ����.
			�Ű������� �ⲯ ���� �����ؼ� �����ߴ���, �ᱹ���� � ���ǿ� ���ؼ� ������� �ʰ� �Ǵ� ��쿡�� ���� ����� �̾߱�.
		*/
		void addNameNotRecommended(const std::string newName)
		{
			int	minLength = 8, maxLength = 128;

			if (newName.length() < minLength && newName.length() > maxLength)
				return;

			names.push_back(std::move(newName));
		}

	private:
		std::vector<std::string> names;
	};

	virtual int chapterMain()
	{
		return 0;
	}
};

/*
	�̵��� �����ϰ� �׻� ����Ǵ� ���� ���� �Ű������� ���ؼ��� �� ������ ���� ���޸�ŭ�̳�
	ȿ�����̰�, �����ϱⰡ ����, ����Ǵ� ���� �ڵ��� ũ�⵵ �۴�.

	�ް� �μ��� ��� �� ����(��, ���� ����) ������ �̵� ������ ���� ���� ������
	���� �������� �ξ� ��� ���ɼ��� �ִ�.
	-> �̰� vector �� ���� ���ο� �������� ���� (���� �޸� ����) -> ( ���ο� �޸� �Ҵ� ) ��
	������ ������ �Ͼ�� ��츦 ���Ѵ�. �� ���� �Ű� ���� �̵� ��İ� Ư�� �ڷᱸ���� ���Ҵ� �����
	ȭ���ۿ��� ������ �߻��ϴ� �̽��ε�, å���� �Ű� ���� �̵��� Ư�� ���̽��� �����ϱ⿡��
	�����μ� �������ϴ�. å �÷� �����.
	41��� 42���� ��� ȭ��� ������ �ᵵ �������.

	�� ���޿����� �߸� ������ �߻��� �� �����Ƿ�, �Ϲ������� ��� Ŭ���� �Ű� ���� ���Ŀ�
	���ؼ��� �� ������ �������� �ʴ�.
	-> ��ü ���������� ���� �߻��� �� �ִ� ������ ��ư� �����س���...
*/