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
	lock �ɸ� ���¿���
	lock �� �� �ɸ� ����ϴ� �� Ȯ��
*/
TEST_F(SharedMutexTest, 01_lock_lock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.unlock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

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

	lock �ɸ� ���¿���
	shared lock �� �� �ɸ� ����ϴ� �� Ȯ��
*/
TEST_F(SharedMutexTest, 02_lock_sharedlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.unlock();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

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
	shared lock �ɸ� ���¿���
	lock �� �� �ɸ� ����ϴ� �� Ȯ��
*/
TEST_F(SharedMutexTest, 03_sharedlock_lock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock_shared();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.unlock_shared();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

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
	shared lock �ɸ� ���¿���
	shared lock �� �� �ɸ� ������� �ʰ� �ٷ� lock �� ȹ���ϴ� �� Ȯ��
*/
TEST_F(SharedMutexTest, 04_sharedlock_sharedlock_test)
{
	thread	threads[2];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock_shared();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 2;
		_mtx.unlock_shared();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

		EXPECT_EQ(step, 1);

		_mtx.lock_shared();		// ������� �ʰ� ��� thread1 �� �������� ȹ��

		EXPECT_EQ(step, 1);

		_mtx.unlock_shared();

		step = 3;
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 2);			// thread1 �� thread2 ���� �ʰ� ����ǹǷ�
}

/*
	shared lock read �ɸ� ���¿��� 10�� ���
	�� �������κ��� 1�� �� write lock �õ�, ������ �ʾƾ� ��
	ù��° �������κ��� 2�� �� shared read lock �õ�,
		read-preferring �̶�� lock �� ȹ���ؾ� ��
		write-preferring �̶�� lock �� ȹ������ ����.
	vs2022 ���� shared_mutex �� write-preferring ���� Ȯ�ε�
*/
TEST_F(SharedMutexTest, 05_write_preferring_test)
{
	thread	threads[3];
	int		step = 0;

	threads[0] = thread([&] {
		_mtx.lock_shared();

		step = 1;
		EXPECT_EQ(step, 1);

		this_thread::sleep_for(chrono::seconds(5));	// thread1 ���� lock ��� 5�� ���

		step = 3;
		_mtx.unlock_shared();
		});

	threads[1] = thread([&] {
		this_thread::sleep_for(chrono::seconds(1)); // thread2 �� 1�� �ڿ� ����

		EXPECT_EQ(step, 1);

		_mtx.lock();			// lock �� �õ�

		EXPECT_EQ(step, 3);

		_mtx.unlock();

		step = 5;
		});

	threads[2] = thread([&] {
		this_thread::sleep_for(chrono::seconds(3)); // thread3 �� 3�� �ڿ� ����

		EXPECT_EQ(step, 1);

		_mtx.lock_shared();		// ������� �ʰ� ��� thread1 �� �������� ȹ��

		EXPECT_EQ(step, 5);

		_mtx.unlock_shared();
		});

	for (thread& thr : threads)
	{
		thr.join();
	}

	EXPECT_EQ(step, 5);			// thread2 �� thread1 ���� �ʰ� ����ǹǷ�
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
	�׽�Ʈ ��ü�� �б� ��û ��ü�� �ξ� ������ �����ؾ� ���� ��ġ�� �� ���´�.
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
