#include "hash_map.h"
#include <iostream>
#include <map>

using namespace ProCpp;
using namespace std;

int main()
{
	hash_map<string, int> myHash_temp;
	myHash_temp.insert(make_pair("KeyOne", 100));
	myHash_temp.insert(make_pair("KeyTwo", 200));
	myHash_temp.insert(make_pair("KeyThree", 300));

	hash_map<string, int> myHash{
			{ "KeyOne", 100 },
			{ "KeyTwo", 200 } };

	myHash.insert({
			{ "KeyThree", 300 },
			{ "KeyFour", 400 } });

	for (auto it = myHash.cbegin(); it != myHash.cend(); ++it) {
		// ->�� *�� �� �� ����ؼ� �� ������ �׽�Ʈ�Ѵ�.
		cout << it->first << " maps to " << (*it).second << endl;
	}

	cout << "----" << endl;

	// ���� ��� for������ ���Ҹ� ����Ѵ�.
	for (auto& p : myHash) {
		cout << p.first << " maps to " << p.second << endl;
	}

	cout << "----" << endl;

	// ���� ��� for���� C++17 ������ ���ε��� ����ؼ� ���Ҹ� ����Ѵ�.
	for (auto&[key, value] : myHash) {
		cout << key << " maps to " << value << endl;
	}

	cout << "----" << endl;

	// �ؽø��� ���Ҹ� ��� ���� std::map�� �����Ѵ�.
	map<string, int> myMap(cbegin(myHash), cend(myHash));
	for (auto& p : myMap) {
		cout << p.first << " maps to " << p.second << endl;
	}

	cout << "----" << endl;

	auto found = myHash.find("KeyThree");
	if (found != end(myHash))
	{
		cout << "Found KeyThree: value = " << found->second << endl;
	}

	map<string, int> someMap{ {"One", 1},{"Two", 2} };
	hash_map<string, int> hashMapFromMap(cbegin(someMap), cend(someMap));

	hash_map<string, int> myHash2;
	myHash.swap(myHash2);

	hash_map<string, int> myHash3(std::move(myHash2));

	cout << myHash3.size() << endl;
	cout << myHash3.max_size() << endl;

	// ���� ���� �˻�
	{
		hash_map<string, int> myHash1{
			{ "KeyOne", 100 },
			{ "KeyTwo", 200 } };

		hash_map<string, int> myHash2{
			{ "KeyOne", 100 },
			{ "KeyTwo", 200 } };

		hash_map<string, int> myHash3{
			{ "KeyOne", 100 },
			{ "KeyThree", 300 } };

		if (myHash1 == myHash2)
			cout << "myHash1 and myHash2 is equal." << endl;
		else
			cout << "myHash1 and myHash2 is not equal." << endl;

		if (myHash1 != myHash3)
			cout << "myHash1 and myHash3 is not equal." << endl;
		else
			cout << "myHash1 and myHash3 is equal." << endl;
	}

	// reverse iterator �׽�Ʈ
	{
		hash_map<int, int> myHash{
			{ 1, 100 },
			{ 2, 200 },
			{ 3, 300 }, 
			{ 4, 400 }, };

		for (auto it = myHash.cbegin(); it != myHash.cend(); ++it) {
			// ->�� *�� �� �� ����ؼ� �� ������ �׽�Ʈ�Ѵ�.
			cout << it->first << " maps to " << (*it).second << endl;
		}

		//const_hash_map_reverse_iterator<hash_map<int, int>>	iterator(1, std::rbegin(myHash.mBuckets), &myHash);
		//auto it = myHash.rbegin();
		for (auto it = myHash.crbegin(); it != myHash.crend(); ++it) {
			// ->�� *�� �� �� ����ؼ� �� ������ �׽�Ʈ�Ѵ�.
			cout << it->first << " maps to " << (*it).second << endl;
		}
	}
	
	return 0;
}
