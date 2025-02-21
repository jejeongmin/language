#include "stdafx.h"
#include "DestructorException.h"

DestructorException::DestructorException()
{
}


DestructorException::~DestructorException()
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
}
