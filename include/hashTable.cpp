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

			bool operator==(const Pair& other);
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
		bool operator==(const HashTable& other);

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
		//if (capacity == 0) throw std::exception("Invalud argument: capacity = 0");
		_data.resize(capacity);
	}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable(const HashTable& other) : HashTable(other._size)
	{
		if (other == *this) return;
		for (auto& pair : other._data)
		{
			if(pair.filled) insert(pair.key, pair.value);
		}
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
	void HashTable<Key, Value>::insert_or_assign(const Key& key, const Value& value)
	{
		if (_size != 0)
		{
			double load_factor = _size / (_data.size() + 0.0);
			if (load_factor > 0.6) grow();
		}
		for (size_t i = 0; i < _data.size(); ++i)
		{
			size_t index = (hash(key) + i * hash(key)) % _data.size();
			if (!_data[index].filled || _data[index].key == key)
			{
				_data[index].key = key;
				_data[index].value = value;
				_data[index].filled = true;
				++_size;
				return;
			}
		}
		grow();
		insert_or_assign(key, value);
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

	template<class Key, class Value>
	bool HashTable<Key, Value>::operator==(const HashTable& other)
	{
		if (this->_size != other._size) return false;
		for (size_t i = 0; i < std::min(this->_data.size(), other._data.size()); ++i)
		{
			if (this->_data[i] != other._data[i]) return false;
		}
		return true;
	}

	template<class Key, class Value>
	bool HashTable<Key, Value>::Pair::operator==(const Pair& other)
	{
		return key == other.key && value == other.value && filled == other.filled;
	}

	template<class Key, class Value>
	bool HashTable<Key, Value>::contains(Value value)
	{
		for (auto& pair : _data)
		{
			if (pair.filled and pair.value == value) return true;
		}
		return false;
	}

	template<class Key, class Value>
	Value* HashTable<Key, Value>::search(Key key)
	{
		for (size_t i = 0; i < _data.size(); ++i)
		{
			size_t index = (hash(key) + i * hash(key)) % _data.size();
			if (_data[index].filled && _data[index].key == key)
			{
				return &(_data[index].value);
			}
		}
		return nullptr;
	}
}