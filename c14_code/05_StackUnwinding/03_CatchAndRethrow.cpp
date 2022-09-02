#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

void funcOne();
void funcTwo();

int main()
{
	try {
		funcOne();
	} catch (const exception& /* e */) {
		cerr << "Exception caught!" << endl;
		return 1;
	}

	return 0;
}

/*
	예외 처리하게 되면 예외가 발생하는 순간, 즉시 함수에서 빠져나오기 때문에(stack 감기)
	메모리 할당 해둔 것은 catch 문 내에서 반드시 해제 해야 한다.
*/
void funcOne()
{
	string str1;
	string* str2 = new string();
	try {
		funcTwo();
	} catch (...) {
		delete str2;
		throw; // 예외를 다시 던진다.
	}
	delete str2;
}

void funcTwo()
{
	ifstream fileStream;
	fileStream.open("filename");
	throw exception();
	fileStream.close();
}
