#include <iostream>

using namespace std;

/* 
void* �� int* �� �־�����, �����Ϸ��� nullptr �� � �����ε� �Լ��� ��� �� �� �ĺ��� ���ϳ�..
nullptr �� ��Ȯ�� Ư���� ���� ���� �� �ƴϰ� ���� pointer Ÿ���� �͸� ��Ȯ�� ��
NULL �� ���� ��Ȯ�� 0 ���� define �Ǿ� �����ϱ�.
*/

//void func(void* str) { cout << "void* version" << endl; }
//void func(int* str) { cout << "int* version" << endl; }
void func(char* str) {cout << "char* version" << endl;}
void func(int i) {cout << "int version" << endl;}

int main()
{
	func(NULL);
	func(nullptr);

	return 0;
}
