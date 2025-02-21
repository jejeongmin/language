#include <algorithm>
#include <iostream>
#include <vector>
#include <execution>

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
	for_each, all_of, copy, count_if, find, replace, search, sort, transform ����
	��� ���� ������ �����ϴ� �˰����̴�.
	���� ������ �����ϴ� �˰����� ���� ���� ��å�̶� �θ��� �ɼ��� ù��° �Ű������� �޴´�.

	sequenced_policy				seq
	paralled_policy					par
	paralled_unsequenced_policy		par_unseq

	par_unseq ���� �ݹ� �Լ����� ���� ������ ����.
	�޸𸮸� �Ҵ��ϰų� ������ �� ����
	���ؽ��� ȹ���� �� ����
	��ݿ� ������ ���� std::atomic �� ����� �� ����.

	������ ��å���� ������ ���� �ʴ´�.

	���� �˰����� race �� deadlock �� ���� ���å�� ���� �������� �ʱ� ������
	�˰����� ���ķ� ������ �� �̷��� ��Ȳ�� ���� �����ڰ� ��ó�ؾ� �Ѵ�.
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
