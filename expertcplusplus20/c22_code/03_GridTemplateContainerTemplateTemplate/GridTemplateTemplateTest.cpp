#include "GridTemplateTemplate.h"
#include <vector>
#include <iostream>

using namespace std;

/*
	Grid<int, vector<int>> myGrid;
	
	위 선언 보다는 아래 방식 실수가 적겠지.

	Grid<int, vector> myGrid;
*/
int main()
{
	Grid<int, vector> myGrid;
	myGrid.at(1, 2) = 3;
	cout << myGrid.at(1, 2).value_or(0) << endl;

	Grid<int, vector> myGrid2(myGrid);

	return 0;
}
