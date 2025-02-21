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

void funcOne()
{
	string str1;
	string* str2 = new string();
	funcTwo();
	delete str2;			// ����� �޸𸮰� ���ǵȴ�.
}

void funcTwo()
{
	ifstream fileStream;
	fileStream.open("filename");
	throw exception();
	fileStream.close();		// ����� ���� ������ fileStream �� �Ҹ��ڰ� ȣ��Ǹ鼭 close �� ó���ȴ�.
}
