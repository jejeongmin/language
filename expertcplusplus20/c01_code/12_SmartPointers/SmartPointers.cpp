#include <iostream>
#include <memory>

/*
	unique_ptr 과 shared_ptr 은 배열로 저장할 경우,
	디버깅하면 조사식이나 로컬 변수 값 확인할 때, array 에 대한 참조나 [] 표현식이 안먹지?
	VS 2017 이 아직 지원안한다고 하기엔, c++11부터 있던 스펙인데..
*/

using namespace std;

struct Employee {
	char firstInitial = 'M';
	char lastInitial = 'G';
	int  employeeNumber = 42;
	int  salary = 80'000;
};

int main()
{
	{
		// unique_ptr
		auto anEmployee = make_unique<Employee>();
		if (anEmployee) {
			cout << "Salary: " << anEmployee->salary << endl;
		}
	}

	{
		// 배열을 unique_ptr로 저장한다.
		auto employees = make_unique<Employee[]>(10);
		for (int i=0; i<10; ++i)
		{
			cout << "employees " << i << " Salary: " << employees[i].salary << endl;
		}		
	}

	{
		// shared_ptr
		auto anEmployee = make_shared<Employee>();
		if (anEmployee) {
			cout << "Salary: " << anEmployee->salary << endl;
		}
	}

	{
		// 배열을 shared_ptr로 저장한다. (C++17)
		shared_ptr<Employee[]> employees(new Employee[10]);
		cout << "Salary: " << employees[0].salary << endl;
		for (int i = 0; i < 10; ++i)
		{
			cout << "employees " << i << " Salary: " << employees[i].salary << endl;
		}
	}
}
