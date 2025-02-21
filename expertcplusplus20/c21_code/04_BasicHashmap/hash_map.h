#pragma once

#include <cstddef>
#include <vector>
#include <list>
#include <string>
#include <functional>

/*
	hash_map 을 간단한 chained_hashing 으로 구현한다.
*/
namespace ProCpp {

	// 디폴트 해시 객체
	template <typename T>
	class hash
	{
	public:
		size_t operator()(const T& key) const;
	};

	/*
		스트링에 대한 해시 특수화가 필요하다.
		같은 문자열 값을 가지고 있어도 string 객체의 주소값이 다를 수 있기 때문에 
		스트링의 값 자체로 해싱을 구해야 한다.
	*/
	template <>
	class hash<std::string>
	{
	public:
		size_t operator()(const std::string& key) const;
	};


	/*
		map, set 과 달리 hash_map 은 원소를 키에 따라 정렬하지 않고, 키의 동등 여부를
		비교해야 한다. 따라서 less<> 대신 equal_to<> 를 기본 비교자로 사용한다. 

		아래와 같이 value_type 을 지정해두면, 다소 번거로운 pair<const Key, T> 타입을
		참조하는데 유용하다.
	*/
	template <typename Key, typename T,
		typename KeyEqual = std::equal_to<>,
		typename Hash = hash<Key>>
	class hash_map
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair<const Key, T>;

		// 가상 소멸자
		virtual ~hash_map() = default;

		// 버킷 수가 맞지 않으면 invalid_argument를 던진다.
		explicit hash_map(const KeyEqual& equal = KeyEqual(), size_t numBuckets = 101, const Hash& hash = Hash());

		// 복제 생성자
		hash_map(const hash_map<Key, T, KeyEqual, Hash>& src) = default;
		// 이동 생성자
		hash_map(hash_map<Key, T, KeyEqual, Hash>&& src) noexcept = default;

		// 복제 대입 연산자
		hash_map<Key, T, KeyEqual, Hash>& operator=(const hash_map<Key, T, KeyEqual, Hash>& rhs);
		// 이동 대입 연산자
		hash_map<Key, T, KeyEqual, Hash>& operator=(hash_map<Key, T, KeyEqual, Hash>&& rhs) noexcept;

		// 키/값 쌍 x를 추가한다.
		void insert(const value_type& x);

		// 키가 k인 원소가 있다면 삭제한다.
		void erase(const key_type& k);

		// 모든 원소를 삭제한다.
		void clear() noexcept;

		// 키가 k인 원소에 대한 포인터를 리턴한다.
		// 그 키에 대한 원소가 없으면 nullptr를 리턴한다.
		value_type* find(const key_type& k);
		const value_type* find(const key_type& k) const;

		// operator[]는 키가 k인 원소를 찾거나
		// 그 키의 원소가 없다면 새로 추가한다. 
		// 그러고 나서 해당 키의 값에 대한 레퍼런스를 리턴한다.
		T& operator[] (const key_type& k);

		// 두 해시 맵을 맞바꾼다.
		void swap(hash_map<Key, T, KeyEqual, Hash>& other) noexcept;

	private:
		using ListType = std::list<value_type>;

		// 주어진 키에 대한 원소를 가리키는 반복자와 그 원소의 버킷 인덱스로 구성된 쌍을 리턴한다.
		std::pair<typename ListType::iterator, size_t> findElement(const key_type& k);

		std::vector<ListType> mBuckets;
		size_t mSize = 0;
		KeyEqual mEqual;
		Hash mHash;
	};

}

#include "hash_map.inl"
