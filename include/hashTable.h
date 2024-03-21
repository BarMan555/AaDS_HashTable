#pragma once
#include <vector>

namespace HashTable
{
	template<class Key, class Value>
	class HashTable
	{
		struct Pair
		{
			Key key;
			Value value;
			bool filled;
		};

		std::vector<Pair> _data;

	public:
		HashTable();
		HashTable(const size_t size);
		//HashTable() -> random HashTable
		HashTable(const HashTable& other);

		~HashTable();

		HashTable& operator=(const HashTable& hashTable);

		void print();
		void insert(Key key, Value value);
		void insert_or_assign(Key key, Value value);
		bool contains(Value value);
		Value* search(Key key);
		bool erase(Key key);
		int count(Key key);

		size_t hash(const Key key);
	};
}

namespace HashTable
{
	template<class Key, class Value>
	size_t HashTable<Key, Value>::hash(const Key key)
	{
		return key % (Key)_data.size();
	}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable()
	{
	}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable(const size_t size)
	{
	}
}