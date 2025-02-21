
//#define MAIN_2

#ifdef MAIN_2

class Simple 
{
public:
	Simple() { mIntPtr = new int(); }
	~Simple() { delete mIntPtr; }

	void setValue(int value) { *mIntPtr = value; }

private:
	int* mIntPtr;
};

// Simple* 의 레퍼런스, 그래서 Simple*& 이다. 원본 객체에 영향을 줘야 하니까.
void doSomething(Simple*& outSimplePtr)
{
	outSimplePtr = new Simple(); // 버그! 원본 객체를 삭제하지 않았다.
}

int main()
{
	Simple* simplePtr = new Simple(); // Simple 객체 하나를 할당한다.

	doSomething(simplePtr);

	delete simplePtr; // 두 번째 객체만 해제한다.

	return 0;
}

#endif
