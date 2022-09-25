#include <numeric>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

double arithmeticMean(const vector<int>& nums)
{
	double sum = accumulate(cbegin(nums), cend(nums), 0);// 합에 대한 초기값을 세번째 인자로 받는다.  0 은 덧셈의 항등원,
	return sum / nums.size();
}

int product(int num1, int num2)
{
	return num1 * num2;
}

double geometricMean(const vector<int>& nums)
{
	double mult = accumulate(cbegin(nums), cend(nums), 1, product);	// 곱에 대한 초기값을 세번째 인자로 받는다. 1은 곱셈의 항등원
	return pow(mult, 1.0 / nums.size());
}

double geometricMeanLambda(const vector<int>& nums)
{
	double mult = accumulate(cbegin(nums), cend(nums), 1,
		[](int num1, int num2){ return num1 * num2; });
	return pow(mult, 1.0 / nums.size());
}

int main()
{
	vector<int> myVector;

	int num;
	while (true) {
		cout << "Enter a test score to add (0 to stop): ";
		cin >> num;
		if (num == 0) {
			break;
		}
		myVector.push_back(num);
	}

	cout << "The arithmetic mean is " << arithmeticMean(myVector) << endl;
	cout << "The geometric mean is " << geometricMean(myVector) << endl;
	cout << "The geometric mean (Lambda version) is " << geometricMeanLambda(myVector) << endl;

	return 0;
}
