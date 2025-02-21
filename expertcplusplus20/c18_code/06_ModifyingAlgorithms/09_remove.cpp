#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
	�ݺ����� ���鼭 erase �� �ϴ� �� ������ ��ȿ�����̴�.
	vector ���� �޸𸮸� ���������� ����ϱ� ���� erase �� ���� �޸� ������
	����� ���� �߻��ϱ� �����̴�.
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
	�� ������ ���� remove-erase �������� �����ϴ� ���� ����.
	ǥ�� ���̺귯�� �˰����� �����̳ʸ� �ٷ� �� �ݺ��� �������̽��θ� �����Ѵ�.
	�׷��� remove() �˰����� �����̳ʿ��� ���Ҹ� ���� �������� �ʰ�,
	�־��� ���̳� ����������Ʈ�� �����ϴ� ���Ҹ� �׷��� ���� ���ҷ� ��ü�Ѵ�.
	�� �۾��� �̵� ���� �������� ó���Ѵ�. �׷��� �־��� ������ �� �������� ���ҵȴ�.
	�ϳ��� �״�� ������ ���� �����̰�, �ٸ� �ϳ��� ������ ���� �����̴�.
	remove()�� ������ ������ ù��° ���Ҹ� ����Ű�� �ݺ��ڸ� �����Ѵ�.
	�� ���Ҹ� �����̳ʿ��� ������ �����Ϸ��� ���� remove() �˰������ ������ ��
	���ϵ� �ݺ��ڸ� �̿��Ͽ� �����̳ʿ� ���� erase()�� ȣ���ؼ� �ݺ��ڰ� ����Ű�� ���ҵ���
	�ѹ��� ��� �����. �̰��� �ٷ� remove-erase �����̴�.

*/
void removeEmptyStrings(vector<string>& strings)
{
	auto it = remove_if(begin(strings), end(strings),
		[](const string& str) { return str.empty(); });
	// ���ŵ� ���Ҹ� ��� �����.
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
