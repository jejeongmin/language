#include <iostream>
#include <vector>
#include "Spreadsheet.h"

using namespace std;

Spreadsheet createObject()
{
	return Spreadsheet(3, 2);
}

int main()
{
	vector<Spreadsheet> vec;
	for (int i = 0; i < 2; ++i) {
		cout << "Iteration " << i << endl;
		vec.push_back(Spreadsheet(100, 100));
		cout << endl;
	}

	/*
	Output :
		Iteration 0
		Normal constructor
		Move constructor

		Iteration 1
		Normal constructor
		Move constructor
		Move constructor
	*/

	Spreadsheet s(2, 3);
	s = createObject();
	/*
	Output :
		Normal constructor
		Normal constructor
		Move assignment operator
	*/

	Spreadsheet s2(5, 6);
	s2 = s;
	/*
	Output :
		Normal constructor
		Copy assignment operator
		Normal constructor
		Copy constructor
	*/

	return 0;
}
