#include <iostream>

using namespace std;

#define MAIN_2

#ifdef MAIN_2

class Animal
{
public:
	virtual void eat() = 0;
};

class Dog : public Animal
{
public:
	virtual void bark() { cout << "woof!" << endl; }
	virtual void eat() override { cout << "The dog ate." << endl; }
};

class Bird : public Animal
{
public:
	virtual void chirp() { cout << "chirp!" << endl; }
	virtual void eat() override { cout << "The bird ate." << endl; }
};

class DogBird : public Dog, public Bird
{
public:
	using Dog::eat;	// Diamon 문제가 있을 때 명시적으로 Dog::eat 쪽을 상속하겠다는 선언
};

int main()
{
	DogBird myConfusedAnimal;
	myConfusedAnimal.eat();

	return 0;
}

#endif