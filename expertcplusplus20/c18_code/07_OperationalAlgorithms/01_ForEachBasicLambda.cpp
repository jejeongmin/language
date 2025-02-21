#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

/*
	for_each 를 소개하지만
	대부분 범위 기반 for 문을 사용하는 것이 코드를 작성하기도, 읽기도 쉽다
*/
int main()
{
	map<int, int> myMap = { { 4, 40 }, { 5, 50 }, { 6, 60 } };
	for_each(cbegin(myMap), cend(myMap), [](const auto& p)
		{ cout << p.first << "->" << p.second << endl; });

	return 0;
}
