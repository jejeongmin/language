#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>
#include <exception>

using namespace std;

vector<int> readIntegerFile(string_view fileName)
{
	ifstream inputStream(fileName.data());
	if (inputStream.fail()) {
		// 파일 열기 실패: 익셉션을 던진다.
		throw invalid_argument("Unable to open the file.");
	}

	// 파일에 담긴 정숫값을 하나씩 읽어서 벡터에 추가한다.
	vector<int> integers;
	int temp;
	while (inputStream >> temp) {
		integers.push_back(temp);
	}

	if (!inputStream.eof()) {
		// 파일 끝(EOF)에 도달하지 않았다.
		// 다시 말해 파일을 읽는 도중에 에러가 발생했다.
		// 따라서 익셉션을 던진다.
		throw runtime_error("Error reading the file.");
	}

	return integers;
}

void myTerminate()
{
	cout << "Uncaught exception!" << endl;
	exit(1);
}

/*
	처리되지 않은 예외를 만날 경우, 기본적으로 terminate 가 호출된다.
	set_terminate 호출을 통해 terminate 시 동작을 교체할 수 있다.
	덤프를 남기는 등의 동작을 이렇게 수행할 수 있다.
	set_terminate 는 새로운 terminate 동작을 지정하는 동시에, 현재 설정된 terminate 동작을 반환한다
	반환된 terminate function 을 저장해두었다가, 나중에 custom 한 terminate 동작을 필요로하지 않는 상황이 되면 다시 복원할 수 있다.
*/
int main()
{
	set_terminate(myTerminate);

	const string fileName = "IntegerFile_none.txt";
	vector<int> myInts = readIntegerFile(fileName);

	for (const auto& element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
