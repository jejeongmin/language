//#define MAIN_2
#ifdef MAIN_2

class MyClass
{
public:
	// 레퍼런스 멤버 변수는 생성자에서 initializer 를 써서 초기화해줘야 한다.
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