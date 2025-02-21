#include <iostream>
#include <vector>
#include <algorithm>

class IObserver
{
public:
	virtual ~IObserver() = default;  // 항상 가상 소멸자로 정의한다.
	virtual void notify() = 0;
};

class ConcreteObserver1 : public IObserver
{
public:
	void notify() override { std::cout << "ConcreteObserver1::notify()" << std::endl; }
};

class ConcreteObserver2 : public IObserver
{
public:
	void notify() override { std::cout << "ConcreteObserver2::notify()" << std::endl; }
};



class Observable
{
public:
	virtual ~Observable() = default;  // 항상 가상 소멸자로 지정한다.

	// 옵저버를 추가한다. 소유권은 이전되지 않는다.
	void addObserver(IObserver* observer)
	{
		mObservers.push_back(observer);
	}

	// 지정한 옵저버를 제거한다.
	void removeObserver(IObserver* observer)
	{
		mObservers.erase(
			std::remove(begin(mObservers), end(mObservers), observer),
			end(mObservers));
	}

protected:
	void notifyAllObservers()
	{
		for (auto* observer : mObservers)
			observer->notify();
	}

private:
	std::vector<IObserver*> mObservers;
};



class ObservableSubject : public Observable
{
public:
	void modifyData()
	{
		// ...
		notifyAllObservers();
	}
};


/*
	Observer 패턴은 Observer 역할을 하는 객체가 관찰 대상(Observable) 객체로부터 알림을 받도록 구현할 때 사용한다.
	그러기 위해서 각 Observer 객체를 Observable 객체로 등록해야 한다.
	Observable 객체의 상태가 변하면 현재 등록된 Observer에 알림을 보낸다.

	Observer 패턴의 가장 큰 장점은 결합도를 낮춘다는 것이다.
	Observable 클래스는 자신을 관찰하는 Observer 의 구체적인 타입을 몰라도 된다.
	IObserver 와 같은 기본 인터페이스만 알면 된다.
*/
int main()
{
	ObservableSubject subject;

	ConcreteObserver1 observer1;
	subject.addObserver(&observer1);

	subject.modifyData();

	std::cout << std::endl;

	ConcreteObserver2 observer2;
	subject.addObserver(&observer2);

	subject.modifyData();

	return 0;
}