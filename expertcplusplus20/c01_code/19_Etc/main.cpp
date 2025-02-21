#pragma once

#include <iostream>
#include <string>

using namespace std;

// 이걸 유용하게 쓸 수 있는 용례는 잘 모르겠다만
// 함수 리턴 타입 역시 아래와 같은 방식으로 auto 를 사용하면 컴파일러가 알아서 추론한다.
auto addNumbers(int number1, int number2)
{
	std::cout << std::endl << "enter function " << __func__ << std::endl;
	return number1 + number2;
}

const std::string	gMessage = "Test";
const std::string& foo()
{
	return gMessage;
}

int main()
{
	// 구조적 바인딩 예시1
	{
		int	numbers[]{ 3, 5 };
		printf("%d+%d=%d \n", numbers[0], numbers[1], addNumbers(numbers[0], numbers[1]));


		auto[x, y] = numbers;
		printf("%d+%d=%d \n", x, y, addNumbers(x, y));
	}

	// 구조적 바인딩 예시2
	{
		struct Point { double x = 1, y = 2, z = 3; };
		Point point;
		auto[x, y, z] = point;
		std::cout << x << y << z << std::endl;
	}

	// 레퍼런스의 본질 대한 정확한 설명 중 하나는, 참조를 사용하면 기존 변수에 새 이름을 지정할 수 있다는 설명이다.
	// 함수 인자로 넘길 때 const ref 를 쓰는 것의 가장 큰 장점은 성능이다.
	{
		int	x = 42;
		int& ref_x = x;
	}

	// auto 를 지정하면, 레퍼런스와 const 지정자가 사라져서 값이 복제된다는 점에 주의한다.
	// 복제 방식으로 전달되지 않게 하려면 auto& 나 const auto& 로 지정해야 한다.
	{
		auto f1 = foo();
		const auto& f2 = foo();
	}

	// decltype 키워드는 인수로 지정한 표현식의 타입을 알아낸다.
	// decltype 은 레퍼런스나 const 지정자를 삭제하지 않는다는 점에서 auto 와 다르다.
	// 이런 장점에도 불구하고, 얼핏보면 auto 사용에 비해서 가독성만 떨어지고 복잡하다고 생각할 수도 있지만
	// 템플릿이 활용된 객체를 구현할 때 상당히 유용하게 쓰일 수 있다.
	{
		decltype(foo()) f1 = foo();
	}

	return 0;
}
