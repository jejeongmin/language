#include <vector>

using namespace std;

int main()
{
	vector<int> intVector;

	auto iter = end(intVector);
	*iter = 10; // ����! end iter�� ���� ���Ҹ� ����Ű�� �ʰ� �ִ�.

	vector<int> vectorOne(10);
	vector<int> vectorTwo(10);

	// ���Ϳ� ���Ҹ� ä���.

	// ����! ���� �ٸ� �����̳��� ���ͷ����͸� ���ϸ� ���� ������ ���� �� �ִ�.
	for (auto iter = begin(vectorTwo); iter != end(vectorOne); ++iter)
	{
		// ���� ����
	}

	return 0;
}
