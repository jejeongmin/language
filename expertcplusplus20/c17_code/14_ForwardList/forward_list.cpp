#include <iostream>
#include <forward_list>

using namespace std;

/*
	before_begin() 은 begin() 바로 앞단계의 iterator 를 나타내며 닫힌 범위의 시작을 나타낸다.
	end() 가 실제 가장 마지막 노드의 다음 단계 노드인 것처럼
	before_begin() 은 가장 첫번째 노드의 이전 단계 노드이다.
*/
int main()
{
	// forward_list 세 개를 생성한다.
	// 이때 원소를 initializer_list로 초기화한다. (유니폼 초기화)
	// to initialize their elements (uniform initialization).
	forward_list<int> list1 = { 5, 6 };
	forward_list<int> list2 = { 1, 2, 3, 4 };
	forward_list<int> list3 = { 7, 8, 9 };

	// splice 연산으로 list1 앞에 list2를 추가한다.
	list1.splice_after(list1.before_begin(), list2);

	// list1 맨 앞에 숫자 0을 추가한다.
	list1.push_front(0);

	// list1 뒤에 list3을 추가한다.
	// 이를 위해 먼저 마지막 원소에 대한 반복자를 구한다.
	auto iter = list1.before_begin();
	auto iterTemp = iter;
	while (++iterTemp != end(list1)) {
		++iter;
	}
	list1.insert_after(iter, cbegin(list3), cend(list3));
	//list1.splice_after(iter, list3);

	// list1의 내용을 화면에 출력한다.
	for (auto& i : list1) {
		cout << i << ' ';
	}

	return 0;
}
