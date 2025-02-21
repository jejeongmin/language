#include "GridRefNonType.h"
#include "SpreadsheetCell.h"
#include <iostream>

using namespace std;

/*
	레퍼런스 형태의 비타입 템플릿 매개변수에 전달할 인자로 임시값을 사용할 수 없고,
	internal, external link 없이 이름 있는 좌측값으로 지정할 수도 없다.
	그래서 아래 예제에서 전역으로 초기화 변수들을 만든 것이다.

	c++17 부터는 이러한 제약이 없어졌다고 알고 있는데, vs2017 c++17 에서는 여전히 안되네..
	나중에 vs2022 설치하면 다시 해봐야겠다.
*/
namespace {
	int defaultInt = 11;
	SpreadsheetCell defaultCell(1.2);
}

int main()
{
	Grid<int, defaultInt> myIntGrid;
	Grid<SpreadsheetCell, defaultCell> mySpreadsheet;

	Grid<int, defaultInt> myIntGrid2(myIntGrid);
	myIntGrid2.at(1, 2) = 3;

	cout << myIntGrid.at(1, 2).value_or(-1) << endl;
	cout << myIntGrid2.at(1, 2).value_or(-1) << endl;

	return 0;
}
