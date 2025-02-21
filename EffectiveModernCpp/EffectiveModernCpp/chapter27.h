#pragma once

#include <iostream>
#include <functional>
#include <memory>

/*********************************************************
**********************************************************/

using namespace std;

class chapter27 : public chapter
{
	std::vector<std::string>	names;

	template<typename T>
	void logAndAdd(T&& name)
	{
		logAndAddImpl(std::forward<T>(name), std::is_integral<std::remove_reference_t<T>>::value);		
	}

	template<typename T>
	void logAndImpl(T&& name, std::true_type)
	{
		std::cout << "log and add for integral" << std::endl;
	}

	template<typename T>
	void logAndImpl(T&& name, std::false_type)
	{
		std::cout << "log and add for non integral" << std::endl;
	}

	/*
		���� ������ �޴� ���ø��� ������ �������� �������� �����ؼ� �����ε��� �����ϰ� ������ ���� �ִ�.

		std::enable_if �� �̿��ϸ� ������ ������ ������ ����, �ش� ���ø��� Ȱ��ȭ�ȴ�.
		std::is_same �� �� ������ ���� �� �����Ѵ�.
		std::decay �� ��� ������ ��� const, volatile �����ڸ� ������ ���Ŀ� �ش��Ѵ�.
		std::is_base_of<T1, T2> �� ���� T2 �� T1 ���� �Ļ��� �����̸� ���̴�. std::is_base_of<T1, T1> �� ���� T1 �� ����� ���� �����̶�� ���̰�, ���� ������ ���� �����̴�.
		std::is_constructible �� �� ������ ��ü�� �ٸ� �� ������ ��ü�κ��� ������ �� �ִ� �� ������ �������� �����Ѵ�.
	*/
	class Person
	{
	public:
		template<typename T,
				 typename = std::enable_if_t<
								!std::is_base_of<Person, std::decay_t<T>>::value
								&&
								!std::is_integral<std::remove_reference_t<T>>::value>>
			explicit Person(T&& n)
			: name(std::forward<T>(n))
		{
			static_assert(std::is_constructible<std::string, T>::value, "Paameter n can't be used to construct a std::string");
		}

	private:
		std::string	name;
	};
	
	virtual int chapterMain()
	{
		return 0;
	}
};

/*
	���� ������ �ߺ������� ���տ� ���� ������δ� �����Ǵ� �Լ� �̸� ���, �Ű������� const �� ���� �ް� ������ ����, �Ű������� ������ ����,
	����ǥ ��� ������ �ִ�.

	std::enable_if �� �̿��ؼ� ���ø��� �ν��Ͻ�ȭ�� ���������ν� ���� ������ �ߺ����縦 �Բ� ����� �� �ִ�.
	std::enable_if �� �����Ϸ��� ���� ���� �ߺ����縦 ����ϴ� ������ ���α׷��Ӱ� ���� �����ϴ� �뵵�� ���δ�.

	���� ���� �Ű������� ȿ���� �鿡�� ������ ��찡 ������, ��ü�� ��뼺 �鿡���� ������ �ȴ�.
*/