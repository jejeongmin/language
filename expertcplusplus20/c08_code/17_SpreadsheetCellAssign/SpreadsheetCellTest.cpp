#include "SpreadsheetCell.h"

#define MAIN_2

#ifdef MAIN_2
int main()
{
	SpreadsheetCell myCell, anotherCell, aThirdCell;

	// ���� ���� �����ڸ� ���ɻ��� ������ ���� Ÿ�� ��ü�� ���� ���۷����� �����Ѵ�.
	// �ֳ��ϸ� �Ʒ��� ���� ���� ���� ���� ������ ���޾� ���� �� �ֱ� �����̴�.
	myCell = anotherCell = aThirdCell;

	myCell.operator=(anotherCell.operator=(aThirdCell));

	SpreadsheetCell cell(4);
	cell = cell; // �ڱ� �ڽ��� �����Ѵ�.

	return 0;
}
#endif