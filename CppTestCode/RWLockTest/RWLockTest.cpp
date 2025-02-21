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
	write lock �ɸ� ���¿���
	write lock �� �� �ɸ� ����ϴ� �� Ȯ��
*/
TEST_F(RWLockTest, 01_writelock_writelock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterWriteLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.LeaveWriteLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

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

	write lock �ɸ� ���¿���
	read lock �� �� �ɸ� ����ϴ� �� Ȯ��
*/
TEST_F(RWLockTest, 02_writelock_readlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterWriteLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.LeaveWriteLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

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
	read lock �ɸ� ���¿���
	write lock �� �� �ɸ� ����ϴ� �� Ȯ��
*/
TEST_F(RWLockTest, 03_readlock_writelock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterReadLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.LeaveReadLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

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
	read lock �ɸ� ���¿���
	read lock �� �� �ɸ� ������� �ʰ� �ٷ� lock �� ȹ���ϴ� �� Ȯ��
*/
TEST_F(RWLockTest, 04_readlock_readlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterReadLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.LeaveReadLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

		EXPECT_EQ(step, 1);

		_mtx.EnterReadLock();		// ������� �ʰ� ��� thread1 �� �������� ȹ��

		EXPECT_EQ(step, 1);

		_mtx.LeaveReadLock();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 2);			// thread1 �� thread2 ���� �ʰ� ����ǹǷ�
}


/*
	read lock read �ɸ� ���¿��� 5�� ���
	�� �������κ��� 1�� �� write lock �õ�, ������ �ʾƾ� ��
	ù��° �������κ��� 3�� �� shared read lock �õ�,
		read-preferring �̶�� lock �� ȹ���ؾ� ��
		write-preferring �̶�� lock �� ȹ������ ����.
	RWLock ������ write-preferring ���� Ȯ�ε�
*/
TEST_F(RWLockTest, 05_write_preferring_test)
{
	thread	threads[3];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.EnterReadLock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 3;
		_mtx.LeaveReadLock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

		EXPECT_EQ(step, 1);

		_mtx.EnterWriteLock();			// lock �� �õ�

		EXPECT_EQ(step, 3);

		_mtx.LeaveWriteLock();

		step = 5;
		});

	threads[2] = thread([&] {
		this_thread::sleep_for(chrono::seconds(3)); // thread3 �� 3�� �ڿ� ����

		EXPECT_EQ(step, 1);

		_mtx.EnterReadLock();		// ������� �ʰ� ��� thread1 �� �������� ȹ��

		EXPECT_EQ(step, 5);

		_mtx.LeaveReadLock();
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 5);			// thread2 �� thread1 ���� �ʰ� ����ǹǷ�
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
	�׽�Ʈ ��ü�� �б� ��û ��ü�� �ξ� ������ �����ؾ� ���� ��ġ�� �� ���´�.
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
