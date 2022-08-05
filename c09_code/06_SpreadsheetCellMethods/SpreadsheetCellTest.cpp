#include "SpreadsheetCell.h"
#include <iostream>

using namespace std;

int main()
{
	string str = SpreadsheetCell::doubleToString(5);

	SpreadsheetCell myCell(5);
	cout << myCell.getValue() << endl; // OK
	myCell.set("6"); // OK

	const SpreadsheetCell& myCellConstRef = myCell;
	cout << myCellConstRef.getValue() << endl; // OK
	//myCellConstRef.set("6"); // 컴파일 에러 발생! const ref 객체를 가지고 set ( write ) 하려고 하니깐.

	return 0;
}
