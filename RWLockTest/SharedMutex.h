#pragma once

#include <shared_mutex>

class SharedMutex : public ::testing::Test
{
public:
	void SetUp(void);
	void TearDown(void);

public:

	int	_x,	_y,	_z,
		_bad_result;

	std::shared_mutex	_mtx;
};