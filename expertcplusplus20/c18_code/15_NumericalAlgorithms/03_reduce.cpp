#include <execution>
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

/*
	reduce 알고리즘에 병렬 실행 옵셤을 지정하면 accumulate 보다 실행속도가 훨씬 빠르다.
*/
int main()
{
	auto	g = gcd(3, 18);
	auto	l = lcm(3, 18);

	cout << "greatest common divisor : " << g << endl;
	cout << "least common multiple : " << l << endl;

	vector<int> vec{ 1,3,6,4,6,9 };
	double result1 = std::accumulate(cbegin(vec), cend(vec), 0.0);
	double result2 = std::reduce(std::execution::par_unseq, cbegin(vec), cend(vec));

	cout << "std::accumulate value : " << result1 << endl;
	cout << "std::reduce value : " << result2 << endl;

	return 0;
}
