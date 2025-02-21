#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

/*
	보이어 무어 알고리즘은 성능이 뛰어나며, 방대한 텍스트에서 서브 스트링을 검색하는데 주로 사용된다.
	보이어 무어 알고리즘의 성능은 아래와 같다.

	탐색할 대상의 크기를 N, 패턴의 크기를 M 이라고 할 때
	패턴을 찾지 못한 경우 : O(N+M)
	패턴을 찾은 경우 : O(NM)
*/
int main()
{
	// C++17 보이어-무어 탐색 알고리즘
	string text = "This is the haystack to search a needle in.";
	string toSearchFor = "needle";
	auto searcher = std::boyer_moore_searcher(cbegin(toSearchFor), cend(toSearchFor));
	auto result = search(cbegin(text), cend(text), searcher);
	if (result != cend(text)) {
		cout << "Found the needle." << endl;
	} else {
		cout << "Needle not found." << endl;
	}

	return 0;
}
