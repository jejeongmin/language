#include <iostream>
#include <sstream>

using namespace std;

/*
	string �� �����͸� �� ���� std::ostringstream ��,
	�ݴ�� string ���� �����͸� ���� ���� std::istringstream Ŭ������ ����Ѵ�.
	�Ѵ� <sstream> ��� ���Ͽ� ���ǵǾ� �ִ�.
	ostringstream, istringstream �� ���� ostream �� istream �� ����ϹǷ� ���� ����� ��Ʈ��ó�� �ٷ� �� �ִ�.
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
