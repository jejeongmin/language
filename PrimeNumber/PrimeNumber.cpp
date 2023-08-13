#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include <set>

using namespace std;
using namespace chrono;

int main()
{
	std::vector<std::function<bool(int)>> funcs;

	// simple loop
	funcs.push_back([](int primeNumber)
		{
			if (primeNumber < 2)
				return false;

			for (int i = 2; i < primeNumber; ++i)
			{
				if (0 == primeNumber % i)
					return false;
			}

			return true;
		});

	// advanced loop
	funcs.push_back([](int primeNumber)
		{
			if (primeNumber < 2)
				return false;

			int	skipableNumber = static_cast<int>(primeNumber / 2);

			for (int i = 2; i < primeNumber; ++i)
			{
				if (0 == primeNumber % i)
					return false;

				// if loop count over half value, it must prime number
				// additional loop operation do not need
				if (i == skipableNumber)
					return true;
			}

			return true;
		});

	// get sqrt and loop
	funcs.push_back([](int primeNumber)
		{
			if (primeNumber < 2)
				return false;

			int	count = static_cast<int>(sqrt(primeNumber));

			for (int i = 2; i < count; ++i)
			{
				if (0 == primeNumber % i)
					return false;
			}

			return true;
		});

	cout << "select [get prime number] function" << endl;
	cout << "0. simple loop" << endl;
	cout << "1. advanced loop" << endl;
	cout << "2. sqrt loop" << endl;
	cout << ">" << endl;

	int	selection = 0;
	cin >> selection;

	if (selection > funcs.size())
	{
		cout << " there is not function for " << selection;
		return 0;
	}

	int		loopCount = 100000;
	int		primeNumberCount = 0;

	system_clock::time_point start = system_clock::now();

	for (int i = 1; i < loopCount; ++i)
	{
		bool	result = funcs[selection](i);

		if (result)
		{
			++primeNumberCount;
		}
	}

	system_clock::time_point end = system_clock::now();
	milliseconds milliSec = duration_cast<milliseconds>(end - start);

	cout << "1 to " << loopCount << " have " << primeNumberCount << " prime number." << endl;
	cout << "It takes " << milliSec.count() << " milliseconds." << endl;
}