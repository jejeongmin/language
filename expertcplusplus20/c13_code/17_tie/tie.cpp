#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ostream *prevstr;
	ofstream ofs;
	ofs.open("test.txt");

	cout << "tie example:" << endl;

	*cin.tie() << "This is inserted into cout";
	prevstr = cin.tie(&ofs);
	*cin.tie() << "This is inserted into the file";
	cin.tie(prevstr);

	ofs.close();

	return 0;
}

int main2()
{
	// ����: input.txt�� �ݵ�� �־�� �Ѵ�.
	// ������ ����� �ַ�� Ž���� â�� ������Ʈ �̸� ������ ���콺 ������ Ŭ���� ��
	// '���� Ž���⿡�� ���� ����'�� �����ؼ� ��Ÿ���� ���� �ȿ� input.txt ������ �����.
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	// inFile�� outFile�� �����Ѵ�.
	inFile.tie(&outFile);
	// outFile�� �ؽ�Ʈ�� ����. std::endl�� �ԷµǱ� �������� �������� �ʴ´�.
	outFile << "Hello there!";
	// outFile�� ���� �������� ���� ���´�.
	// inFile���� �ؽ�Ʈ�� �д´�. �׷��� outFile�� ���� flush()�� ȣ��ȴ�.

	string nextToken;
	inFile >> nextToken;
	// ���� outFile�� ����������.

	return 0;
}
