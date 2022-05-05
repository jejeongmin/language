#include <iostream>
#include "namespaces.h"

//namespace mycode {
//	void foo()
//  {
//		std::cout << "foo() called in the mycode namespace" << std::endl;
//	}
//}

// 네임스페이스 안의 함수를 아래와 같이 클래스 함수 구현처럼 사용할 수 있다.
// 가능한 축약 표현이긴 하나, 기존과 같이 클래스 함수 구현과 문법적으로 명확히 구분되는 게 나을 듯.
void mycode::foo()
{
	std::cout << "foo() called in the mycode namespace" << std::endl;
}
