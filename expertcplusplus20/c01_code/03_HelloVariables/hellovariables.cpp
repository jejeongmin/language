// NOTE: ��ټ��� �����Ϸ��� �ʱ�ȭ���� ���� ������ ����ϸ� ��� ������ �߻��Ѵ�.
// �Ϻ� �����Ϸ��� ��Ÿ�ӿ� ���α׷����� ������ �߻���Ű�� �ڵ带 �����Ѵ�.

#include <iostream>
#include <initializer_list>

using namespace std;

int main()
{
	int uninitializedInt;
	int initializedInt = 7;

	// 10����, 8����, 16����, 2���� ���ͷ� ���� ����
	initializer_list<int> lst{ 123, 0173, 0x7b, 0b1111011 };

	// �ڸ��� ���� ����
	int	exampleInt = 123'456;
	double exampleDouble = 0.123'456f;

	//cout << uninitializedInt << " is a random value" << endl;	// �ֽ� �����Ϸ��� �ʱ�ȭ���� ���� ���� ��뿡 ���ؼ� ������ ������ �⺻���� �Ѵ�.
	cout << initializedInt << " was assigned an initial value" << endl;

	return 0;
}
