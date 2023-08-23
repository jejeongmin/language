#pragma once

#include "RWLock.h"

class RWLockTest : public ::testing::Test
{
public:
	void SetUp(void);
	void TearDown(void);

public:

	int	_x, _y, _z,
		_bad_result;

	RWLock	_mtx;
};

