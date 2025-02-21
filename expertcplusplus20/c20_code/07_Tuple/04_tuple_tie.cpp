#include <iostream>
#include <string>
#include <tuple> 

using namespace std;

/*
	구조적 바인딩을 적용하지 않고 tuple 을 분리하려면, std::tie 라는 유틸리티 함수를 활용하면 된다.
	이 함수는 레퍼런스로 구성된 tuple 을 생성한다.
	
	tie(i, str, b) 라고 호출하면 i,str,b 에 대한 레퍼런스로 구성된 tuple 이 생성된다.
	여기에 대입 연산자를 이용하여 tuple t1 을 tie()의 결과에 대입한 것이다.

	구조적 바인딩이 훨씬사용하기 편리하다.
	std::ignore 가 된다는 장점 외에는 딱히 쓸 일이 없을 듯 하다.
	구조적 바인딩을 auto[i, , b] = t1; 와 같은 방식으로 지원해주면 좋을텐데.
*/
int main()
{
	tuple<int, string, bool> t1(16, "Test", true);

	{
		int i = 0;
		string str;
		bool b = false;
		cout << "Before: i = " << i << ", str = \"" << str << "\", b = " << b << endl;
		tie(i, str, b) = t1;
		cout << "After:  i = " << i << ", str = \"" << str << "\", b = " << b << endl;
	}

	{
		int i = 0;
		bool b = false;
		cout << "Before: i = " << i << ", b = " << b << endl;
		tie(i, std::ignore, b) = t1;
		cout << "After:  i = " << i << ", b = " << b << endl;
	}
	return 0;
}