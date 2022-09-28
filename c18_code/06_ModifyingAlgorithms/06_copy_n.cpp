#include <cstddef>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// int 타입 컨테이너에 원소를 채우는 함수 템플릿
// 이때 컨테이너는 반드시 push_back()을 제공해야 한다.
template<typename Container>
void populateContainer(Container& cont)
{
	int num;

	while (true) {
		cout << "Enter a number (0 to quit): ";
		cin >> num;
		if (num == 0) {
			break;
		}
		cont.push_back(num);
	}
}

/*
	copy_n 은 경계값 검사를 하지 않기 때문에 
	end()를 초과하지 않는 복사가 되도록 검사하는 코드를 직접 작성해야 한다.
*/
int main()
{
	vector<int> vec1, vec2;

	populateContainer(vec1);

	size_t cnt = 0;
	cout << "Enter number of elements you want to copy: ";
	cin >> cnt;
	cnt = min(cnt, size(vec1));
	vec2.resize(cnt);
	copy_n(cbegin(vec1), cnt, begin(vec2));
	for (const auto& i : vec2) { cout << i << " "; }

	cout << endl;

	return 0;
}
