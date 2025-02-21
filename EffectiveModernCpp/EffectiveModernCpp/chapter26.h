#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
������ ���� ������ ���� ���ø� �Լ���, �����ø� �Լ��� �����ε��� �Ծ���� �� �ִٴ� ��
�����ֱ� ���� �����̴�.
å������ �°�(short -> int ) �� ���� �����ε����� ���ø� �Ű� ���� ��ġ�� ���� �����ε���
�� �켱 ������ �������� ���� �������� ���׸� �����ְ� �;��� �� �ѵ�,
VS 2017 ������ ������ �ǵ���� ������� �ʴ´�.

������ ���ø� �Լ��� �����ø� �Լ��� ������ ���� �������� �ߺ�����Ǿ� ���� ����
�����ø� �Լ��� �켱�Ѵٴ� ��Ģ ���� ���� �ʴ´�.

--->

�Լ� �̸� ���� Ÿ������ �߸��Ǿ �����ε��� ���� �ʾҴ� ���̾��ٴ� �� �ڴʰ� �߰�...
�� ���� �д� ����, �̷��� �����ϰ� �����ε��� ó���� �ٿ��� �����ε��� ������� ���ƾ���. ��� ������ ��� �ߴµ�
�����ε��� ���� �ʰ�, �Լ� �̸��� �޸� �ؼ� ó���� ���� �Լ� �̸��� ���� Ȯ���ϰ� �ٸ���
- postfix �� ��Ȯ�ϰ� �ǵ��� ���̹��Ѵٴ��� - �������� �Ѵٴ� ������ ����.
**********************************************************/

using namespace std;

class chapter26 : public chapter
{
	std::vector<std::string>	names;

	template<typename T>
	void logAndAdd(T&& name)
	{
		std::cout << "log and add" << std::endl;
		names.push_back(std::forward<T>(name));
	}

	std::string nameFromIdx(int idx)
	{
		return "";
	}

	void logAndAdd(int idx)
	{
		std::cout << "log and add" << std::endl;
		names.push_back( nameFromIdx(idx) );
	}

	void logAndAdd(std::string value)
	{
		std::cout << "log and add" << std::endl;
		names.push_back(value);
	}

	virtual int chapterMain()
	{
		std::string petName("Darla");

		logAndAdd(petName);
		logAndAdd(std::string("Persephone"));
		logAndAdd("Patty Dog");

		int value = 22;

		logAndAdd(22);

		return 0;
	}
};

/*
	���� ������ ���� �ߺ������ ���� �׻� ���� ���� �ߺ����� ������ ���󺸴� ���� ȣ��Ǵ� ��Ȳ���� �̾�����.

	�Ϻ� ���� �����ڵ��� Ư���� ������ ����. �׷� �����ڴ� ��ü�� �� const �ް��� ���� ���� �����ں��� �� ���� �����̸�,
	��� Ŭ���� ���� �� �̵� �����ڵ鿡 ���� �Ļ� Ŭ������ ȣ����� ����ç �� �ֱ� �����̴�.
*/