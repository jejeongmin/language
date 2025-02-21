#include <stdio.h>

/*
	c 언어는 동일한 함수 이름에 대한 오버로딩 개념이 없다.
	따라서 C 컴파일러가 생성한 함수 이름은 프로그래머가 지은 이름과 동일하거나 상당히 단순하다.

	그러나 c++ 은 동일한 함수 이름에 대한 오버로딩을 지원하기 위해 name mangling 을 활용한다.

	void MyFunc(double);
	void MyFunc(int);
	void MyFunc(int, int);

	와 같은 선언에 대해 c++ 컴파일러는 

	MyFunc_double
	MyFunc_int
	MyFunc_int_int

	와 같은 형식으로 링커가 참조할 이름을 자동 생성한다. 물론 바로 위의 이름은 이해하기 쉽게 정한 규칙이며
	MS Visual Studio 경우는 아래와 같이 나름의 이름 규칙을 사용한다.

	?MyFunc@@YAXN@Z
	?MyFunc@@YAXH@Z
	?MyFunc@@YAXHH@Z

	c++ 표준은 특정한 플랫폼에서 함수 오버로딩을 구현하는 방식을 구체적으로 정의하고 있지 않다.
	이와 같이 name mangling 에 대한 표준이 없기 때문에 벤더마다 이름 규칙이 다르다.

	따라서 함수 이름 규칙을 c++ 컴파일러 밴더에 종속하지 않도록, name mangling 을 적용하지 않도록 하는 키워드가 extern "C" 이다.
*/

// extern 용례 #1
extern "C" void MyFunc1()
{
	printf("MyFunc1()\n");
}

// extern 용례 #2
extern "C" {
	void MyFunc2()
	{
		printf("MyFunc2()\n");
	}
}

// extern 용례 #3
#ifdef __cplusplus
	extern "C" {
#endif
		void MyFunc3()
		{
			printf("MyFunc3()\n");
		}
#ifdef __cplusplus
	}
#endif

int main()
{
	int classId = 1; // C++가 아닌 C 컴파일러로 빌드해야 한다.
	printf("class is %d\n", classId);

	MyFunc1();
	MyFunc2();
	MyFunc3();

	return 0;
}
