#include <iostream>

using namespace std;

class Animal
{
public:
	virtual void eat() = 0;
	virtual void sleep() { cout << "zzzzzz..." << endl; }
};

class Dog : public virtual Animal	// 클래스 계층의 모호함이 발생할 경우 virtual 상속을 받는 것도 좋은 방법이다.
{
public:
	virtual void bark() { cout << "woof!" << endl; }
	virtual void eat() override { cout << "The dog ate." << endl; }
};

class Bird : public virtual Animal	// public 상속이 아닌, private, protected 상속을 받으면 베이스 클래스의 접근자가 모두, 상속에서 지정한 접근자로 변경된다.
{
public:
	virtual void chirp() { cout << "chirp!" << endl; }
	virtual void eat() override { cout << "The bird ate." << endl; }
};

class DogBird : public Dog, public Bird
{
public:
	virtual void eat() override { Dog::eat(); }
};

int main()
{
	DogBird myConfusedAnimal;
	myConfusedAnimal.sleep();

	return 0;
}
