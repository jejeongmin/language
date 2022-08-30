#include <iostream>
#include <sstream>

using namespace std;

/*
	string 에 데이터를 쓸 때는 std::ostringstream 을,
	반대로 string 에서 데이터를 읽을 때는 std::istringstream 클래스를 사용한다.
	둘다 <sstream> 헤더 파일에 정의되어 있다.
	ostringstream, istringstream 은 각각 ostream 과 istream 을 상속하므로 기존 입출력 스트림처럼 다룰 수 있다.
*/
int main()
{
	cout << "Enter tokens. Control+D (Unix) or Control+Z (Windows) to end." << endl;

	ostringstream outStream;

	while (cin) {
		string nextToken;

		cout << "Next token: ";
		cin >> nextToken;

		if (!cin || nextToken == "done")
			break;

		outStream << nextToken << "\t";
	}

	cout << "The end result is: " << outStream.str();

	return 0;
}
