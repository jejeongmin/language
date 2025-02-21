/*
	크기를 변수로 받아서 스택 기반 배열을 생성한다.
	표준 C++ 기능은 아니지만, 이렇게 작성하는 것을 허용하는 컴파일러도 있다.

	최신 g++ 에서는 C언어 컴파일 기능에 한해 
	VLA ( Varaible-Length stack-based Array) 라는 이름으로 지원한다.
	그러나 MSVC 에서는 해당 코드에 대한 컴파일을 허용하지 않는다. 

	constexpr 키워드로 상수표현식으로 변경해 컴파일 가능하게 변경했다.
*/

int main()
{
	//int i = 4;
	constexpr int i = 4;

	char myStackArray[i];  // 표준 기능은 아니다.

	return 0;
}
