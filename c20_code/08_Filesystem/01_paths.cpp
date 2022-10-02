#include <filesystem>
#include <iostream>

using namespace std;
using namespace std::filesystem;

/*
	L - wide character, R - raw string
*/
int main()
{
	path p1(LR"(D:\Foo\Bar)");
	path p2(L"D:/Foo/Bar");
	cout << p1 << endl;
	cout << p2 << endl;

	return 0;
}
