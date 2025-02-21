#pragma once

#include <iostream>
#include <string>

using namespace std;

// �̰� �����ϰ� �� �� �ִ� ��ʴ� �� �𸣰ڴٸ�
// �Լ� ���� Ÿ�� ���� �Ʒ��� ���� ������� auto �� ����ϸ� �����Ϸ��� �˾Ƽ� �߷��Ѵ�.
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
	// ������ ���ε� ����1
	{
		int	numbers[]{ 3, 5 };
		printf("%d+%d=%d \n", numbers[0], numbers[1], addNumbers(numbers[0], numbers[1]));


		auto[x, y] = numbers;
		printf("%d+%d=%d \n", x, y, addNumbers(x, y));
	}

	// ������ ���ε� ����2
	{
		struct Point { double x = 1, y = 2, z = 3; };
		Point point;
		auto[x, y, z] = point;
		std::cout << x << y << z << std::endl;
	}

	// ���۷����� ���� ���� ��Ȯ�� ���� �� �ϳ���, ������ ����ϸ� ���� ������ �� �̸��� ������ �� �ִٴ� �����̴�.
	// �Լ� ���ڷ� �ѱ� �� const ref �� ���� ���� ���� ū ������ �����̴�.
	{
		int	x = 42;
		int& ref_x = x;
	}

	// auto �� �����ϸ�, ���۷����� const �����ڰ� ������� ���� �����ȴٴ� ���� �����Ѵ�.
	// ���� ������� ���޵��� �ʰ� �Ϸ��� auto& �� const auto& �� �����ؾ� �Ѵ�.
	{
		auto f1 = foo();
		const auto& f2 = foo();
	}

	// decltype Ű����� �μ��� ������ ǥ������ Ÿ���� �˾Ƴ���.
	// decltype �� ���۷����� const �����ڸ� �������� �ʴ´ٴ� ������ auto �� �ٸ���.
	// �̷� �������� �ұ��ϰ�, ���ͺ��� auto ��뿡 ���ؼ� �������� �������� �����ϴٰ� ������ ���� ������
	// ���ø��� Ȱ��� ��ü�� ������ �� ����� �����ϰ� ���� �� �ִ�.
	{
		decltype(foo()) f1 = foo();
	}

	return 0;
}
