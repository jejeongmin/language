#pragma once

#include <functional>
#include <memory>

/*********************************************************
	delete �� �̿��ϸ� member function �� �ƴ϶� �Ϲ� function �� ������ �� �ִ�.
	���� �ǹ̷� �����ε� access level �� ���� �����ϴ� �� �ƴ϶�
	���� delete ��� �ǹ̸� �ο��� ������ ������ �� �ִ�.

	��.. ������ �� �� �׽�Ʈ�غ��� �Լ��� delete �� �����ϸ�, �ش� �Լ��� ���� �ڵ嵵 �����ؾ� �ϴµ�,
	������ �Լ� ���� �ڵ带 �����ϸ�, ���� �� ��ŷ ������ ���� �� �Լ��� ��� ���Ѵ�.
	delete �� ���� ��ŷ Ÿ���� ������ ������ Ÿ���� ������ �ű��, delete ��� �ǹ̸� �ο��� �ų�.
	�� ���� ����̴µ�..
	������ ���� �ڵ嵵 ���� ��.. �׳� delete ������ ���� ���������� ���ݾ�..
**********************************************************/

class chapter11 : public chapter
{
	class Widget
	{
	public:
		void	public_test() = delete;
	private:
		void	private_test() = delete;

		friend class chapter11;
	};

	void isLucky(int number);
	void isLucky(char number) = delete;	
	void isLucky(bool number) = delete;
	void isLucky(double number) = delete;

	// ������ �Լ��� ������ �� �ִ� ������ ������ ��ġ ���� ���ø��� �ν��Ͻ�ȭ�� ���� �� �ִٴ� ������ ���δ�.
	template<typename T>
	void processPointer(T* ptr);

	template<typename T>
	void processPointer(void* ptr) = delete;
	template<typename T>
	void processPointer(const void* ptr) = delete;
	template<typename T>
	void processPointer(char* ptr) = delete;
	template<typename T>
	void processPointer(const char* ptr) = delete;
	
	virtual int chapterMain()
	{
		Widget	test;

		//test.public_test();
		//test.private_test();
		
		isLucky(10);
		//isLucky('a');
		//isLucky(true);
		//isLucky(3.5);

		return 0;
	}
};

void chapter11::isLucky(int number)
{
}

//void chapter11::isLucky(char number)
//{
//}

//void chapter11::isLucky(bool number)
//{
//}
//
//void chapter11::isLucky(double number)
//{
//}

/*
	���ǵ��� ���� ����� �Լ����� ������ �Լ��� ��ȣ�϶�.

	���� �Լ��� ���ø� �ν��Ͻ��� ����� �� � �Լ��� ������ �� �ִ�.
*/