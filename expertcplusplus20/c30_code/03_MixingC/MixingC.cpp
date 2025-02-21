#include <stdio.h>

/*
	c ���� ������ �Լ� �̸��� ���� �����ε� ������ ����.
	���� C �����Ϸ��� ������ �Լ� �̸��� ���α׷��Ӱ� ���� �̸��� �����ϰų� ����� �ܼ��ϴ�.

	�׷��� c++ �� ������ �Լ� �̸��� ���� �����ε��� �����ϱ� ���� name mangling �� Ȱ���Ѵ�.

	void MyFunc(double);
	void MyFunc(int);
	void MyFunc(int, int);

	�� ���� ���� ���� c++ �����Ϸ��� 

	MyFunc_double
	MyFunc_int
	MyFunc_int_int

	�� ���� �������� ��Ŀ�� ������ �̸��� �ڵ� �����Ѵ�. ���� �ٷ� ���� �̸��� �����ϱ� ���� ���� ��Ģ�̸�
	MS Visual Studio ���� �Ʒ��� ���� ������ �̸� ��Ģ�� ����Ѵ�.

	?MyFunc@@YAXN@Z
	?MyFunc@@YAXH@Z
	?MyFunc@@YAXHH@Z

	c++ ǥ���� Ư���� �÷������� �Լ� �����ε��� �����ϴ� ����� ��ü������ �����ϰ� ���� �ʴ�.
	�̿� ���� name mangling �� ���� ǥ���� ���� ������ �������� �̸� ��Ģ�� �ٸ���.

	���� �Լ� �̸� ��Ģ�� c++ �����Ϸ� ����� �������� �ʵ���, name mangling �� �������� �ʵ��� �ϴ� Ű���尡 extern "C" �̴�.
*/

// extern ��� #1
extern "C" void MyFunc1()
{
	printf("MyFunc1()\n");
}

// extern ��� #2
extern "C" {
	void MyFunc2()
	{
		printf("MyFunc2()\n");
	}
}

// extern ��� #3
#ifdef __cplusplus
	extern "C" {
#endif
		void MyFunc3()
		{
			printf("MyFunc3()\n");
		}
#ifdef __cplusplus
	}
#endif

int main()
{
	int classId = 1; // C++�� �ƴ� C �����Ϸ��� �����ؾ� �Ѵ�.
	printf("class is %d\n", classId);

	MyFunc1();
	MyFunc2();
	MyFunc3();

	return 0;
}
