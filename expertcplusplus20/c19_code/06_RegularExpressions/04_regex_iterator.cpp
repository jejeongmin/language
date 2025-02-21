#include <iostream>
#include <string>
#include <regex>

using namespace std;

/*
	한 개 이상의 단어를 검색하는 [\w]+ 정규 표현식을 정의했다.

	sregex_iterator 를 역참조하면 smatch 객체를 구할 수 있다.
	이 smatch 객체의 첫 번째 원소인 [0]를 접근하면 매치된 부분 스트링을 구할 수 있다.

	sregex_iterator iter(cbegin(str), cend(str), regex("[\\w]+")) 와 같은 형식으로
	사용하지 않도록 주의한다.
	 왜냐하면 iterator 가 내부적으로 정규 표현식에 대한 포인터를 가지고 
	우측값 정규 표현식을 인수로 받는 생성자를 명시적으로 delete 하기 때문에
	임시 regex 객체를 생성할 수 없다.
*/
int main()
{
	regex reg("[\\w]+");
	while (true) {
		cout << "Enter a string to split (q=quit): ";
		string str;
		if (!getline(cin, str) || str == "q")
			break;
		
		const sregex_iterator end;
		for (sregex_iterator iter(cbegin(str), cend(str), reg); iter != end; ++iter) {
			cout << "\"" << (*iter)[0] << "\"" << endl;
		}
	}

	return 0;
}