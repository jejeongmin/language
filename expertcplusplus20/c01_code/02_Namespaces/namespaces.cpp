#include <iostream>
#include "namespaces.h"

//namespace mycode {
//	void foo()
//  {
//		std::cout << "foo() called in the mycode namespace" << std::endl;
//	}
//}

// ���ӽ����̽� ���� �Լ��� �Ʒ��� ���� Ŭ���� �Լ� ����ó�� ����� �� �ִ�.
// ������ ��� ǥ���̱� �ϳ�, ������ ���� Ŭ���� �Լ� ������ ���������� ��Ȯ�� ���еǴ� �� ���� ��.
void mycode::foo()
{
	std::cout << "foo() called in the mycode namespace" << std::endl;
}
