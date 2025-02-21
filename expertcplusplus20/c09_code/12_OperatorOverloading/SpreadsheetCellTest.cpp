#include "AddFirstAttempt/AddFirstAttempt.h"
#include "AddSecondAttempt/AddSecondAttempt.h"
#include "GlobalOperators/GlobalOperators.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//#define MAIN_1
#define MAIN_2
//#define MAIN_3

#ifdef MAIN_1

using namespace AddFirstAttempt;

int main()
{
	SpreadsheetCell myCell(4), anotherCell(5);
	SpreadsheetCell aThirdCell = myCell.add(anotherCell);
	cout << aThirdCell.getValue() << endl;

	return 0;
}

#endif

#ifdef MAIN_2

using namespace AddSecondAttempt;

int main()
{
	SpreadsheetCell myCell(4), anotherCell(5);
	SpreadsheetCell aThirdCell = myCell + anotherCell;	// SpreadsheetCell aThirdCell = myCell.operator+(anotherCell); ȣ��� �����ϴ�.
	
	string str = "hello";

	aThirdCell = myCell + string_view(str);
	aThirdCell = myCell + 5.6;
	aThirdCell = myCell + 4;

	// ���� �� ���忡�� ������ ������ �߻��Ѵ�.
	// aThirdCell = 4 + myCell; // ������ ����!
	// aThirdCell = 5.6 + myCell; // ������ ����!

	return 0;
}

#endif


#ifdef MAIN_3

using namespace GlobalOperators;

int main()
{
	SpreadsheetCell myCell(4), anotherCell(5);
	SpreadsheetCell aThirdCell = myCell + anotherCell;

	// ���� �� ������ ����� ��Ʈ�� ctor�� ������ �� ����.
	// string str = "hello";
	// aThirdCell = myCell + str;

	aThirdCell = myCell + 5.6;
	aThirdCell = myCell + 4;

	aThirdCell = 4 + myCell;   // ���� ���� ����ȴ�.
	aThirdCell = 5.6 + myCell; // ���� ���� ����ȴ�.
	aThirdCell = 4.5 + 5.5;

	aThirdCell = myCell - anotherCell;
	aThirdCell = myCell * anotherCell;
	aThirdCell = myCell / anotherCell;

	try {
		aThirdCell = myCell / 0;
	} catch (const invalid_argument& e) {
		cout << "Caught: " << e.what() << endl;
	}

	aThirdCell -= myCell;
	aThirdCell += 5.4;
	aThirdCell *= myCell;
	aThirdCell /= myCell;

	if (myCell > aThirdCell || myCell < 10) {
		cout << myCell.getValue() << endl;
	}

	if (anotherCell == myCell) {
		cout << "cells are equal\n";
	} else {
		cout << "cells are not equal\n";
	}

	return 0;
}

#endif