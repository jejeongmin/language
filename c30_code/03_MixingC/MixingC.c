#include <stdio.h>

/*
	MixingC.cpp은 C++이 아닌 C에서 컴파일할 수 있다.
	VS 에서 빌드하려면 확장자를 *.c 로 변경해야 한다. 
*/
int main()
{
	int class = 1; // C++가 아닌 C 컴파일러로 빌드해야 한다.
	printf("class is %d\n", class);

	return 0;
}
