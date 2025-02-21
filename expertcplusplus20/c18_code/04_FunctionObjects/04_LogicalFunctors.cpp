#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

using namespace std;

bool allTrue(const vector<bool>& flags)
{
	return accumulate(begin(flags), end(flags), true, logical_and<>());			// C++14 ���� ������ ���͸� ����� �ڵ�
	//return accumulate(begin(flags), end(flags), true, logical_and<bool>());	// C++14 ���� ����
}

bool anyTrue(const vector<bool>& flags)
{
	return accumulate(begin(flags), end(flags), false, logical_or<>());			// C++14 ���� ������ ���͸� ����� �ڵ�
	//return accumulate(begin(flags), end(flags), false, logical_or<bool>());	// C++14 ���� ����
}

/*
	allTrue �� anyTrue �� ���� �����ֱ� ���� ���� �Ű�
	�����δ� �˰��򿡼� ���Ǵ� std::all_of, any_of, none_of ���� ����Ѵ�.
	�����(short-circuiting)�� ����ϱ� ������ �� ������.
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
