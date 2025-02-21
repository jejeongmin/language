#pragma once

#include <functional>
#include <memory>
#include <iostream>
#include <string>

/*********************************************************
�� ���� �����ʹ� �ٸ����� c++ ���� ���� �� ���� ������ ����(?)�ϱ� ���� �ڵ��̴�.

���ܸ� ������ �ʴ´ٴ� ����� ����� �Լ����� - ���ο��� ������������ ȣ���ϴ� �Լ��鵵 ���ܸ� ������ �ʾƾ� �Ѵ�
- noexcept �� ������ �����Ϸ��� ����ȭ�� �� �ֵ��� �ؾ� �Ѵ�.
���� ����� ���� �����ϰ� ������ �����ؼ� noexcept �� ���� �ʿ�� ����. �������� �ڿ�������...
**********************************************************/

using namespace std;

class chapter14 : public chapter
{

	int		mf1(int x)	throw();		// ���ܸ� ������ �ʴ´�. c++98 ���.
	int		mf2(int x)	throw(...);		// ���ܸ� ������.
	int		mf3(int x)	noexcept;		// ���ܸ� ������ �ʴ´�. �����Ϸ� ����ȭ�� ������ ���� ũ��.

	class MyException {};

	class Dummy
	{
	public:
				Dummy(string s) : MyName(s) { PrintMsg("Created Dummy:"); }
				Dummy(const Dummy& other) : MyName(other.MyName) { PrintMsg("Copy created Dummy:"); }
				~Dummy() { PrintMsg("Destroyed Dummy:"); }
		void	PrintMsg(string s) { cout << s << MyName << endl; }
		
	public:
		string	MyName;
		int		level;
	};

	void C(Dummy d, int i)
	{
		cout << "Entering FunctionC" << endl;
		d.MyName = " C";
		throw MyException();

		cout << "Exiting FunctionC" << endl;
	}

	void B(Dummy d, int i)
	{
		cout << "Entering FunctionB" << endl;
		d.MyName = "B";
		C(d, i + 1);
		cout << "Exiting FunctionB" << endl;
	}

	void A(Dummy d, int i)
	{
		cout << "Entering FunctionA" << endl;
		d.MyName = " A";
		//  Dummy* pd = new Dummy("new Dummy"); //Not exception safe!!!  
		B(d, i + 1);
		//   delete pd;   
		cout << "Exiting FunctionA" << endl;
	}

	virtual int chapterMain()
	{
		cout << "Entering main" << endl;
		try
		{
			Dummy d(" M");
			A(d, 1);
		}
		catch (MyException& e)
		{
			cout << "Caught an exception of type: " << typeid(e).name() << endl;
		}

		cout << "Exiting main." << endl;
		char c;
		cin >> c;

		return 0;
	}
};

/*
	noexcept �� �Լ��� �������̽��� �Ϻ��̴�. �̴� ȣ���ڰ� noexcept ���ο� ������ �� ������ ���Ѵ�.

	noexcept �Լ��� �� noexcept �Լ����� ����ȭ�� ������ ũ��.

	noexcept �� �̵� ������ swap, �޸� ���� �Լ���, �׸��� �Ҹ��ڵ鿡 Ư���� �����ϴ�.

	��κ��� �Լ��� noexcept �� �ƴ϶� ���ܿ� �߸����̴�.
*/