#include <gtest/gtest.h>
#include "../include/hashTable.cpp"

using namespace HashTableSpace;

TEST(hash_test, insert)
{
	HashTable<int, int> ht(1);
	ht.insert(1, 100);

	ASSERT_TRUE(ht.contains(100));
}

TEST(hash_test, insert_or_assign_1)
{
	HashTable<int, int> ht(2);
	ht.insert_or_assign(1, 100);
	ht.insert_or_assign(1, 200);

	ASSERT_TRUE(ht.contains(200));
}

TEST(hash_test, insert_or_assign_2)
{
	HashTable<int, int> ht(2);
	ht.insert_or_assign(1, 100);
	ht.insert_or_assign(1, 200);

	ASSERT_FALSE(ht.contains(100));
}

TEST(hash_test, search)
{
	HashTable<int, int> ht(1);
	ht.insert(1, 100);

	ASSERT_EQ(*ht.search(1), 100);
}

TEST(hash_test, erase)
{
	HashTable<int, int> ht(1);
	ht.insert(1, 100);
	ht.erase(1);

	ASSERT_FALSE(ht.contains(100));
}

TEST(hash_test, equal)
{
	HashTable<int, int> ht1(2);
	ht1.insert(1, 100);
	ht1.insert(2, 200);

	HashTable<int, int> ht2(2);
	ht2.insert(1, 100);
	ht2.insert(2, 200);

	ASSERT_TRUE(ht1 == ht2);
}

TEST(hash_test, constructor_1)
{
	HashTable<int, int> ht(10);
	ASSERT_EQ(ht.get_size(), 0);
}

TEST(hash_test, constructor_2)
{
	HashTable<int, int> ht1(2);
	ht1.insert(1, 100);
	ht1.insert(2, 200);

	HashTable<int, int> ht2(ht1);
	ASSERT_TRUE(ht1==ht2);
}

TEST(hash_test, erase_in_middle)
{
	HashTable<int, int> ht(5);
	ht.insert(1, 10);
	ht.insert(2, 10);
	ht.insert(3, 10);
	ht.insert(4, 10);
	ht.insert(11, 10);
	ht.erase(3);
	ASSERT_EQ(ht.count(11), 2);
}