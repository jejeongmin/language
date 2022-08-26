#include "Grid.h"

/*
가상 메서드와 소멸자는 메서드 템플릿으로 만들 수 없다.
인스턴스화 되지 않은 부모 객체의 가상 함수가 있는 상황에서
자식 객체의 상속받은 가상 함수만 인스턴스화 하는 상황을 가정해보자.
virtual 함수가 기대대로 동작하지 않겠지.
템플릿 부분 인스턴스화와 관련된 최적화와 virtual 상속 함수이 개념이
상충할 수 있기 때문이다.
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
