#pragma once

#include <functional>
#include <memory>


/*********************************************************
raw pointer �� ����� �۰� ����� ���� ��Ȳ�̶��, std::unique_ptr ���� �׷� ���� ���� Ȯ���ϴ�.

std::unique_ptr �� ������ ������(exclusive ownership) �ǹ̷��� ü���ϰ� �ִ�.
null �� �ƴ� std::unique_ptr �� �׻� �ڽ��� ����Ű�� ��ü�� �����Ѵ�.
std::unique_ptr �� �̵��ϸ� �������� ���� �����Ϳ��� ��� �����ͷ� �Ű�����.
�̶� ���� �����ʹ� null �� �����ȴ�.
std::unique_ptr �� ����� ������ �ʴ´�.
�׷� �ǹ̿��� std::unique_ptr �� �̵� ���� ����(move only type)�̴�.

std::unique_ptr �� ���� ���� �뵵 �� �ϳ���, ���� ����(hierarchy) ����
��ü�� �����ϴ� ���丮 �Լ��� ��ȯ �������� ���̴� ���̴�.
**********************************************************/

using namespace std;


class Investment {};
class Stock : public Investment {};
class Bond : public Investment {};
class RealEstate : public Investment {};

auto delInvmt = [](Investment* pInvestment)
{
	// custom action
	// ex) makeLogEntry();
	delete pInvestment;
};
/*********************************************************
��ȯ���� ������ �����ϹǷ� auto �� ��ü�ϴ� ���� �ξ� �����ϴ�.

raw pointer �� std::unique_ptr �� �����ϴ� ������ �����ϵ��� �ʴ´�.
�׷� ������ ����Ѵٸ�, raw pointer ���� smart pointer ���� �Ϲ����� ��ȯ�� �����ϱ� �����̴�.
�׷� �Ϲ����� ��ȯ���� ������ �����Ƿ�, c++11 ��  smart pointer ���� �׷� ��ȯ�� �����Ѵ�.
�� ������ �Ʒ� �ڵ忡���� new �� ������ ��ü�� �������� pInv �� �ο��ϱ� ���� reset �� ȣ���Ͽ���.
**********************************************************/
template<typename T>
auto	// std::unique_ptr<Investment, decltype(delInvmt)>
makeInvestment(T&& param)
{
	std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);

	if ( true /* stock �� �����ؾ� �ϴ� ��� */)
	{
		pInv.reset(new Stock());
	}
	else if ( false /* Bond �� �����ؾ� �ϴ� ��� */)
	{
		pInv.reset(new Bond());
	}
	else if ( false /* RealEstate �� �����ؾ� �ϴ� ��� */)
	{
		pInv.reset(new RealEstate());
	}

	return pInv;
}

class chapter18 : public chapter
{
	
	virtual int chapterMain()
	{
		/* 
			���丮 �Լ��� �ڽ��� ������ ��ü�� ȣ���ڰ� ���������� �����Ϸ��� ������,
			�ƴϸ� �������� �����ϰ��� �ϴ���(std::shared_ptr �� �ش�) �̸� �� �� ����.
			���͸� �Լ��� unique_ptr �� ��ȯ�Ѵٸ� ȣ���ڴ� �����ϰ� �ڽ��� �뵵�� �°�
			��ȯ�� �� �ִ� ������ �����.
		*/ 
		std::shared_ptr<Investment> sp = makeInvestment<int>(0);

		return 0;
	}
};

/*
	std::unique_ptr �� ���� ������ �ǹ̷��� ���� �ڿ��� ������ ����, �۰� ���� �̵� ���� �������̴�.

	�⺻������ �ڿ� �ı��� delete �� ���� �Ͼ��, Ŀ���� �����ڸ� ������ ���� �ִ�.
	���� �ִ� �����ڳ� �Լ� �����͸� ����ϸ� std::unique_ptr ��ü�� ũ�Ⱑ Ŀ����.

	std::unique_ptr �� std::shared_ptr �� �ս��� ��ȯ�� �� �ִ�.
*/