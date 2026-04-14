// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <string>

#include "../lib_hash_table_oa/hash_table_oa.h"

TEST(TestHashTableOALib, CreateDefaultTable) {
  HashTableOA<int> table;

  EXPECT_TRUE(table.is_empty());

  // std::cout << table;
}

TEST(TestHashTableOALib, InsertElements) {
  HashTableOA<int> table;

  EXPECT_TRUE(table.insert("One", 1));

  EXPECT_FALSE(table.is_empty());

  EXPECT_TRUE(table.insert("Two", 2));

  EXPECT_TRUE(table.insert("enO", 1));

  EXPECT_FALSE(table.is_full());

  // std::cout << table;

  auto* val1 = table.find("One");
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(*val1, 1);

  auto* val2 = table.find("Two");
  EXPECT_NE(val2, nullptr);
  EXPECT_EQ(*val2, 2);

  auto* val3 = table.find("enO");
  EXPECT_NE(val3, nullptr);
  EXPECT_EQ(*val3, 1);
}

TEST(TestHashTableOALib, InsertElementsFulseWhenIsFull) {
  HashTableOA<int> table(3);

  table.insert("One", 1);

  table.insert("Two", 2);

  table.insert("enO", 1);

  EXPECT_FALSE(table.insert("Three", 3));

  EXPECT_TRUE(table.is_full());
}

TEST(TestHashTableOALib, InsertExistentKey) {
  HashTableOA<int> table;

  EXPECT_TRUE(table.insert("One", 1));

  EXPECT_EQ(*table.find("One"), 1);

  // std::cout << table;

  EXPECT_FALSE(table.insert("One", 1));
}

TEST(TestHashTableOALib, FindElements) {
  HashTableOA<int> table;
  table.insert("One", 1);
  table.insert("Two", 2);
  table.insert("enO", 1);

  auto* val = table.find("One");
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, 1);

  auto* val1 = table.find("enO");
  ASSERT_NE(val1, nullptr);
  EXPECT_EQ(*val1, 1);

  EXPECT_EQ(table.find("Nine"), nullptr);

  const auto& const_table = table;
  EXPECT_NE(const_table.find("One"), nullptr);
  EXPECT_NE(const_table.find("enO"), nullptr);
  EXPECT_EQ(const_table.find("Nine"), nullptr);
}

TEST(TestHashTableOALib, EraseElements) {
  HashTableOA<int> table;
  table.insert("One", 1);
  table.insert("Two", 2);
  table.insert("Three", 3);

  // std::cout << table;

  EXPECT_TRUE(table.erase("Two"));

  // std::cout << table;

  EXPECT_EQ(table.find("Two"), nullptr);
  EXPECT_NE(table.find("One"), nullptr);
  EXPECT_NE(table.find("Three"), nullptr);
}

TEST(TestHashTableOALib, EraseElementsNonExistentKey) {
  HashTableOA<int> table;
  table.insert("One", 1);
  table.insert("Two", 2);
  table.insert("Three", 3);

  EXPECT_FALSE(table.erase("Six"));
}

TEST(TestHashTableOALib, EraseElementsNonExistentKeyWhenFull) {
  HashTableOA<int> table(3);
  table.insert("One", 1);
  table.insert("Two", 2);
  table.insert("Three", 3);

  EXPECT_TRUE(table.is_full());

  EXPECT_FALSE(table.erase("Six"));
}

TEST(TestHashTableOALib, FindElementsNonExistentKeyWhenFull) {
  HashTableOA<int> table(3);
  table.insert("One", 1);
  table.insert("Two", 2);
  table.insert("Three", 3);

  EXPECT_TRUE(table.is_full());

  EXPECT_EQ(table.find("Six"), nullptr);
}

TEST(TestHashTableOALib, IsEmptyTrue) {
  HashTableOA<int> table;

  EXPECT_TRUE(table.is_empty());

  table.insert("One", 1);
  table.erase("One");

  EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableOALib, IsEmptyFalse) {
  HashTableOA<int> table;

  EXPECT_TRUE(table.is_empty());

  table.insert("One", 1);

  EXPECT_FALSE(table.is_empty());
}

TEST(TestHashTableOALib, IsFullTrue) {
  HashTableOA<int> table(3);

  EXPECT_FALSE(table.is_full());

  table.insert("One", 1);
  table.insert("enO", 1);
  table.insert("Oen", 1);

  EXPECT_TRUE(table.is_full());
}

TEST(TestHashTableOALib, IsFullFalse) {
  HashTableOA<int> table;

  EXPECT_FALSE(table.is_full());

  table.insert("One", 1);

  EXPECT_FALSE(table.is_full());
}

TEST(TestHashTableOALib, FindElementAfterDeletedCollision) {
  HashTableOA<int> table;
  table.insert("One", 1);
  table.insert("enO", 2);

  table.erase("One");

  auto* val = table.find("enO");
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, 2);
}

TEST(TestHashTableOALib, InsertDuplicateWithDeletedInChain) {
  HashTableOA<int> table;
  table.insert("One", 1);
  table.insert("enO", 2);

  table.erase("One");

  EXPECT_FALSE(table.insert("enO", 3));
}
