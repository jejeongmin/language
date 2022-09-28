#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
	반복문을 돌면서 erase 를 하는 건 굉장히 비효율적이다.
	vector 에서 메모리를 연속적으로 사용하기 위해 erase 를 위한 메모리 연산이
	상당히 많이 발생하기 때문이다.
*/
void removeEmptyStringsWithoutAlgorithms(vector<string>& strings)
{
	for (auto iter = begin(strings); iter != end(strings); ) {
		if (iter->empty())
			iter = strings.erase(iter);
		else
			++iter;
	}
}

/*
	이 문제는 소위 remove-erase 패턴으로 구현하는 것이 좋다.
	표준 라이브러리 알고리즘은 컨테이너를 다룰 때 반복자 인터페이스로만 접근한다.
	그래서 remove() 알고리즘은 컨테이너에서 원소를 직접 삭제하지 않고,
	주어진 값이나 프레디케이트를 만족하는 원소를 그렇지 않은 원소로 교체한다.
	이 작업은 이동 대입 연산으로 처리한다. 그러면 주어진 범위가 두 집합으로 분할된다.
	하나는 그대로 유지할 원소 집합이고, 다른 하나는 삭제할 원소 집합이다.
	remove()는 삭제할 범위의 첫번째 원소를 가르키는 반복자를 리턴한다.
	이 원소를 컨테이너에서 실제로 삭제하려면 먼저 remove() 알고리즘부터 적용한 뒤
	리턴된 반복자를 이용하여 컨테이너에 대해 erase()를 호출해서 반복자가 가르키는 원소들을
	한번에 모두 지운다. 이것이 바로 remove-erase 패턴이다.

*/
void removeEmptyStrings(vector<string>& strings)
{
	auto it = remove_if(begin(strings), end(strings),
		[](const string& str) { return str.empty(); });
	// 제거된 원소를 모두 지운다.
	strings.erase(it, end(strings));
}


int main()
{
	vector<string> myVector = { "", "one", "", "two", "three", "four" };

	for (auto& str : myVector) { cout << "\"" << str << "\"  "; }
	cout << endl;
	removeEmptyStrings(myVector);
	for (auto& str : myVector) { cout << "\"" << str << "\"  "; }
	cout << endl;

	return 0;
}
