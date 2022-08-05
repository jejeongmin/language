#include "stdafx.h"
#include "DestructorException.h"
#include "DestructorNoException.h"

using namespace std;

int main()
{
	try
	{
		std::string s;
		s.resize(-1);  // 예외 발생
	}
	catch (std::exception & e)
	{
		std::cout << typeid(e).name() << std::endl;
		std::cerr << e.what() << std::endl;
	}

	// 소멸자 내에서 예외가 처리되어서, 크래시 막는 것 확인
	try
	{
		DestructorException test;
	}
	catch (std::exception & e)
	{
		std::cout << typeid(e).name() << std::endl;
		std::cerr << e.what() << std::endl;
	}

	// 예외가 소멸자를 벗어나지 못하고, 크래시로 종료되는 것 확인
	try
	{
		DestructorNoException test;
	}
	catch (std::exception & e)
	{
		std::cout << typeid(e).name() << std::endl;
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
