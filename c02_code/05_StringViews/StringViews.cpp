#include <iostream>
#include <string>
#include <string_view>
#include <cstddef>

using namespace std;

/*
	함수의 인자로 string literal 을 전달하면, 컴파일러는 그 리터럴의 복사본이 담긴 string 객체를
	생성해서 함수에 전달하기 때문에 오버헤드가 발생한다. 간혹 이러한 함수에 대해 오버로딩 버전을 여러개 만들기도 하는데 좋은 선택은 아니다.
	c++17 부터 추가된 string_view 클래스를 사용하면 이러한 고민을 해결할 수 있다.
	아무런 성능 오버 헤드 없이 string 객체의 함수를 거의 유사하게 사용할 수 있다.
	단, string 과 string_view 가 완전히 동일하지는 않아, 두 객체를 순정 그대로 서로 연결/결합할 순 없다.
*/
string_view extractExtension(string_view fileName)
{
	return fileName.substr(fileName.rfind('.'));
}

int main()
{
	// C++ std::string.
	string fileName = R"(c:\temp\my file.ext)";
	cout << "C++ string: " << extractExtension(fileName) << endl;

	// C-스타일 스트링.
	const char* cString = R"(c:\temp\my file.ext)";
	cout << "C string: " << extractExtension(cString) << endl;

	// 스트링 리터럴.
	cout << "Literal: " << extractExtension(R"(c:\temp\my file.ext)") << endl;

	// 버퍼 길이가 주어진 로 스트링
	const char* raw = "test.ext";
	size_t length = 8;
	cout << "Raw: " << extractExtension(string_view(raw, length)) << endl;

	// 결과를 std::string에 대입
	string extension = extractExtension(fileName).data();

	return 0;
}
