#include <iostream>

using namespace std;

int main()
{
	//const char* str1 = "Hello "World"!";    // ����!
	const char* str2 = "Hello \"World\"!";
	const char* str3 = R"(Hello "World"!)";

	const char* str4 = "Line 1\nLine 2";
	const char* str5 = R"(Line 1
Line 2)";

	const char* str6 = R"(Is the following a tab character? \t)";

	//const char* str7 = R"(Embedded )" characters)";    // ����!
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
	string literal �� �����ؼ� ������ ������ ��, �����ϸ� ��� �� �� Ȯ���غ����� �ߴµ�
	�ֽ� �����Ϸ������� ���ʿ� const char* �� �ƴϸ� ���� ������ �ȵǰ� �����ֳ�.
*/
void update_string_literal_test()
{
	const char*	ptr = "hello";
	//char*	ptr = "hello";
	//ptr[1] = 'a';
}
