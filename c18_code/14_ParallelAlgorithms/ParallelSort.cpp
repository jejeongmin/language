#include <algorithm>
#include <iostream>
#include <vector>
#include <execution>

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
	for_each, all_of, copy, count_if, find, replace, search, sort, transform 등이
	모두 병렬 실행을 지원하는 알고리즘이다.
	병렬 실행을 지원하는 알고리짐은 소위 실행 정책이라 부르는 옵션을 첫번째 매개변수로 받는다.

	sequenced_policy				seq
	paralled_policy					par
	paralled_unsequenced_policy		par_unseq

	par_unseq 경우는 콜백 함수에서 제약 사항이 많다.
	메모리를 할당하거나 해제할 수 없고
	뮤텍스를 획득할 수 없고
	잠금에 제약이 없는 std::atomic 을 사용할 수 없다.

	나머지 정책들은 제약을 두지 않는다.

	병렬 알고리즘은 race 나 deadlock 에 대한 대비책을 따로 제공하지 않기 때문에
	알고리즘을 병렬로 실행할 때 이러한 상황에 직접 개발자가 대처해야 한다.
*/
int main()
{
	vector<int> myVector;
	populateContainer(myVector);

	cout << "Before sorting:" << endl;
	for (const auto& i : myVector) { cout << i << " "; }
	cout << endl;

	sort(std::execution::par, begin(myVector), end(myVector));

	cout << "After sorting:" << endl;
	for (const auto& i : myVector) { cout << i << " "; }
	cout << endl;
}
