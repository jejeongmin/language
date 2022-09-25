#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

/*
	find() 함수에서 원소를 찾지 못하면 내부 컨테이너의 끝 반복자가 아니라 함수를 호출할 때 지정한 끝 반복자를 리턴한다.
*/
int main()
{
	int num;

	vector<int> myVector;
	while (true) {
		cout << "Enter a number to add (0 to stop): ";
		cin >> num;
		if (num == 0) {
			break;
		}
		myVector.push_back(num);
	}

	while (true) {
		cout << "Enter a number to lookup (0 to stop): ";
		cin >> num;
		if (num == 0) {
			break;
		}
		
		auto endIt = cend(myVector);

		auto it = find(cbegin(myVector), endIt, num);
		if (it == endIt) {
			cout << "Could not find " << num << endl;
		} else {
			cout << "Found " << *it << endl;
		}

		// C++17부터 추가된 if문의 이니셜라이저를 사용한 코드
		if (auto it = find(cbegin(myVector), endIt, num); it == endIt) {
			cout << "Could not find " << num << endl;
		} else {
			cout << "Found " << *it << endl;
		}
	}

	return 0;
}
