#include <cstdlib>
#include <iostream>
using namespace std;

void memoryLeak()
{
	int* p = new int[1000];
	return; // ����! p�� �������� �ʾҴ�.
}

void mismatchedFree()
{
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = new int;
	int* p3 = new int[1000];
	delete p1;    // ����! free()�� ����ؾ� �Ѵ�.
	delete [] p2; // ����! delete�� ����ؾ� �Ѵ�.
	free(p3);     // ����! delete []�� ����ؾ� �Ѵ�.
}

void doubleFree()
{
	int* p1 = new int[1000];
	delete [] p1;
	int* p2 = new int[1000];
	delete [] p1; // ����! p1�� �� �� �����ߴ�.
} // ����! p2�� �޸𸮿� ������ �߻��Ѵ�.

void freeUnallocated()
{
	int* p = reinterpret_cast<int*>(10000);
	delete p; // ����! p�� �ùٸ� �����Ͱ� �ƴϴ�.
}

void freeStack()
{
	int x;
	int* p = &x;
	delete p; // ����! ���� �޸� ����
}

void accessInvalid()
{
	int* p = reinterpret_cast<int*>(10000);
	*p = 5;    // ����! p�� �߸��� �����ʹ�.
}

void accessFreed()
{
	int* p1 = new int;
	delete p1;
	int* p2 = new int;
	*p1 = 5; // ����!. p1�� ����Ű�� �޸𸮴� �̹� �����ƴ�.
}

void accessElsewhere()
{
	int x, y[10], z;
	x = 0;
	z = 0;
	for (int i = 0; i <= 10; i++) {
		y[i] = 5; // ����! i==10�϶� y�� ���Ҵ� �迭�� ��踦 �����.
	}
}

/*
	VS2017 ���� �����ϸ� ������ �ܰ迡�� �����Ѵ�.

	���� ���带 ���� nullptr �� �ʱ�ȭ�ϵ��� �����ߴ�
*/
void readUninitialized()
{
	//int* p;	// ���� �ڵ�
	int* p = nullptr;
	cout << *p << endl; // ����! p�� �ʱ�ȭ���� �ʾҴ�.
}

int main()
{
	cout << "Memory leak" << endl;
	memoryLeak();
	cout << "Mismatched Free" << endl;
	mismatchedFree();
	cout << "Double Free" << endl;
	doubleFree();		// vs2017 ���� ���� ����
	cout << "Free Unallocated" << endl;
	freeUnallocated();	// vs2017 ���� ���� ����
	cout << "Free Stack" << endl;
	freeStack();		// vs2017 ���� ���� ����
	cout << "Access Invalid" << endl;
	accessInvalid();	// vs2017 ���� ���� ����
	cout << "Access Freed" << endl;
	accessFreed();		// vs2017 ���� ���� ����
	cout << "Access Elsewhere" << endl;
	accessElsewhere();	// vs2017 ���� ���� ����
	cout << "Read Uninitialized" << endl;
	readUninitialized();

	return 0;
}
