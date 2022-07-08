#include <memory>
#include <iostream>

//#define MAIN_3

using namespace std;

class Simple
{
public:
	Simple() { cout << "Simple constructor called!" << endl; }
	~Simple() { cout << "Simple destructor called!" << endl; }
};

// 객체 하나를 shared_ptr 두 개로 각자 가르키면, 두 shared_ptr 이 레퍼런스 카운터도 각자
// 관리할테고, 그러면 ref count 가 0이 되면 mySimple 을 두번 delete 해서 뻑이 난다.
void doubleDelete()
{
	Simple* mySimple = new Simple();
	shared_ptr<Simple> smartPtr1(mySimple);
	shared_ptr<Simple> smartPtr2(mySimple);
}

// 위처럼 객체 하나를 두 개의 shared_ptr 로 가르키지 말고, 아래와 같이 복사본을 이용해 사용해야 한다.
// 그래야 ref count 가 같이 관리가 되니까.
void noDoubleDelete()
{
	auto smartPtr1 = make_shared<Simple>();
	shared_ptr<Simple> smartPtr2(smartPtr1);
}

#ifdef MAIN_3

int main()
{
	//doubleDelete();  // 버그, 프로그램이 뻗을 수 있다.
	noDoubleDelete();

	return 0;
}

#endif