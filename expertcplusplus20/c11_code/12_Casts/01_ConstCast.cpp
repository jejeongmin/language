//#define MAIN_1

#ifdef MAIN_1
extern void ThirdPartyLibraryMethod(char* str);

void f(const char* str)
{
	ThirdPartyLibraryMethod(const_cast<char*>(str));
}

int main()
{
	// const -> non-const ĳ������ const_cast
	f("Hello World");

	// non-const -> const ĳ������ �Ʒ� ������� ����
	std::string	std = "c++";
	const std::string& conststr = std::as_const(str);

	return 0;
}
#endif