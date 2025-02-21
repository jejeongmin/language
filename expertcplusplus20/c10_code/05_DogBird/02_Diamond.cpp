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
	using Dog::eat;	// Diamon ������ ���� �� ��������� Dog::eat ���� ����ϰڴٴ� ����
};

int main()
{
	DogBird myConfusedAnimal;
	myConfusedAnimal.eat();

	return 0;
}

#endif