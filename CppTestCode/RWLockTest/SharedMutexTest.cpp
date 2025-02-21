#include "pch.h"
#include "SharedMutexTest.h"

void SharedMutexTest::SetUp()
{
	_x = 0;
	_y = 0;
	_z = 0;
	_bad_result = 0;
}

void SharedMutexTest::TearDown()
{

}


/**
	lock 걸린 상태에서
	lock 을 또 걸면 대기하는 것 확인
*/
TEST_F(SharedMutexTest, 01_lock_lock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.unlock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.lock();

		EXPECT_EQ(step, 2);

		_mtx.unlock();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 3);
}

/**

	lock 걸린 상태에서
	shared lock 을 또 걸면 대기하는 것 확인
*/
TEST_F(SharedMutexTest, 02_lock_sharedlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.unlock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.lock_shared();

		EXPECT_EQ(step, 2);

		_mtx.unlock_shared();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 3);
}

/**
	shared lock 걸린 상태에서
	lock 을 또 걸면 대기하는 것 확인
*/
TEST_F(SharedMutexTest, 03_sharedlock_lock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock_shared();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.unlock_shared();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.lock();

		EXPECT_EQ(step, 2);

		_mtx.unlock();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 3);
}

/*
	shared lock 걸린 상태에서
	shared lock 을 또 걸면 대기하지 않고 바로 lock 을 획득하는 것 확인
*/
TEST_F(SharedMutexTest, 04_sharedlock_sharedlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock_shared();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.unlock_shared();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.lock_shared();		// 대기하지 않고 즉시 thread1 의 공유락을 획득

		EXPECT_EQ(step, 1);

		_mtx.unlock_shared();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 2);			// thread1 이 thread2 보다 늦게 종료되므로
}

/*
	shared lock read 걸린 상태에서 10초 대기
	위 동작으로부터 1초 후 write lock 시도, 잡히지 않아야 함
	첫번째 동작으로부터 2초 후 shared read lock 시도,
		read-preferring 이라면 lock 을 획득해야 함
		write-preferring 이라면 lock 을 획득하지 못함.
	vs2022 에서 shared_mutex 는 write-preferring 으로 확인됨
*/
TEST_F(SharedMutexTest, 05_write_preferring_test)
{
	thread	threads[3];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock_shared();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 3;
		_mtx.unlock_shared();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.lock();			// lock 을 시도

		EXPECT_EQ(step, 3);

		_mtx.unlock();

		step = 5;
		});

	threads[2] = thread([&] {
		this_thread::sleep_for(chrono::seconds(3)); // thread3 는 3초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.lock_shared();		// 대기하지 않고 즉시 thread1 의 공유락을 획득

		EXPECT_EQ(step, 5);

		_mtx.unlock_shared();
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 5);			// thread2 가 thread1 보다 늦게 종료되므로
}

TEST_F(SharedMutexTest, 10_ExclusiveReadWriteLock_Test)
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


/*
	테스트 자체가 읽기 요청 자체가 훨씬 많도록 구성해야 성능 수치가 잘 나온다.
*/
TEST_F(SharedMutexTest, 11_SharedReadWriteLock_Test)
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
					_mtx.unlock_shared();
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
