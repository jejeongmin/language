//#define MAIN_2
#ifdef MAIN_2

class MyClass
{
public:
	// ���۷��� ��� ������ �����ڿ��� initializer �� �Ἥ �ʱ�ȭ����� �Ѵ�.
	MyClass(int& ref) : mRef(ref) {}

private:
	int& mRef;
};

int main()
{
	int i = 123;
	MyClass m(i);

	return 0;
}


#endif