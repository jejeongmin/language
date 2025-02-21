#include "stdafx.h"
#include "DestructorNoException.h"



DestructorNoException::DestructorNoException()
{
}


DestructorNoException::~DestructorNoException()
{
	std::string s;
	s.resize(-1);  // 예외 발생
}
