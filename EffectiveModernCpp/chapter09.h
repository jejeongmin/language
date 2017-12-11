#pragma once

#include <functional>
#include <memory>
#include <mutex>


/*********************************************************
**********************************************************/

class chapter09 : public chapter
{
	class Widget
	{
	};

	template<typename T>
	struct MyAllocList1 {
		typedef std::vector<T> type;
	};
	// -> ���ø� �� ������ �ξ� ����������.
	template<typename T>
	using MyAllocList2 = std::vector<T>;

	template<typename T>
	class Change_Trait
	{
		// ���ø� ��Ÿ ���α׷��� �ÿ� ���ø� ���� �Ű� ������ �޾�
		// ������ ������ �������� ����� ���� �ϴ� ��Ȳ���� �Ʒ� �Լ����� Ȱ���� �� �ִ�.
		void change_trait()
		{
			std::remove_const_t<T>;			// const T -> T
			std::remove_reference_t<T>;		// T& / T&& -> T
			std::add_lvalue_reference_t<T>;	// T -> T&
		}

		T	_value;
	};

	virtual int chapterMain()
	{
		typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS1;
		// ->
		using UPtrMapSS2 = std::unique_ptr<std::unordered_map<std::string, std::string>>;

		typedef void(*FP1) (int, const std::string&);
		//-> ��Ī ������ ���� �� ���������� ���δ�.
		using FP2 = void(*)(int, const std::string&);

		MyAllocList1<Widget>::type	lw1;
		MyAllocList2<Widget>		lw2;
		
		return 0;
	}
};

/*
	typedef �� ���ø�ȭ�� �������� ������, ��Ī ������ �����Ѵ�.
	
	��Ī ���ø������� "::type" ���̾ ���� �ʿ䰡 ����. ���ø� �ȿ���
	typedef �� ������ ������ "typename" ���λ縦 �ٿ��� �ϴ� ��찡 ����.

	C++14 �� C++11 �� ��� ���� Ư�� ��ȯ�� ���� ��Ī ���ø����� �����Ѵ�.
*/