#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

bool isEven(int num)
{
	return num % 2 == 0;
}

/*
	std::function 대신 람다 구현이 대체로 더 나은 선택이다.
	그러나 콜백을 클래스의 멤버 변수에 저장해야 하는 경우에는 람다 표현식은 아예 불가능하고
	함수 포인터 보다는 std::function 이 더 나은 선택일 때가 많다.
	물론 함수객체도 괜찮지만 상대적으로 구현이 더 커질 수 있으니..
*/
int main()
{
	vector<int> vec{ 1,2,3,4,5,6,7,8,9 };

	function<bool(int)> fcn = isEven;
	auto result = find_if(cbegin(vec), cend(vec), fcn);
	if (result != cend(vec)) {
		cout << "First even number: " << *result << endl;
	} else {
		cout << "No even number found." << endl;
	}

	// lambda 구현
	{
		auto result = find_if(cbegin(vec), cend(vec), [](int num) { return num % 2 == 0; });
		if (result != cend(vec)) {
			cout << "First even number: " << *result << endl;
		}
		else {
			cout << "No even number found." << endl;
		}
	}	

	return 0;
}

