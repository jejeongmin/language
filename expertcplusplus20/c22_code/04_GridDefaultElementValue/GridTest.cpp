#include "Grid.h"
#include "SpreadsheetCell.h"

/*
	비타입 매개 변수에는 객체를 전달할 수 없고, double 이나 float 로 지정하면 안된다.
	반드시 정수 계열의 타입과 enum, 포인터, 레퍼런스로만 지정해야 한다.
*/
int main()
{
	Grid<int> myIntGrid;		// 초깃값은 0
	Grid<int, 10> myIntGrid2;	// 초깃값은 10

	myIntGrid.at(1, 2) = 3;

	SpreadsheetCell defaultCell;
	//Grid<SpreadsheetCell, defaultCell> mySpreadsheet; // 컴파일 에러 발생!

	return 0;
}
