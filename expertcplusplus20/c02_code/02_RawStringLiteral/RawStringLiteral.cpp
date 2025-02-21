#include <iostream>

using namespace std;

int main()
{
	//const char* str1 = "Hello "World"!";    // 에러!
	const char* str2 = "Hello \"World\"!";
	const char* str3 = R"(Hello "World"!)";

	const char* str4 = "Line 1\nLine 2";
	const char* str5 = R"(Line 1
Line 2)";

	const char* str6 = R"(Is the following a tab character? \t)";

	//const char* str7 = R"(Embedded )" characters)";    // 에러!
	const char* str8 = R"-(Embedded )" characters)-";

	std::cout << "str2 : " << str2 << std::endl;
	std::cout << "str3 : " << str3 << std::endl;
	std::cout << "str4 : " << str4 << std::endl;
	std::cout << "str5 : " << str5 << std::endl;
	std::cout << "str6 : " << str6 << std::endl;
	std::cout << "str8 : " << str8 << std::endl;

	return 0;
}

/*
	string literal 을 선언해서 변수에 대입한 후, 변경하면 어떻게 될 지 확인해보려고 했는데
	최신 컴파일러에서는 애초에 const char* 가 아니면 변수 대입이 안되게 막혀있네.
*/
void update_string_literal_test()
{
	const char*	ptr = "hello";
	//char*	ptr = "hello";
	//ptr[1] = 'a';
}
