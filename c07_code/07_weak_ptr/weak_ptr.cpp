#include <memory>
#include <iostream>

using namespace std;

class Simple
{
public:
	Simple() { cout << "Simple constructor called!" << endl; }
	~Simple() { cout << "Simple destructor called!" << endl; }
};

void useResource(weak_ptr<Simple>& weakSimple)
{
	auto resource = weakSimple.lock();	// weak_ptr 의 lock 을 호출하면, 연결된 shared_ptr 을 넘겨받는다.
	if (resource) {
		cout << "Resource still alive." << endl;
	} else {
		cout << "Resource has been freed!" << endl;
	}
}

// shared_ptr 만 사용해서 자기 자신을 가르키는 순환 참조가 발생할 위험이 있을 때, weak_ptr 을 사용하면 좋다.
int main()
{
	auto sharedSimple = make_shared<Simple>();
	weak_ptr<Simple> weakSimple(sharedSimple);

	// weak_ptr를 사용한다.
	useResource(weakSimple);

	// shared_ptr를 리셋한다.
	// Simple 리소스에는 shared_ptr가 하나 뿐이므로
	// weak_ptr가 남아 있더라도 이렇게 하면 리소스를 해제한다. 
	sharedSimple.reset();

	// weak_ptr를 다시 한 번 사용한다.
	useResource(weakSimple);

    return 0;
}
