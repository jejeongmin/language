#pragma once

#include <functional>
#include <memory>

/*********************************************************
**********************************************************/

class chapter13 : public chapter
{
	// �� �ڵ�� ���� �Ϲ����� �ڵ�������, �����ϰ� �ǹ̷����� ���鿡�� ������ �ʿ��ϴ�.
	// ���� iterator �� ����Ű�� ���� ���� �������� �ʾ������� const_iterator �� ������� �ʾҴ�.
	void cpp_98()
	{
		std::vector<int> values;
		std::vector<int>::iterator it = std::find(values.begin(), values.end(), 1983);
		values.insert(it, 1998);
	}

	// ���� �ڵ带 ��Ȯ�ϰ� �����ϸ� �Ʒ��� ����.
	void cpp_14()
	{
		std::vector<int> values;
		auto it = std::find(values.cbegin(), values.cend(), 1983);
		values.insert(it, 1998);
	}
	
	virtual int chapterMain()
	{
		return 0;
	}
};

/*
	iterator ���� const_iterator �� ��ȣ�϶�.

	�ִ��� �Ϲ����� �ڵ忡���� begin, end, rbegin ���� ���� �������� �ش� ��� �Լ��麸�� ��ȣ�϶�.
*/