#include <algorithm>
#include <vector>
#include <iostream>

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
	copy ��, copy_backward �� copy source �� copy target �� ��ġ�� �ȵȴ�.
	Ư���� ���ǿ��� ��ġ�� �� ����ϴ� ��찡 �ִٰ� ������,
	�׷� Ư���� ���� ��ﵵ ���� ���� ���� ����.
*/
int main()
{
	vector<int> vec1, vec2;

	populateContainer(vec1);

	vec2.resize(size(vec1));

	copy(cbegin(vec1), cend(vec1), begin(vec2));

	for (const auto& i : vec2) { cout << i << " "; }

	return 0;
}
