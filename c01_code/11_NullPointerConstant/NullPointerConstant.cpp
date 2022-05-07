#include <iostream>

using namespace std;

/* 
void* 나 int* 를 넣었더니, 컴파일러가 nullptr 을 어떤 오버로드 함수를 써야 할 지 식별을 못하네..
nullptr 이 명확한 특별한 형을 가진 건 아니고 단지 pointer 타입인 것만 명확한 듯
NULL 인 경우는 명확히 0 으로 define 되어 있으니까.
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
