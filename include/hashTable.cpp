#pragma once
#include <vector>
#include <string>
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
		HashTable(const size_t size);
		HashTable(size_t size, const Value& max, const Value& min);
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
		size_t get_size();

	private:
		size_t hash(const Key key);
		void grow();
	};
}

namespace HashTableSpace
{
	template<class Key, class Value>
	size_t HashTable<Key, Value>::get_size()
	{
		return _size;
	}

	template<class Key, class Value>
	size_t HashTable<Key, Value>::hash(const Key key)
	{
		return key % (Key)_data.size();
	}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable(const size_t size) : _size(0)
	{
		if (size == 0)
			throw std::invalid_argument("size = 0");
		_data.resize(size);
	}

	template<class Key, class Value>
	HashTable<Key, Value>::HashTable(size_t size, const Value& min, const Value& max) {
		if (size == 0)
			throw std::invalid_argument("size = 0");
		_size = size;
		_data.resize(size);
		for (int i = 0; i < size; ++i) {
			Value value = rand() % (max - min + 1) + min;
			_data[i] = *(new Pair(i, value));
			_data[i].filled = true;
		}
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

	template<class Key, class Value>
	bool HashTable<Key, Value>::erase(Key key)
	{
		for (size_t i = 0; i < _data.size(); ++i)
		{
			size_t index = (hash(key) + i * hash(key)) % _data.size();
			if (_data[index].filled && _data[index].key == key)
			{
				_data[index].filled = false;
				return true;
			}
		}
		return false;
	}

	template<class Key, class Value>
	HashTable<Key, Value>& HashTable<Key, Value>::operator=(const HashTable& hashTable)
	{
		if (hashTable == *this) return *this;
		_data.clear();
		_data.resize(hashTable._size);
		for (auto& pair : hashTable._data)
		{
			if (pair.filled) insert(pair.key, pair.value);
		}
		return *this;
	}

	template<class Key, class Value>
	int HashTable<Key, Value>::count(Key key)
	{
		int count = 0;
		for(size_t i = 0; count < _size; ++i)
		{
			size_t index = (hash(key) + i * hash(key)) % _data.size();
			if (!_data[index].filled) return count;
			else if (hash(key) == hash(_data[index].key)) ++count;
		}
		return count;
	}
}

namespace HashTableSpace_Task
{
	using namespace HashTableSpace;

	static const unsigned char T[256] = {
		// 0-255 shuffled in any (random) order suffices
		 98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219, //  1
		 61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115, //  2
		 90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10, //  3
		237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121, //  4
		123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55, //  5
		 59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222, //  6
		197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, //  7
		 39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99, //  8
		154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, //  9
		133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139, // 10
		189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, // 11
		183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, // 12
		221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, // 13
		  3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, // 14
		238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, // 15
		 43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239  // 16
	};
	
	int pearson_hash(const std::string& str)
	{
		int hash = 0;
		for (auto& c : str)
		{
			hash = T[hash ^ c];
		}

		return hash;
	}

	bool compare_hashes(unsigned int saved_hash, const std::string& new_text) {
		unsigned int new_hash = pearson_hash(new_text);

		return saved_hash == new_hash;
	}
}