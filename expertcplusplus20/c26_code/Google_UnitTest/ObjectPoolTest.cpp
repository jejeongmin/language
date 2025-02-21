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

		// ��ȸ�� Serial�� �����ϵ��� vector�� �߰��Ѵ�.
		// �Ϸù�ȣ�� set�� �����Ѵ�.
		retrievedSerials.push_back(nextSerial);
		seenSerialNumbers.insert(nextSerial->getSerialNumber());
	}

	// ��ȸ�� �Ϸù�ȣ�� ��� �ٸ��� Ȯ���ϴ� ���
	ASSERT_EQ(numberOfObjectsToRetrieve, seenSerialNumbers.size());
}

TEST(ObjectPoolTest, testRelease)
{
	ObjectPool<Serial> myPool;
	const size_t numberOfObjectsToRetrieve = 10;

	std::vector<ObjectPool<Serial>::Object> retrievedSerials;
	for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
		// ��ȸ�� �ø����� ���Ϳ� �����Ѵ�.
		retrievedSerials.push_back(myPool.acquireObject());
	}
	size_t lastSerialNumber = retrievedSerials.back()->getSerialNumber();
	// ��ü�� ��� Ǯ�� ��ȯ�Ѵ�.
	retrievedSerials.clear();

	// �տ� ���� �ݺ������� Serial ��ü�� �� �� �����ؼ� �Ϸù�ȣ�� 0���� 9���� �����.
	// �׷� ���� �� ���� Serial ��ü�� ��� Ǯ�� ��ȯ�Ѵ�.

	// ���� �ݺ����� ���� Serial ��ü�� �ٽ� �� �� �����´�.
	// ������ �Ϸù�ȣ�� lastSerialNumber���� �۰ų� ���ƾ� �Ѵ�.
	// �� �Ŀ� ������ Serial ��ü�� �Ϸù�ȣ�� ������ �ٸ� ���� ������ �Ѵ�.

	bool wronglyNewObjectCreated = false;
	for (size_t i = 0; i < numberOfObjectsToRetrieve; i++) {
		auto nextSerial = myPool.acquireObject();
		if (nextSerial->getSerialNumber() > lastSerialNumber) {
			wronglyNewObjectCreated = true;
			break;
		}
		retrievedSerials.push_back(nextSerial);
	}

	// Serial ��ü�� �ϳ� �̻� �����´�.
	// ������ ��ü�� �Ϸù�ȣ�� �ݵ�� lastSerialNumber���� Ŀ�� �Ѵ�.
	auto anotherSerial = myPool.acquireObject();
	bool newObjectCreated = (anotherSerial->getSerialNumber() > lastSerialNumber);

	ASSERT_FALSE(wronglyNewObjectCreated);
	ASSERT_TRUE(newObjectCreated);
}
