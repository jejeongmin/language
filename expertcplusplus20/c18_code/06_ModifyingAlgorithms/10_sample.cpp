#include <cstddef>
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

/*
	sample() 알고리즘은 인수로 지정된 원본 범위에서 무작위로 n개의 원소를 골라서 리턴하고,
	이를 대상 범위에 지정한다.

	shuffle() 알고리즘은 주어진 범위의 원소를 무작위 순으로 재정렬하며 성능은 선형 시간이다.
	이 알고리즘은 카드를 섞는 것과 같은 작업에 유용하다. 
*/
int main()
{
	vector<int> vec{ 1,2,3,4,5,6,7,8,9,10 };
	const size_t numberOfSamples = 5;
	vector<int> samples(numberOfSamples);

	random_device seeder;
	const auto seed = seeder.entropy() ? seeder() : time(nullptr);
	default_random_engine engine(static_cast<default_random_engine::result_type>(seed));

	for (int i = 0; i < 6; ++i) {
		sample(cbegin(vec), cend(vec), begin(samples), numberOfSamples, engine);

		for (const auto& sample : samples) { cout << sample << " "; }
		cout << endl;
	}

	return 0;
}
