#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

/*
	컨테이너 인터페이스만 가이드라인에 따른다면 알고리즘은 독립적으로 구현 가능하다
*/
template <typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator find_all(InputIterator first, InputIterator last,
	OutputIterator dest, Predicate pred)
{
	while (first != last) {
		if (pred(*first)) {
			*dest = first;
			++dest;
		}
		++first;
	}
	return dest;
}


int main()
{
	vector<int> vec{ 3, 4, 5, 4, 5, 6, 5, 8 };
	vector<vector<int>::iterator> matches;

	find_all(begin(vec), end(vec), back_inserter(matches), [](int i){ return i == 5; });

	cout << "Found " << matches.size() << " matching elements: " << endl;

	for (const auto& it : matches) {
		cout << *it << " at position " << (it - cbegin(vec)) << endl;;
	}
	cout << endl;

	return 0;
}
