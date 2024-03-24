#pragma once
#include <vector>
#include <iostream>

namespace HashTableSpace
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
		size_t _size;

	public:
		HashTable();
		HashTable(const size_t size);
		//HashTable() -> random HashTable
		HashTable(const HashTable& other);

		~HashTable() = default;

		HashTable& operator=(const HashTable& hashTable);

		void print();
		void insert(const Key& key, const Value& value);
		void insert_or_assign(const Key& key, const Value& value);
		bool contains(Value value);
		Value* search(Key key);
		bool erase(Key key);
		int count(Key key);

	private:
		size_t hash(const Key key);
		void grow();
	};
}

namespace HashTableSpace
{
	template<class Key, class Value>
	size_t HashTable<Key, Value>::hash(const Key key)
	{
		return key % (Key)_data.size();
	}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable() : _size(0) {}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable(const size_t capacity) : _size(0)
	{
		if (capacity == 0) throw std::exception("Invalud argument: capacity = 0");
		_data.resize(capacity);
	}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable(const HashTable& other)
	{

	}

	template<class Key, class Value>
	void HashTable<Key, Value>::print()
	{
		for (Pair& pair : _data)
		{
			if (pair.filled) std::cout << "Key: " << pair.key << "\tValue: " << pair.value << std::endl;
		}
	}

	template<class Key, class Value>
	void HashTable<Key, Value>::insert(const Key& key,const Value& value)
	{
		if (_size != 0) 
		{
			double load_factor = _size / (_data.size() + 0.0);
			if (load_factor > 0.6) grow();
		}
		for (size_t i = 0; i < _data.size(); ++i)
		{
			size_t index = (hash(key)+i*hash(key)) % _data.size();
			if (!_data[index].filled)
			{
				_data[index].key = key;
				_data[index].value = value;
				_data[index].filled = true;
				++_size;
				return;
			}
			if (_data[index].key == key) throw std::logic_error("Key is exist");
		}
		grow();
		insert(key, value);
	}

	template<class Key, class Value>
	void HashTable<Key, Value>::grow()
	{
		std::vector<Pair> vect;
		vect.resize((_data.size()+1) * 1.7);
		std::swap(vect, _data);
		_size = 0;
		for (size_t i = 0; i < vect.size(); ++i)
		{
			if (vect[i].filled) insert(vect[i].key, vect[i].value);
		}
	}
}