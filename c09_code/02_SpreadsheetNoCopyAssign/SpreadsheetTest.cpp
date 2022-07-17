#include "Spreadsheet.h"

void printSpreadsheet(Spreadsheet s)
{
	// 코드 생략
}

int main()
{
	//Spreadsheet s1(4, 3);
	//printSpreadsheet(s1);

	Spreadsheet s1(2, 2), s2(4, 3);
	// s1 = s2; 대입 연산자를 delete 선언했기 때문에 컴파일 에러 발생

	return 0;
}
