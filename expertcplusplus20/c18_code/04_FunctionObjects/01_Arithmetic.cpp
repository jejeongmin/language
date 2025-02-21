#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

double geometricMean(const vector<int>& nums)
{
	double mult = accumulate(cbegin(nums), cend(nums), 1, multiplies<int>());
	return pow(mult, 1.0 / nums.size());
}

/*
	C++14 투명 연산자 펑터를 사용한 예

	간결할 뿐 아니라 실질적인 기능도 더 뛰어나다.
	int, double 등 이종 타입도 동일한 코드로 지원 가능하다.
	항상 투명 functor 를 사용하기 바란다.

*/
double geometricMeanTransparent(const vector<int>& nums)
{
	double mult = accumulate(cbegin(nums), cend(nums), 1, multiplies<>());
	return pow(mult, 1.0 / nums.size());
}

/*
	산술 함수 객체는 산술 연산자에 대한 래퍼에 불과하다.
	알고리즘에서 함수 객체를 콜백으로 사용하려면 반드시 컨테이너에 담김 객체에 
	해당연산(operator+ 나 operator*)를 구현해야 한다.
*/
int main()
{
	plus<int> myPlus;
	int res = myPlus(4, 5);
	cout << res << endl;

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

	cout << "The geometric mean is " << geometricMean(myVector) << endl;
	cout << "The geometric mean is (transparent function object) "
		<< geometricMeanTransparent(myVector) << endl;

	return 0;
}
