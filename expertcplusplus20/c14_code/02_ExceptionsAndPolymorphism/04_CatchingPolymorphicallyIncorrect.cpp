#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>

using namespace std;

vector<int> readIntegerFile(string_view fileName)
{
	ifstream inputStream(fileName.data());
	if (inputStream.fail()) {
		// 파일 열기 실패: 익셉션을 던진다.
		const string error = "Unable to open file "s + fileName.data();
		throw invalid_argument(error);
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
		const string error = "Unable to read file "s + fileName.data();
		throw runtime_error(error);
	}

	return integers;
}

int main()
{
	const string fileName = "IntegerFile_none.txt";
	vector<int> myInts;

	try {
		myInts = readIntegerFile(fileName);
	} catch (const exception& e) { // 버그: 베이스 클래스를 먼저 잡는다.
		cerr << e.what() << endl;
		return 1;
	} catch (const invalid_argument& /* e */) {
		// 여기는 절대 코드 제어가 오지 않는다. 바로 위의 catch 문에서 먼저 다 처리되버리기 때문에.
		// 파일 이름이 잘못된 경우를 처리한다.
	}

	for (const auto& element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
