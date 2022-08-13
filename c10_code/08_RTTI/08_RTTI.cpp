#include <iostream>
#include <typeinfo>

using namespace std;

class Animal
{
public:
	virtual ~Animal() = default;
};

class Dog : public Animal
{
};

class Bird : public Animal
{
};

int main()
{
	Animal	*dog	= new Dog();
	Animal	*bird	= new Bird();

	if (typeid(*dog) == typeid(Dog))
	{
		std::cout << "Dog!!!" << std::endl;
	}

	if (typeid(*bird) != typeid(Dog))
	{
		std::cout << "not Dog!!!" << std::endl;
	}

	if (typeid(*bird) == typeid(Bird))
	{
		std::cout << "Bird!!!" << std::endl;
	}

	if (typeid(*dog) != typeid(Bird))
	{
		std::cout << "not Bird!!!" << std::endl;
	}

	delete dog;
	delete bird;

	return 0;
}