#include "Grid.h"

/*
���� �޼���� �Ҹ��ڴ� �޼��� ���ø����� ���� �� ����.
�ν��Ͻ�ȭ ���� ���� �θ� ��ü�� ���� �Լ��� �ִ� ��Ȳ����
�ڽ� ��ü�� ��ӹ��� ���� �Լ��� �ν��Ͻ�ȭ �ϴ� ��Ȳ�� �����غ���.
virtual �Լ��� ����� �������� �ʰ���.
���ø� �κ� �ν��Ͻ�ȭ�� ���õ� ����ȭ�� virtual ��� �Լ��� ������
������ �� �ֱ� �����̴�.
*/
int main()
{
	Grid<int> myIntGrid(2,2);
	Grid<double> myDoubleGrid;
	myIntGrid.at(1, 1) = 11;

	myDoubleGrid = myIntGrid;
	Grid<double> newDoubleGrid(myIntGrid);

	return 0;
}
