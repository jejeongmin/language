#include "SpreadsheetCell.h"
#include <iostream>

using namespace std;

int main()
{
	SpreadsheetCell c1(4);
	SpreadsheetCell c2(6);
	
	cout << (c1 == c2) << endl;
	cout << (c1 < c2) << endl;
	cout << (c1 != c2) << endl;	// == 연산자가 선언되어 있으면 자동으로 되는 듯. 확인 필요
	cout << (c1 > c2) << endl;
	cout << (c1 <= c2) << endl;	// > 연산자가 선언되어 있으면 자동으로 되는 듯. 확인 필요
	cout << (c1 >= c2) << endl;	// > 연산자가 선언되어 있으면 자동으로 되는 듯. 확인 필요

	return 0;
}
