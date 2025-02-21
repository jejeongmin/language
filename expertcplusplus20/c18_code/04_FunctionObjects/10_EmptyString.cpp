#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
	메서드 포인터를 호출하는 코드는 일반 함수 포인터를 호출할 때와 다르다.
	메서드 포인터는 반드시 객체의 문맥 안에서 호출해야 하기 때문이다.
	c++은 이를 위해 mem_fn() 이라는 변환 한수를 제공한다.
*/
void findEmptyString(const vector<string>& strings)
{
	auto endIter = end(strings);

	// mem_fn()
	auto it = find_if(begin(strings), endIter, mem_fn(&string::empty));

	// 람다 표현식 버전
	//auto it = find_if(begin(strings), endIter,
	//	[](const string& str){ return str.empty(); });

	if (it == endIter) {
		cout << "No empty strings!" << endl;
	} else {
		cout << "Empty string at position: "
			<< static_cast<int>(it - begin(strings)) << endl;
	}
}

int main()
{
	vector<string> myVector;

	string one = "blah";
	string two = "";
	myVector.push_back(one);
	myVector.push_back(one);
	myVector.push_back(two);
	myVector.push_back(one);

	findEmptyString(myVector);

	return 0;
}
