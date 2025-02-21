#include <iostream>
#include <random>
#include <ctime>

using namespace std;

/*
	�������� �������� ���������� ������ �� �� �޸��� Ʈ������ �˰��� ����� ������ ���������� ����.
	�Ķ���Ͱ� �Ʒ��� ���� ���� 14������ �ȴ�.

	�Ķ������ ���� �����ϴ� ���� �˰��� ���� ���ذ� �ʿ��ϴ�, �Ʒ��� ���� ���ǵ� mt19937 �� �׷��� �������.
	typedef mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df,	11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253> mt19937;

	�Ʒ� �ڵ�� 1~99 ������ ������ �޸���-Ʈ������ �˰������� ���Ժ����� ����� ������ �����Ѵ�.
*/
int main()
{
	random_device seeder;
	const auto seed = seeder.entropy() ? seeder() : time(nullptr);
	mt19937 eng(static_cast<mt19937::result_type>(seed));

	uniform_int_distribution<int> dist(1, 99);
	cout << dist(eng) << endl;

	return 0;
}

