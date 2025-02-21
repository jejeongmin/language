#pragma once


void sumFunc(int, double)	{}

template<typename T> void f1(T param)
{
}

template<typename T> void f2(std::initializer_list<T> initList)
{
}

/***************************************
	auto �� ���� ���� ���� �� ���� ���� ������.

	��� 1 : ���� �����ڰ� �����ͳ� ���� ���������� ���� ����(universal reference) �� �ƴ� ���
	��� 2 : ���� �����ڰ� ���� ������ ���
	��� 3 : ���� �����ڰ� �����͵� �ƴϰ� ������ �ƴ� ���
***************************************/
class chapter02 : public chapter
{
	virtual int chapterMain()
	{
		auto x = 27;			// ��� 3, x �� �����͵� �ƴϰ� ������ �ƴ�
		std::cout << typeid(x).name() << " : " << x << std::endl;

		const auto cx = x;		// ��� 3, cx ���� �Ѵ� �ƴ�
		std::cout << typeid(cx).name() << " : " << cx << std::endl;

		const auto& rx = x;		// ��� 1, rx �� ���� ������ �ƴ� ����
		std::cout << typeid(rx).name() << " : " << rx << std::endl;

		auto&& uref1 = x;		// x �� int ���� �ް��̹Ƿ� uref1 �� ������ int&
		std::cout << typeid(uref1).name() << " : " << uref1 << std::endl;

		auto&& uref2 = cx;		// cx �� const int ���� �ް��̹Ƿ� uref2 �� ������ const int&
		std::cout << typeid(uref2).name() << " : " << uref2 << std::endl;

		auto&& uref3 = 27;		// 27 �� int ���� �������̹Ƿ� uref3 �� ������ int&&
		std::cout << typeid(uref3).name() << " : " << uref3 << std::endl;

		const char name[] = "Je, JeongMin";
		auto arr1 = name;		// const char*
		auto& arr2 = name;		// const char (&)[13]

		auto func1 = sumFunc;	// void (*)(int, double)
		auto& func2 = sumFunc;	// å���� void (&)(int, double) �ϰŶ�� �ϳ�, �����δ� void (*)(int, double)

		/*
			���ø� ���� �����߷а� auto ���� �����߷��� ������ �� �ϳ��� �Ʒ� �巯����.
			auto �� ����� ������ �ʱ�ġ(initializer)�� �߰�ȣ ������ ������ �����̸�, ������ ������
			std::initialzer_list �̴�.
		*/
		auto	x1 = 27;		// int
		auto	x2(27);			// int
		auto	x3 = { 27 };		// std::initializer_list<int>
		auto	x4{ 27 };			// int
		//auto	x5 = { 1, 2, 3.0 };		// std::initializer_list<T> �� T �� �ϰ��ǰ� ������ �� ����

		//f1({ 11, 23, 9 });	// T �� ���� ������ ������ �� ����
		f2({ 11, 23, 9 });		// T �� int �� �����Ǹ�, initList �� ������ std::initializer_list<int>�� �����ȴ�.

		return 0;
	}

	/*******************************************************
	c++14 ������ �Լ��� ��ȯ ������ auto �� �����ؼ� �����Ϸ��� �����ϰ� �� �� ������,
	������ �Ű����� ���� auto �� ����ϴ� �͵� �����ϴ�.
	�׷��� auto �� �׷��� ����鿡�� auto ���� ������ �ƴ϶� ���ø� ���� ������ ��Ģ���� ����ȴ�.
	���� �Ʒ��� ���� ���Ϲ��� auto �� �����ص� �����Ϸ��� std::initializer_list<int> �� ������ �� ����.
	*******************************************************/
	auto createInitList()
	{
		return	0;
		//return	{ 1, 2, 3 };	compile error
	}
};

/*
	����� �� ���׵�

	auto ���� ������ ��ü�� ���ø� ���� ������ ������, auto ���� ������ �߰�ȣ �ʱ�ġ��
	std::initializer_list �� ��Ÿ���ٰ� �����ϴ� �ݸ�, ���ø� ���� ������ �׷��� �ʴٴ� ���̰� �ִ�.

	�Լ��� ��ȯ �����̳� ���� �Ű������� ���� auto �� ���ؼ��� auto ���� ������ �ƴ϶�
	���ø� ���� ������ ����ȴ�.
*/