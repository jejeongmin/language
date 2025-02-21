#include <cstddef>
#include <array>

void doubleInts(int* theArray, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		theArray[i] *= 2;
	}
}

/*
void doubleInts(int theArray[], size_t size)
{
	for (size_t i = 0; i < size; i++) {
		theArray[i] *= 2;
	}
}
*/

/*
void doubleIntsStack(int (&theArray)[4])
{
	for (size_t i = 0; i < 4; i++) {
		theArray[i] *= 2;
	}
}
*/

template<size_t N>
void doubleIntsStack(int (&theArray)[N])
{
	for (size_t i = 0; i < N; i++) {
		theArray[i] *= 2;
	}
}

int main()
{
	size_t arrSize = 4;
	int* heapArray = new int[arrSize]{ 1, 5, 3, 4 };
	doubleInts(heapArray, arrSize);
	//doubleIntsStack(heapArray);	// 이렇게 할 수 없다.
	delete[] heapArray;
	heapArray = nullptr;

	int stackArray[] = { 5, 7, 9, 11 };
	arrSize = std::size(stackArray);	// C++17부터 <array>를 사용한다.
	//arrSize = sizeof(stackArray) / sizeof(stackArray[0]); //  C++17 이전 방식: 1장 참조
	doubleInts(stackArray, arrSize);
	doubleInts(&stackArray[0], arrSize);

	// 함수템플릿을 활용하면 스택 배열의 크기를 컴파일러가 알아낼 수 있지만..
	doubleIntsStack(stackArray);

	// 스택 크기가 달라지면 크기마다 함수템플릿이 함수를 계속 구체화해버리니, 좋지도 않고 문법이 깔끔하지도 않음.
	int stackArray2[] = { 5, 7, 9, 11, 13 };
	doubleIntsStack(stackArray2);

	// 크기가 다른 호출에 대해 함수가 달라지는 걸 확인
	printf("%p \n", doubleIntsStack<4>);
	printf("%p \n", doubleIntsStack<4>);
	printf("%p \n", doubleIntsStack<5>);
	
	return 0;
}
