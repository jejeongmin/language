#include <iostream>
#include "Employee.h"

using namespace std;
using namespace Records;

/*
std::mem_fn �� �̿��ϸ� (.*)�� ���� ������ ����� ���� ����.

���α׷��� �ۼ��� �� �޼��峪 ������ ����� ���� �����͸� ����� ���� ���� ������,
non-static �޼��峪 ������ ����� ���� �����͸� ��ü�� ��ġ�� �ʰ��� �������� �� ���ٴ� ����� �ݵ�� ����Ѵ�.
*/
int main()
{
	Employee employee;
	
	// ���� ��Ÿ��:
	//int (Employee::*methodPtr) () const = &Employee::getSalary;

	// Ÿ�� �ٸ�� ���:
	//using PtrToGet = int (Employee::*) () const;
	//PtrToGet methodPtr = &Employee::getSalary;

	// auto ���:
	auto methodPtr = &Employee::getSalary;

	cout << (employee.*methodPtr)() << endl;

	return 0;
}