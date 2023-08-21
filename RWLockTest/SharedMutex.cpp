#include "pch.h"
#include "SharedMutex.h"
#include <thread>
#include <random>

using namespace std;

void SharedMutex::SetUp()
{
	_x = 0;
	_y = 0;
	_z = 0;
	_bad_result = 0;
}

void SharedMutex::TearDown()
{

}

TEST_F(SharedMutex, 01_ExclusiveReadWriteLock_Test)
{
	const int Nread = 7;
	thread threads[Nread + 1];

	threads[0] = thread([this] {
			mt19937	gen;
			uniform_int_distribution<int> dist(1, 9);

			for (int i = 0; i < 10000000; ++i)
			{
				_mtx.lock();
				_x = dist(gen);
				_y = dist(gen);
				_z = _x * _y;
				_mtx.unlock();
			}
			_z = -1;
		});

	for (int i = 1; i <= Nread; ++i)
	{
		threads[i] = thread([this]() {
				while (true)
				{
					_mtx.lock();
					if (_z < 0)
					{
						_mtx.unlock();
						break;
					}

					if (_z != _x * _y)
					{
						++_bad_result;
					}

					_mtx.unlock();
				}
			});
	}

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(_bad_result, 0);
}

TEST_F(SharedMutex, 02_SharedReadWriteLock_Test)
{
	const int Nread = 7;
	thread threads[Nread + 1];

	threads[0] = thread([this] {
		mt19937	gen;
		uniform_int_distribution<int> dist(1, 9);

		for (int i = 0; i < 10000000; ++i)
		{
			_mtx.lock();
			_x = dist(gen);
			_y = dist(gen);
			_z = _x * _y;
			_mtx.unlock();
		}
		_z = -1;
		});

	for (int i = 1; i <= Nread; ++i)
	{
		threads[i] = thread([this]() {
			while (true)
			{
				_mtx.lock_shared();
				if (_z < 0)
				{
					_mtx.unlock();
					break;
				}

				if (_z != _x * _y)
				{
					++_bad_result;
				}

				_mtx.unlock_shared();
			}
			});
	}

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(_bad_result, 0);
}

TEST_F(SharedMutex, 00_xxx_01)
{
	// read lock 걸린 상태에서 
	// read lock 을 또 걸면 대기하는 것 확인
}

TEST_F(SharedMutex, 00_xxx_02)
{
	// read lock 걸린 상태에서 
	// write lock 을 또 걸면 대기하는 것 확인
}

TEST_F(SharedMutex, 00_xxx_03)
{
	// write lock 걸린 상태에서 
	// read lock 을 또 걸면 대기하는 것 확인
}

TEST_F(SharedMutex, 00_xxx_04)
{
	// write lock 걸린 상태에서 
	// write lock 을 또 걸면 대기하는 것 확인
}

TEST_F(SharedMutex, 00_xxx_01)
{
	// read lock 걸린 상태에서 
	// read lock 을 또 걸면 대기하는 것 확인
}

TEST_F(SharedMutex, 00_xxx_02)
{
	// read lock 걸린 상태에서 
	// write lock 을 또 걸면 대기하는 것 확인
}

TEST_F(SharedMutex, 00_xxx_03)
{
	// write lock 걸린 상태에서 
	// read lock 을 또 걸면 대기하는 것 확인
}

TEST_F(SharedMutex, 00_xxx_04)
{
	// write lock 걸린 상태에서 
	// write lock 을 또 걸면 대기하는 것 확인
}