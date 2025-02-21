#include <iostream>

using namespace std;

int main()
{
	// 가장 간단한 람다 표현식
	auto basicLambda = []{ cout << "Hello from Lambda" << endl; };
	basicLambda();

	// 매개변수가 있는 람다 표현식
	auto parametersLambda = [](int value){ cout << "The value is " << value << endl; };
	parametersLambda(42);

	// 값을 리턴하는 람다 표현식
	auto returningLambda = [](int a, int b) -> int { return a + b; };
	int sum = returningLambda(11, 22);
	cout << "The result is " << sum << endl;

	// 값을 리턴하는 람다 표현식, 리턴 타입은 생략
	auto returningLambda2 = [](int a, int b) { return a + b; };
	sum = returningLambda2(11, 22);
	cout << "The result is " << sum << endl;

	// 변수를 값으로 캡처하는 람다 표현식
	double data = 1.23;
	auto capturingVLambda = [data]{ cout << "Data = " << data << endl; };
	capturingVLambda();

	// 람다 표현식은 이름 없는 functor 로 변환된다. 그리고 그 functor 의 operator() 는 기본적으로 const 로 설정된다.
	// 값으로 갭쳐된 람다 표현식의 변수는 결국 그 functor 객체의 멤버 변수가 되는데 이를 변경하기 위해서는 mutable 선언이 되어 있어야 non const 로 호출 가능하게 된다.
	// mutable 을 지정하는 경우에는 매개변수가 없더라도 반드시 () 소괄호를 적어야 한다.
	auto capturingVLambda2 = [data] () mutable { data *= 2; cout << "Data = " << data << endl; };
	capturingVLambda2();

	// 변수를 레퍼런스로 캡처하는 람다 표현식
	auto capturingRLambda = [&data]{ data *= 2; };
	capturingRLambda();
	cout << "Data = " << data << endl;

	return 0;
}
