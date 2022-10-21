#include <iostream>
#include <string>
#include <string_view>

using namespace std;

void handleValue(int value)
{
	cout << "Integer: " << value << endl;
}
void handleValue(double value)
{
	cout << "Double: " << value << endl;
}
void handleValue(string_view value)
{
	cout << "String: " << value << endl;
}


// 값 전달 방식을 이용하는 첫 번째 버전
void processValues()	// 베이스 케이스
{
	// 베이스 케이스에 대해서 특별히 할 일이 없다.
}

template<typename T1, typename... Tn>
void processValues(T1 arg1, Tn... args)		// 여기의 ... 은 매개변수 팩을 표현
{
	handleValue(arg1);
	processValues(args...);		// ... 이 쓰인 경우는 매개변수 팩 풀기 연산이다.
}


// 우측값 레퍼런스 전달 방식을 이용하는 두 번째 버전
/*
	위의 processValues 는 재귀적으로 호출할 때, 매개변수 복제가 많아지면서 성능 문제가 생길 수 있다.
	레퍼런스를 활용하면 이 문제를 개선할 수 있다.
	const 레퍼런스를 제외하면, 리터럴 값에 대해서는 레퍼런스를 사용할 수 없지만
	non-const 레퍼런스를 사용하면서 리터럴 값을 사용하게 하려면 forward reference 를 사용하면 된다.
	아래 코드는 포워드 레퍼런스인 T&& 를 사용했고, 모든 매개변수에 대해 퍼펙트 포워딩을 적용하도록 std::forward()를 사용했다.
	여기서 perfect fowarding 이란 processValue()에 우측값rvalue 이 전달되면 우측값 레퍼런스로 포워드되고,
	좌측값이나 좌측값 레퍼런스가 전달되면 좌측값 레퍼런스로 포워드된다는 뜻이다.
*/

void processValuesRValueRefs()	// 베이스 케이스
{
	// 베이스 케이스에 대해 특별히 할 일이 없다.
}

template<typename T1, typename... Tn>
void processValuesRValueRefs(T1&& arg1, Tn&&... args)
{
	handleValue(std::forward<T1>(arg1));

	// 아래 코드는 매개 변수 팩에 있는 각 인수를 std::forward()로 호출하고, 그들을 컴마로 구분해서 분리한다.
	processValuesRValueRefs(std::forward<Tn>(args)...);

	// 매개변수 팩을 사용하는 함수의 바디 안에서 이 팩에 담긴 인수의 개수를 알아내는 방법
	int numOfArgs = sizeof...(args);
}


/*
	일반적으로 템플릿의 매개변수는 개수가 고정되어 있다.
	하지만 가변 인수 템플릿은 템플릿 매개 변수의 개수가 고정돼 있지 않다.
	예를 들어 다음과 같이 템플릿 매개변수의 개수를 지정하지 않게 정의할 수 있다.
	이때 Types 라는 매개변수 팩(parameter pack)을 사용한다.

	template<typename... Types> class MyVariadicTemplate {};

	typename 뒤에 붙은 ... 은 오자가 아니라 가변 인수 템플릿에 대한 매개변수 팩을 정의하는 구문이다.
	매개변수 팩은 다양한 수의 인수를 받을 수 있다. 점 세 개의 앞이나 뒤에 공백을 넣어도 된다.
*/


int main()
{
	processValues(1, 2, 3.56, "test", 1.1f);
	cout << endl;
	processValuesRValueRefs(1, 2, 3.56, "test", 1.1f);

	return 0;
}
