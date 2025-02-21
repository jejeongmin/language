#include <iostream>

using namespace std;

class Animal
{
public:
	virtual void eat() = 0;
	virtual void sleep() { cout << "zzzzzz..." << endl; }
};

class Dog : public virtual Animal	// Ŭ���� ������ ��ȣ���� �߻��� ��� virtual ����� �޴� �͵� ���� ����̴�.
{
public:
	virtual void bark() { cout << "woof!" << endl; }
	virtual void eat() override { cout << "The dog ate." << endl; }
};

class Bird : public virtual Animal	// public ����� �ƴ�, private, protected ����� ������ ���̽� Ŭ������ �����ڰ� ���, ��ӿ��� ������ �����ڷ� ����ȴ�.
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
