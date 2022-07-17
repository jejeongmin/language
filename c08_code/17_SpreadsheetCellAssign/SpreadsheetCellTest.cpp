#include "SpreadsheetCell.h"

#define MAIN_2

#ifdef MAIN_2
int main()
{
	SpreadsheetCell myCell, anotherCell, aThirdCell;

	// 복제 대입 연산자를 성능상의 이유로 복사 타겟 객체에 대한 레퍼런스를 전달한다.
	// 왜냐하면 아래와 같이 여러 개의 대입 연산이 연달아 있을 수 있기 때문이다.
	myCell = anotherCell = aThirdCell;

	myCell.operator=(anotherCell.operator=(aThirdCell));

	SpreadsheetCell cell(4);
	cell = cell; // 자기 자신을 대입한다.

	return 0;
}
#endif