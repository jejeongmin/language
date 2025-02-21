#include <execution>
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

/*
	reduce �˰��� ���� ���� �ɼ��� �����ϸ� accumulate ���� ����ӵ��� �ξ� ������.
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
