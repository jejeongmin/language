#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

class Widget6
{};

std::vector<bool> features(const Widget6& w)
{
	std::vector<bool> result;

	return result;
};

/*********************************************************
�������ڸ� ������ ���� �ڵ� ���´� ���ϴ°� ����.

auto someVar = "������ �ʴ�" �븮�� Ŭ���� ������ ǥ����

������� static_cast<> �� Ȱ���ؼ� �븮�� Ŭ���� ������ ��ȯ�� ��������� �巯����
���α׷����� �ǵ��� ��~ Ÿ�� ĳ���� ������ Ÿ������ ���ؼ� ��������� �巯����.

**********************************************************/
class chapter06 : public chapter
{
	virtual int chapterMain()
	{
		Widget6	w;

		// �Ʒ� �ڵ�� ����� �� �۵��Ѵ�.
		{
			bool	highPriority = features(w)[5];
		}

		// �Ʒ� �ڵ�� �� �۵����� �ʴ´�.
		// std::vector<bool> �� [] �����ڴ�, ���� ���ϸ� bool �� ��ȯ�� �Ϲ������� �����ϱ� �ϳ�,
		// auto �� �����ϰ� �Ǹ�, ��������� std::vector<bool>::reference �� ��ȯ�ϰ� �Ǳ� �����̴�.
		// �����Ϸ� ������ ���� �ٸ���, �밳 std::vector<bool>::reference �� bool �� ǥ���ϱ� ���� word ����
		// �� word ���ο��� bool ���� ��� �ִ� bit ���� offset �� ���Ե� ����ü�� ���� �����͸� ��ȯ�ϴµ�
		// auto �� �����Ϳ� ���� �ӽð��� ��ȯ�ϰ� �ǰ�, �ش� ������ ����� ����, �ӽð��� �ı��Ǿ�,
		// dangling pointer �� �ǰ� ����.
		{
			auto	highPriority1 = features(w)[5];

			// �� �ڵ带 ������ �Ʒ� �ڵ�� ������ ����.
			auto	highPriority2 = static_cast<bool>(features(w)[5]);
		}

		return 0;
	}
};

/*
	"������ �ʴ�" �븮�� ���� ������ auto �� �ʱ�ȭ ǥ������ ������ "�߸�" ������ �� �ִ�.
	
	���� ��� �ʱ�ġ ���뱸�� auto �� ���ϴ� ������ �����ϵ��� �����Ѵ�.
*/