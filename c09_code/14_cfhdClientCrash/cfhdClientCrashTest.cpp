#include <iostream>
#include <string>
#include "CfhdClient.h"

using namespace std;

int main()
{
	CfhdClient	test1, test2;

	// nullptr access violation 을 예외처리로 막는 작업 처리, 혹은 divide by zero
	// 예외가 소멸자를 벗어나지 못하고, 크래시로 종료되는 것 확인
	// 소멸자 내에서 예외가 처리되어서, 크래시 막는 것 확인

	return 0;
}
