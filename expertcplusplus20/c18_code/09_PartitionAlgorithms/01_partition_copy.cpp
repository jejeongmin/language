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
	partition_copy() 는 원본에 있는 원소를 복제해서 서로 다른 두 대상으로 분할한다.
	이때 둘 중 어느 대상에 원소를 보낼지는 predicate 의 실행 결과가 true 냐, false 냐에 따라 달라진다.

	partition_copy는 반복자 쌍을 반환한다. 각 요소는 복제된 컨테이너들이다.
*/
int main()
{
	vector<int> vec1, vecOdd, vecEven;

	populateContainer(vec1);

	vecOdd.resize(size(vec1));
	vecEven.resize(size(vec1));

	auto pairIters = partition_copy(cbegin(vec1), cend(vec1),
		begin(vecEven), begin(vecOdd),
		[](int i){ return i % 2 == 0; });

	vecEven.erase(pairIters.first, end(vecEven));
	vecOdd.erase(pairIters.second, end(vecOdd));

	cout << "Even numbers: ";
	for (const auto& i : vecEven) { cout << i << " "; }
	cout << endl << "Odd numbers: ";
	for (const auto& i : vecOdd) { cout << i << " "; }
	cout << endl;

	return 0;
}
