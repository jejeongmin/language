#include <iostream>
#include "Employee.h"

using namespace std;
using namespace Records;

/*
std::mem_fn 을 이용하면 (.*)과 같은 문법을 사용할 일이 없다.

프로그램을 작성할 때 메서드나 데이터 멤버에 대한 포인터를 사용할 일은 많지 않지만,
non-static 메서드나 데이터 멤버에 대한 포인터를 객체를 거치지 않고서는 역참조할 수 없다는 사실을 반드시 명심한다.
*/
int main()
{
	Employee employee;
	
	// 예전 스타일:
	//int (Employee::*methodPtr) () const = &Employee::getSalary;

	// 타입 앨리어스 사용:
	//using PtrToGet = int (Employee::*) () const;
	//PtrToGet methodPtr = &Employee::getSalary;

	// auto 사용:
	auto methodPtr = &Employee::getSalary;

	cout << (employee.*methodPtr)() << endl;

	return 0;
}