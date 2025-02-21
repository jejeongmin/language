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

// ��ü �ϳ��� shared_ptr �� ���� ���� ����Ű��, �� shared_ptr �� ���۷��� ī���͵� ����
// �������װ�, �׷��� ref count �� 0�� �Ǹ� mySimple �� �ι� delete �ؼ� ���� ����.
void doubleDelete()
{
	Simple* mySimple = new Simple();
	shared_ptr<Simple> smartPtr1(mySimple);
	shared_ptr<Simple> smartPtr2(mySimple);
}

// ��ó�� ��ü �ϳ��� �� ���� shared_ptr �� ����Ű�� ����, �Ʒ��� ���� ���纻�� �̿��� ����ؾ� �Ѵ�.
// �׷��� ref count �� ���� ������ �Ǵϱ�.
void noDoubleDelete()
{
	auto smartPtr1 = make_shared<Simple>();
	shared_ptr<Simple> smartPtr2(smartPtr1);
}

#ifdef MAIN_3

int main()
{
	//doubleDelete();  // ����, ���α׷��� ���� �� �ִ�.
	noDoubleDelete();

	return 0;
}

#endif