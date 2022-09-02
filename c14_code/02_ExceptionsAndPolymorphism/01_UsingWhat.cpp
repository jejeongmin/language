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
/*
	exception 객체는 항상 const 참조로 받는 것이 좋다.
	exception 객체를 값으로 받으면 다형성이 적용안될 뿐 더러
	객체 슬라이싱이 발생해 값이 짤릴 수 있다.
*/
int main()
{
	const string fileName = "IntegerFile_none.txt";
	vector<int> myInts;

	try {
		myInts = readIntegerFile(fileName);
	} catch (const invalid_argument& e) {
		cerr << e.what() << endl;
		return 1;
	} catch (const runtime_error& e) {
		cerr << e.what() << endl;
		return 2;
	}

	for (const auto& element : myInts) {
		cout << element << " ";
	}
	cout << endl;

	return 0;
}
