#include "pch.h"
#include <stdexcept>
#include "ObjectPool.h" 
#include "Serial.h"
#include <cstddef>
#include <vector>
#include <set>


TEST(ObjectPoolTest, testSimple)
{
	ASSERT_TRUE(0 < 1);
}

TEST(ObjectPoolTest, testException)
{
	EXPECT_THROW({throw std::invalid_argument("Error"); }, 
		std::invalid_argument);
}

TEST(ObjectPoolTest, testCreation)
{
	ObjectPool<Serial> myPool;
}

TEST(ObjectPoolTest, testAcquire)
{
	ObjectPool<Serial> myPool;
	auto serial = myPool.acquireObject();
	ASSERT_TRUE(serial->getSerialNumber() >= 0);
}

TEST(ObjectPoolTest, testExclusivity)
{
	ObjectPool<Serial> myPool;
	const size_t numberOfObjectsToRetrieve = 10;
	std::vector<ObjectPool<Serial>::Object> retrievedSerials;
	std::set<size_t> seenSerialNumbers;

	for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
		auto nextSerial = myPool.acquireObject();

		// 조회한 Serial을 보관하도록 vector에 추가한다.
		// 일련번호를 set에 저장한다.
		retrievedSerials.push_back(nextSerial);
		seenSerialNumbers.insert(nextSerial->getSerialNumber());
	}

	// 조회한 일련번호가 모두 다른지 확인하는 어서션
	ASSERT_EQ(numberOfObjectsToRetrieve, seenSerialNumbers.size());
}

TEST(ObjectPoolTest, testRelease)
{
	ObjectPool<Serial> myPool;
	const size_t numberOfObjectsToRetrieve = 10;

	std::vector<ObjectPool<Serial>::Object> retrievedSerials;
	for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
		// 조회한 시리얼을 벡터에 보관한다.
		retrievedSerials.push_back(myPool.acquireObject());
	}
	size_t lastSerialNumber = retrievedSerials.back()->getSerialNumber();
	// 객체를 모두 풀에 반환한다.
	retrievedSerials.clear();

	// 앞에 나온 반복문에서 Serial 객체를 열 개 생성해서 일련번호가 0부터 9까지 생겼다.
	// 그런 다음 열 개의 Serial 객체를 모두 풀에 반환한다.

	// 다음 반복문은 먼저 Serial 객체를 다시 열 개 가져온다.
	// 각각의 일련번호는 lastSerialNumber보다 작거나 같아야 한다.
	// 그 후에 가져온 Serial 객체의 일련번호는 이전과 다른 값을 가져야 한다.

	bool wronglyNewObjectCreated = false;
	for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
		auto nextSerial = myPool.acquireObject();
		if (nextSerial->getSerialNumber() > lastSerialNumber) {
			wronglyNewObjectCreated = true;
			break;
		}
		retrievedSerials.push_back(nextSerial);
	}

	// Serial 객체를 하나 이상 가져온다.
	// 가져온 객체의 일련번호는 반드시 lastSerialNumber보다 커야 한다.
	auto anotherSerial = myPool.acquireObject();
	bool newObjectCreated = (anotherSerial->getSerialNumber() > lastSerialNumber);

	ASSERT_FALSE(wronglyNewObjectCreated);
	ASSERT_TRUE(newObjectCreated);
}
