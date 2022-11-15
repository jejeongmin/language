#include <iostream>

class Handler
{
public:
	virtual ~Handler() = default;

	Handler(Handler* nextHandler) : mNextHandler(nextHandler) { }

	virtual void handleMessage(int message)
	{
		if (mNextHandler)
			mNextHandler->handleMessage(message);
	}
private:
	Handler * mNextHandler;
};

class ConcreteHandler1 : public Handler
{
public:
	ConcreteHandler1(Handler* nextHandler) : Handler(nextHandler) {}

	void handleMessage(int message) override
	{
		std::cout << "ConcreteHandler1::handleMessage()" << std::endl;
		if (message == 1)
			std::cout << "Handling message " << message << std::endl;
		else {
			std::cout << "Not handling message " << message << std::endl;
			Handler::handleMessage(message);
		}
	}
};

class ConcreteHandler2 : public Handler
{
public:
	ConcreteHandler2(Handler* nextHandler) : Handler(nextHandler) {}

	void handleMessage(int message) override
	{
		std::cout << "ConcreteHandler2::handleMessage()" << std::endl;
		if (message == 2)
			std::cout << "Handling message " << message << std::endl;
		else {
			std::cout << "Not handling message " << message << std::endl;
			Handler::handleMessage(message);
		}
	}
};

/*
	책임 사슬 패턴은 특정한 동작을 여러 객체가 엮어서 처리할 때 사용한다.
	이 기법은 다형성을 활용하여 가장 구체적인 클래스가 먼저 호출되서 작업을 처리하거나, 이를 부모에게 전달하도록 구성한다.
	객체지향 계층 구조에 잘 맞아 떨어지면서도 굉장히 유연하게 코드를 구성할 수 있다.
	이 패턴의 단점은 프로그래머가 할 일이 많다는 것이다.
	파생 클래스에서 베이스 클래스 방향으로 이벤트를 전달하는 사슬이 끊어지면 이벤트가 중간에 사라져버린다.
	더 심각한 문제는 이벤트를 엉뚱한 클래스에 전달하면 무한 루프에 빠져버린다는 것이다.
*/
int main()
{
	ConcreteHandler2 handler2(nullptr);
	ConcreteHandler1 handler1(&handler2);

	handler1.handleMessage(1);
	std::cout << std::endl;

	handler1.handleMessage(2);
	std::cout << std::endl;

	handler1.handleMessage(3);
}