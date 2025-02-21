#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

using namespace std;

bool allTrue(const vector<bool>& flags)
{
	return accumulate(begin(flags), end(flags), true, logical_and<>());			// C++14 투명 연산자 펑터를 사용한 코드
	//return accumulate(begin(flags), end(flags), true, logical_and<bool>());	// C++14 이전 버전
}

bool anyTrue(const vector<bool>& flags)
{
	return accumulate(begin(flags), end(flags), false, logical_or<>());			// C++14 투명 연산자 펑터를 사용한 코드
	//return accumulate(begin(flags), end(flags), false, logical_or<bool>());	// C++14 이전 버전
}

/*
	allTrue 나 anyTrue 는 예를 보여주기 위해 만든 거고
	실제로는 알고리즘에서 사용되는 std::all_of, any_of, none_of 등을 사용한다.
	축약평가(short-circuiting)를 사용하기 때문에 더 빠르다.
*/
int main()
{
	vector<bool> myVector;
	int num;
	while (true) {
		cout << "Enter a value 0 or 1 to add (-1 to stop): ";
		cin >> num;
		if (num == -1) {
			break;
		}
		myVector.push_back(num == 1);
	}

	cout << "allTrue? " << (allTrue(myVector) ? "yes" : "no") << endl;
	cout << "anyTrue? " << (anyTrue(myVector) ? "yes" : "no") << endl;

	cout << "all_of ? " <<
		std::all_of(myVector.begin(), myVector.end(), [](bool value) { return value; })
		<< std::endl;

	cout << "any_of ? " <<
		std::any_of(myVector.begin(), myVector.end(), [](bool value) { return value; })
		<< std::endl;

	return 0;
}
