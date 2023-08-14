#include "pch.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <random>

using namespace std;
using namespace std::chrono;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

int x;
int y;
int z;

int bad_result;

std::shared_mutex	mtx;

void writer()
{
	mt19937	gen;
	uniform_int_distribution<int> dist(1, 9);

	for (int i = 0; i < 10000000; ++i)
	{
		mtx.lock();
		x = dist(gen);
		y = dist(gen);
		z = x * y;
		mtx.unlock();
	}

	z = -1;
}

void reader()
{
	while (true)
	{
		mtx.lock();
		if (z < 0)
		{
			mtx.unlock();
			break;
		}

		if (z != x * y)
		{
			++bad_result;
		}

		mtx.unlock();
	}
}

void shared_reader()
{
	while (true)
	{
		mtx.lock_shared();
		if (z < 0)
		{
			mtx.unlock();
			break;
		}

		if (z != x * y)
		{
			++bad_result;
		}

		mtx.unlock_shared();
	}
}

void run(bool shared)
{
	x = 0;
	y = 0;
	z = 0;
	bad_result = 0;

	const int Nread = 7;
	thread threads[Nread + 1];

	auto start = chrono::high_resolution_clock::now();
	threads[0] = thread(writer);

	for (int i = 1; i <= Nread; ++i)
	{
		threads[i] = thread(shared ? shared_reader : reader);
	}

	for (thread& thr : threads)
	{
		thr.join();
	}

	auto stop = chrono::high_resolution_clock::now();

	cout << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "[ms]" << "bad_results = " << bad_result << endl;
}

//run(true);
//run(false);