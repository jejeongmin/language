#pragma once

#include <iostream>

using namespace std;

// 이걸 유용하게 쓸 수 있는 용례는 잘 모르겠다만
// 함수 리턴 타입 역시 아래와 같은 방식으로 auto 를 사용하면 컴파일러가 알아서 추론한다.
auto addNumbers(int number1, int number2)
{
	std::cout << "enter function " << __func__ << std::endl;
	return number1 + number2;
}

int main()
{
	int	numbers[]{ 3, 5 };
	printf("%d+%d=%d", numbers[0], numbers[1], addNumbers(numbers[0], numbers[1]));

	// 구조적 바인딩

	return 0;
}
