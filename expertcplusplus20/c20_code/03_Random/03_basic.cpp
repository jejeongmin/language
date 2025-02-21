#include <iostream>
#include <random>
#include <ctime>

using namespace std;

/*
	무작위수 엔진에는 여러가지가 있으나 그 중 메르센 트위스터 알고리즘에 기반한 엔진이 범용적으로 좋다.
	파라메터가 아래와 가이 무려 14개개나 된다.

	파라메터의 값을 변경하는 것은 알고리즘에 대한 이해가 필요하니, 아래와 같이 정의된 mt19937 을 그래도 사용하자.
	typedef mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df,	11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253> mt19937;

	아래 코드는 1~99 사이의 난수를 메르센-트위스터 알고리즘으로 정규분포에 기반한 난수를 생성한다.
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

