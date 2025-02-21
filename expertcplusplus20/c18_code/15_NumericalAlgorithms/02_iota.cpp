#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

// 주어진 범위에서 주어진 값으로 시작해서 operator++로 값을 순차적으로 생성하는 방식으로 값에 대한 시퀀스를 만든다.
int main()
{
	vector<int> vec(10);
	iota(begin(vec), end(vec), 5);
	for (auto& i : vec) { cout << i << " "; }
	cout << endl;

	return 0;
}