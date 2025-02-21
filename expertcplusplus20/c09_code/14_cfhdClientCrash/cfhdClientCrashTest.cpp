#include "stdafx.h"
#include "DestructorException.h"
#include "DestructorNoException.h"

using namespace std;

int main()
{
	try
	{
		std::string s;
		s.resize(-1);  // ���� �߻�
	}
	catch (std::exception & e)
	{
		std::cout << typeid(e).name() << std::endl;
		std::cerr << e.what() << std::endl;
	}

	// �Ҹ��� ������ ���ܰ� ó���Ǿ, ũ���� ���� �� Ȯ��
	try
	{
		DestructorException test;
	}
	catch (std::exception & e)
	{
		std::cout << typeid(e).name() << std::endl;
		std::cerr << e.what() << std::endl;
	}

	// ���ܰ� �Ҹ��ڸ� ����� ���ϰ�, ũ���÷� ����Ǵ� �� Ȯ��
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
