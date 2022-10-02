#include <iostream>
#include <ctime>

using namespace std;

/*
	기존의 rand() 함수는 0과 RAND_MAX(32767 이상) 사이의 무작위수를 생성한다. 	낮은 자리 비트수의 무작위성은 그리 높지 않다.

	소프트웨어 기반의 무작위수 생성기는 진정한 의미의 무작위수를 생성할 수 없다.
	그래서 의사(pseudo) 무작위수 생성기라고 부른다. 무작위인 것처럼 보이게 만드는 수학 공식에 따라 생성하기 때문이다.
*/
int getRandom(int min, int max)
{
	return (rand() % static_cast<int>(max + 1 - min)) + min;
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
	cout << rand() << endl;

	cout << getRandom(1, 6) << endl;

	return 0;
}

