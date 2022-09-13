#include <vector>
using namespace std;

int main()
{
	vector<int> intVector(10);

	auto it = begin(intVector);
	it += 5;	// 5 th
	--it;		// 4 th
	*it = 4;	// intVector[4] = 4

	return 0;
}
