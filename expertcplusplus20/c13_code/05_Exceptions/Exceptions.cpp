#include <iostream>
#include <stdexcept>

using namespace std;

/*
	출력 에러가 발생하는 경우는 다양하다.
	예를 들어
	존재하지 않는 파일을 열거나, 디스크가 꽉 차서 쓰기 연산을 처리할 수 없을 때 에러가 발생한다.
*/
int main()
{
	cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
	try {
		cout << "Hello World." << endl;
	} catch (const ios_base::failure& ex) {
		cerr << "Caught exception: " << ex.what()
			<< ", error code = " << ex.code() << endl;
	}
	return 0;
}
