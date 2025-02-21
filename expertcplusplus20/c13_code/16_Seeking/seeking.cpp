#include <iostream>
#include <fstream>

using namespace std;

/*
	seekg 와 seekp 을 구분하는 이유는 각각 get, put 으로 파일 스트림처럼 입력과 출력을 모두 가질 때가 있기 때문이다.
	이럴 때는 읽는 위치와 쓰는 위치를 별도로 관리해야 한다.
*/
int main()
{
	ofstream fout("test.out");
	if (!fout) {
		cerr << "Error opening test.out for writing" << endl;
		return 1;
	}

	// 1. "12345"란 스트링을 출력한다.
	fout << "12345";

	// 2. 현재 위치가 5인지 확인한다.
	streampos curPos = fout.tellp();
	if (5 == curPos) {
		cout << "Test passed: Currently at position 5" << endl;
	} else {
		cout << "Test failed: Not at position 5" << endl;
	}

	// 3. 스트림의 현재 위치를 2로 옮긴다.
	fout.seekp(2, ios_base::beg);

	// 4. 위치 2에 0을 쓰고 스트림을 닫는다.
	fout << 0;
	fout.close();

	// 5. test.out에 대한 입력 스트림을 연다.
	ifstream fin("test.out");
	if (!fin) {
		cerr << "Error opening test.out for reading" << endl;
		return 1;
	}

	// 6. 첫 번째 토큰을 정수 타입의 값으로 읽는다.
	int testVal;
	fin >> testVal;
	if (!fin) {
		cerr << "Error reading from file" << endl;
		return 1;
	}

	// 7. 읽은 값이 12045인지 확인한다.
	const int expected = 12045;
	if (testVal == expected) {
		cout << "Test passed: Value is " << expected << endl;
	} else {
		cout << "Test failed: Value is not " << expected
			<< " (it was " << testVal << ")" << endl;
	}

	return 0;
}
