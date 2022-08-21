#include <iostream>

namespace TestScope {
	void f();

	void f()
	{
		std::cout << "f\n";
	}
}
