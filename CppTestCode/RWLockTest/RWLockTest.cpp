#include "pch.h"
#include "RWLockTest.h"

void RWLockTest::SetUp()
{
	_x = 0;
	_y = 0;
	_z = 0;
	_bad_result = 0;
}

void RWLockTest::TearDown()
{

}


/**
	write lock 걸린 상태에서
	write lock 을 또 걸면 대기하는 것 확인
*/
TEST_F(RWLockTest, 01_writelock_writelock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterWriteLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.LeaveWriteLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.EnterWriteLock();

		EXPECT_EQ(step, 2);

		_mtx.LeaveWriteLock();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 3);
}


/**

	write lock 걸린 상태에서
	read lock 을 또 걸면 대기하는 것 확인
*/
TEST_F(RWLockTest, 02_writelock_readlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterWriteLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.LeaveWriteLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.EnterReadLock();

		EXPECT_EQ(step, 2);

		_mtx.LeaveReadLock();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 3);
}


/**
	read lock 걸린 상태에서
	write lock 을 또 걸면 대기하는 것 확인
*/
TEST_F(RWLockTest, 03_readlock_writelock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterReadLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.LeaveReadLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.EnterWriteLock();

		EXPECT_EQ(step, 2);

		_mtx.LeaveWriteLock();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 3);
}


/*
	read lock 걸린 상태에서
	read lock 을 또 걸면 대기하지 않고 바로 lock 을 획득하는 것 확인
*/
TEST_F(RWLockTest, 04_readlock_readlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterReadLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 2;
		_mtx.LeaveReadLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.EnterReadLock();		// 대기하지 않고 즉시 thread1 의 공유락을 획득

		EXPECT_EQ(step, 1);

		_mtx.LeaveReadLock();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 2);			// thread1 이 thread2 보다 늦게 종료되므로
}


/*
	read lock read 걸린 상태에서 5초 대기
	위 동작으로부터 1초 후 write lock 시도, 잡히지 않아야 함
	첫번째 동작으로부터 3초 후 shared read lock 시도,
		read-preferring 이라면 lock 을 획득해야 함
		write-preferring 이라면 lock 을 획득하지 못함.
	RWLock 구현은 write-preferring 으로 확인됨
*/
TEST_F(RWLockTest, 05_write_preferring_test)
{
	thread	threads[3];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterReadLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 에서 lock 잡고 5초 대기

		step = 3;
		_mtx.LeaveReadLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 는 1초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.EnterWriteLock();			// lock 을 시도

		EXPECT_EQ(step, 3);

		_mtx.LeaveWriteLock();

		step = 5;
		});

	threads[2] = thread([&] {
		this_thread::sleep_for(chrono::seconds(3)); // thread3 는 3초 뒤에 시작

		EXPECT_EQ(step, 1);

		_mtx.EnterReadLock();		// 대기하지 않고 즉시 thread1 의 공유락을 획득

		EXPECT_EQ(step, 5);

		_mtx.LeaveReadLock();
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 5);			// thread2 가 thread1 보다 늦게 종료되므로
}


TEST_F(RWLockTest, 10_ExclusiveReadWriteLock_Test)
{
	const int Nread = 7;
	thread threads[Nread + 1];

	threads[0] = thread([this] {
		mt19937	gen;
		uniform_int_distribution<int> dist(1, 9);

		for (int i = 0; i < 10000000; ++i)
		{
			_mtx.EnterWriteLock();
			_x = dist(gen);
			_y = dist(gen);
			_z = _x * _y;
			_mtx.LeaveWriteLock();
		}
		_z = -1;
		});

	for (int i = 1; i <= Nread; ++i)
	{
		threads[i] = thread([this]() {
			while (true)
			{
				_mtx.EnterWriteLock();
				if (_z < 0)
				{
					_mtx.LeaveWriteLock();
					break;
				}

				if (_z != _x * _y)
				{
					++_bad_result;
				}

				_mtx.LeaveWriteLock();
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
TEST_F(RWLockTest, 11_SharedReadWriteLock_Test)
{
	const int Nread = 7;
	thread threads[Nread + 1];

	threads[0] = thread([this] {
		mt19937	gen;
		uniform_int_distribution<int> dist(1, 9);

		for (int i = 0; i < 10000000; ++i)
		{
			_mtx.EnterWriteLock();
			_x = dist(gen);
			_y = dist(gen);
			_z = _x * _y;
			_mtx.LeaveWriteLock();
		}
		_z = -1;
		});

	for (int i = 1; i <= Nread; ++i)
	{
		threads[i] = thread([this]() {
			while (true)
			{
				_mtx.EnterReadLock();
				if (_z < 0)
				{
					_mtx.LeaveReadLock();
					break;
				}

				if (_z != _x * _y)
				{
					++_bad_result;
				}

				_mtx.LeaveReadLock();
			}
			});
	}

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(_bad_result, 0);
}
