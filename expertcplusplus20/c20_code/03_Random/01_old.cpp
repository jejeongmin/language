#include <iostream>
#include <ctime>

using namespace std;

/*
	������ rand() �Լ��� 0�� RAND_MAX(32767 �̻�) ������ ���������� �����Ѵ�. 	���� �ڸ� ��Ʈ���� ���������� �׸� ���� �ʴ�.

	����Ʈ���� ����� �������� ������� ������ �ǹ��� ���������� ������ �� ����.
	�׷��� �ǻ�(pseudo) �������� �������� �θ���. �������� ��ó�� ���̰� ����� ���� ���Ŀ� ���� �����ϱ� �����̴�.
*/
int getRandom(int min, int max)
{
	return (rand() % static_cast<int>(max + 1 - min)) + min;
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
	cout << rand() << endl;

	cout << getRandom(1, 6) << endl;

	return 0;
}

