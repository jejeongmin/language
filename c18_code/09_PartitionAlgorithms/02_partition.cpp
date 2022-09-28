#include <algorithm>
#include <vector>
#include <iostream>

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
	partition() 알고리즘은 predicate 에서 true 를 리턴하는 원소가 false 를 리턴하는 원소보다
	앞에 나오도록 정렬한다.
*/
int main()
{
	vector<int> vec;

	populateContainer(vec);
	
	partition(begin(vec), end(vec), [](int i){ return i % 2 == 0; });

	cout << "Partitioned result: ";
	for (const auto& i : vec) { cout << i << " "; }
	cout << endl;

	return 0;
}
