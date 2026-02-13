// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <string>
#include "../lib_unsorted_table_on_array/unsorted_table_on_array.h"

TEST(TestUnsortedTableOnArrayLib, CreateDefaultTable) {
  UnsortedTableOnArr<int, std::string> table;

  EXPECT_TRUE(table.is_empty());
  // std::cout << table;
}

TEST(TestUnsortedTableOnArrayLib, InsertElements) {
  UnsortedTableOnArr<int, std::string> table;

  table.insert(1, "One");

  EXPECT_FALSE(table.is_empty());

  table.insert(2, "Two");

  // std::cout << table;

  auto* val1 = table.find(1);
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(*val1, "One");

  auto* val2 = table.find(2);
  EXPECT_NE(val2, nullptr);
  EXPECT_EQ(*val2, "Two");
}

TEST(TestUnsortedTableOnArrayLib, InsertThrowWhenEqualKey) {
  UnsortedTableOnArr<int, std::string> table;

  table.insert(1, "One");
  EXPECT_EQ(*table.find(1), "One");
  // std::cout << table;

  EXPECT_ANY_THROW(table.insert(1, "Uno"));
}

TEST(TestUnsortedTableOnArrayLib, FindElements) {
  UnsortedTableOnArr<int, std::string> table;
  table.insert(1, "One");
  table.insert(2, "Two");

  auto* val = table.find(1);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "One");

  EXPECT_EQ(table.find(99), nullptr);

  const auto& const_table = table;
  EXPECT_NE(const_table.find(1), nullptr);
  EXPECT_EQ(const_table.find(99), nullptr);
}

TEST(TestUnsortedTableOnArrayLib, EraseElements) {
  UnsortedTableOnArr<int, std::string> table;
  table.insert(1, "One");
  table.insert(2, "Two");
  table.insert(3, "Three");
  // std::cout << table;

  table.erase(2);
  // std::cout << table;
  EXPECT_EQ(table.find(2), nullptr);
  EXPECT_NE(table.find(1), nullptr);
  EXPECT_NE(table.find(3), nullptr);
}

TEST(TestUnsortedTableOnArrayLib, EraseElementsThrowWhenInvalidKey) {
  UnsortedTableOnArr<int, std::string> table;
  table.insert(1, "One");
  table.insert(2, "Two");
  table.insert(3, "Three");

  EXPECT_ANY_THROW(table.erase(6));
}

TEST(TestUnsortedTableOnArrayLib, IsEmptyTrue) {
  UnsortedTableOnArr<int, std::string> table;

  EXPECT_TRUE(table.is_empty());

  table.insert(1, "One");
  table.erase(1);

  EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnArrayLib, IsEmptyFalse) {
  UnsortedTableOnArr<int, std::string> table;

  EXPECT_TRUE(table.is_empty());

  table.insert(1, "One");

  EXPECT_FALSE(table.is_empty());
}
