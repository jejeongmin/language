#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	cout << clamp(-3, 1, 10) << endl;	// 1
	cout << clamp(3, 1, 10) << endl;	// 3
	cout << clamp(22, 1, 10) << endl;	// 10
		
	return 0;
}
