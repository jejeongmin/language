#include <iostream>
#include <fstream>

using namespace std;

/*
	파일 출력과 입력을 위해 std::ofstream 과 std::ifstream 클래스를 제공한다.
*/
int main(int argc, char* argv[])
{
	ofstream outFile("test.txt", ios_base::trunc);
	if (!outFile.good()) {
		cerr << "Error while opening output file!" << endl;
		return -1;
	}
	outFile << "There were " << argc << " arguments to this program." << endl;
	outFile << "They are: " << endl;
	for (int i = 0; i < argc; i++) {
		outFile << argv[i] << endl;
	}

	return 0;
}
