#include "Grid.h"
#include "SpreadsheetCell.h"

/*
	��Ÿ�� �Ű� �������� ��ü�� ������ �� ����, double �̳� float �� �����ϸ� �ȵȴ�.
	�ݵ�� ���� �迭�� Ÿ�԰� enum, ������, ���۷����θ� �����ؾ� �Ѵ�.
*/
int main()
{
	Grid<int> myIntGrid;		// �ʱ갪�� 0
	Grid<int, 10> myIntGrid2;	// �ʱ갪�� 10

	myIntGrid.at(1, 2) = 3;

	SpreadsheetCell defaultCell;
	//Grid<SpreadsheetCell, defaultCell> mySpreadsheet; // ������ ���� �߻�!

	return 0;
}
