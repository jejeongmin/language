#include "Grid.h"
#include <iostream>

using namespace std;

constexpr size_t getHeight()
{
	return 10;
}

int main()
{
	Grid<int, 10, 10> myGrid;
	Grid<int, 10, 10> anotherGrid;
	//Grid<int, 10, 20> nonMatchedGrid;	 ���� ������ �׸��� ��ü��� ���� �ٸ� Ÿ���̾ ���� ���� �� �� ����.

	myGrid.at(2, 3) = 42;
	anotherGrid = myGrid;

	cout << anotherGrid.at(2, 3).value_or(0);

	Grid<double, 2, getHeight()> myDoubleGrid;

	return 0;
}
