#include "SpreadsheetCell.h"
#include <iostream>

using namespace std;

//# define MAIN_2

#ifdef MAIN_2
int main()
{
	SpreadsheetCell* cellPtr1 = new SpreadsheetCell(5);
	SpreadsheetCell* cellPtr2 = new SpreadsheetCell(6);

	cout << "cellPtr1: " << cellPtr1->getValue() << endl;

	delete cellPtr1; // cellPtr1�� �����Ѵ�.
	cellPtr1 = nullptr;

	return 0;
} // cellPtr2�� ���ŵ��� �ʴ´�. ���⿡ ���� delete�� ȣ������ �ʾұ� �����̴�.
#endif