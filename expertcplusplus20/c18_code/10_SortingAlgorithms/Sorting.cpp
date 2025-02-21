#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

// int Ÿ�� �����̳ʿ� ���Ҹ� ä��� �Լ� ���ø�
// �̶� �����̳ʴ� �ݵ�� push_back()�� �����ؾ� �Ѵ�.
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
	stable_sort() �� ���� �Ŀ� ������ ���� ������ �״�� �����Ѵ�.
	is_sorted() �� �־��� ������ ���ĵ� ���¸� true �� �����Ѵ�.
	is_sorted_until() �� �ݺ��ڸ� �����ϴµ�, �� �ݺ��� �տ� ���� ���ұ����� ��� ���ĵ� �����̴�.
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
