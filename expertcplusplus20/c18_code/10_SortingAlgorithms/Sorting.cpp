#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

// int 타입 컨테이너에 원소를 채우는 함수 템플릿
// 이때 컨테이너는 반드시 push_back()을 제공해야 한다.
template<typename Container>
void populateContainer(Container& cont)
{
	int num;

	while (true) {
		cout << "Enter a number (0 to quit): ";
		cin >> num;
		if (num == 0) {
			break;
		}
		cont.push_back(num);
	}
}

/*
	stable_sort() 는 정렬 후에 원본에 나온 순서를 그대로 유지한다.
	is_sorted() 는 주어진 범위가 정렬된 상태면 true 를 리턴한다.
	is_sorted_until() 은 반복자를 리턴하는데, 이 반복자 앞에 나온 원소까지는 모두 정렬된 상태이다.
*/
int main()
{
	vector<int> vec;
	populateContainer(vec);

	sort(begin(vec), end(vec), greater<>());

	for (const auto& i : vec) { cout << i << " "; }
	cout << endl;

	return 0;
}
