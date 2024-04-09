#include <hashTable.cpp>
#include <iostream>
#include <string>

int main() 
{
	using namespace HashTableSpace;
	using namespace HashTableSpace_Task;
	
	std::string str = "boris";

	HashTable<int, int> ht(2);
	ht.insert(1, pearson_hash(str));
	std::cout << compare_hashes(*ht.search(1), "boris");

	return 0;
}
