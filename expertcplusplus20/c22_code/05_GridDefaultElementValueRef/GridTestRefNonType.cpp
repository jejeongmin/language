#include "GridRefNonType.h"
#include "SpreadsheetCell.h"
#include <iostream>

using namespace std;

/*
	���۷��� ������ ��Ÿ�� ���ø� �Ű������� ������ ���ڷ� �ӽð��� ����� �� ����,
	internal, external link ���� �̸� �ִ� ���������� ������ ���� ����.
	�׷��� �Ʒ� �������� �������� �ʱ�ȭ �������� ���� ���̴�.

	c++17 ���ʹ� �̷��� ������ �������ٰ� �˰� �ִµ�, vs2017 c++17 ������ ������ �ȵǳ�..
	���߿� vs2022 ��ġ�ϸ� �ٽ� �غ��߰ڴ�.
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
