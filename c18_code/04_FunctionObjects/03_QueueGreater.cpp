#include <queue>
#include <functional>
#include <iostream>
using namespace std;

/*
	투명 연산자 펑터가 심지어 성능도 더 좋다.
	예를 들어 map<string>에 스트링 리터럴로 주어진 키로 조회 연산을 수행할 때
	비투명 연산자를 사용하면 불필요한 복제 연산이 발생할 수 있다.
	스트링 리터럴로부터 string 인스턴스를 생성하기 때문이다.
	투명 연산자로 된 비교자를 사용하면 이러한 복제 연산을 피할 수 있다.
*/
int main()
{
	priority_queue<int, vector<int>, greater<>> myQueue;		// C++14 투명 연산자 펑터를 사용한 예
	//priority_queue<int, vector<int>, greater<int>> myQueue;	// C++14 이전 버전 코드

	myQueue.push(3);
	myQueue.push(4);
	myQueue.push(2);
	myQueue.push(1);

	while (!myQueue.empty()) {
		cout << myQueue.top() <<  " ";
		myQueue.pop();
	}

	return 0;
}
