#include <filesystem>
#include <iostream>

using namespace std;
using namespace std::filesystem;

/*
	path 의 append 나 /= 연산자는 경로 구분자를 자동으로 추가하지만, concat 이나 += 는 그렇지 않다.
*/
int main()
{
	path p(L"D:\\Foo");
	p.append("Bar");
	p /= "Bar";
	cout << p << endl;

	return 0;
}
