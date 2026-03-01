// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <string>

#include "../lib_unsorted_table_on_list/unsorted_table_on_list.h"

TEST(TestUnsortedTableOnListLib, CreateDefaultTable) {
  UnsortedTableOnList<int, std::string> table;

  EXPECT_TRUE(table.is_empty());
  // std::cout << table;
}

TEST(TestUnsortedTableOnListLib, InsertElements) {
  UnsortedTableOnList<int, std::string> table;

  EXPECT_TRUE(table.insert(1, "One"));

  EXPECT_FALSE(table.is_empty());

  EXPECT_TRUE(table.insert(2, "Two"));

  // std::cout << table;

  auto* val1 = table.find(1);
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(*val1, "One");

  auto* val2 = table.find(2);
  EXPECT_NE(val2, nullptr);
  EXPECT_EQ(*val2, "Two");
}

TEST(TestUnsortedTableOnListLib, InsertExistentKey) {
  UnsortedTableOnList<int, std::string> table;

  EXPECT_TRUE(table.insert(1, "One"));

  EXPECT_EQ(*table.find(1), "One");

  EXPECT_FALSE(table.insert(1, "Uno"));
}

TEST(TestUnsortedTableOnListLib, FindElements) {
  UnsortedTableOnList<int, std::string> table;
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

TEST(TestUnsortedTableOnListLib, EraseElements) {
  UnsortedTableOnList<int, std::string> table;
  table.insert(1, "One");
  table.insert(2, "Two");
  table.insert(3, "Three");
  // std::cout << table;

  EXPECT_TRUE(table.erase(2));

  // std::cout << table;
  EXPECT_EQ(table.find(2), nullptr);
  EXPECT_NE(table.find(1), nullptr);
  EXPECT_NE(table.find(3), nullptr);
}

TEST(TestUnsortedTableOnListLib, EraseElementsNonExistentKey) {
  UnsortedTableOnList<int, std::string> table;
  table.insert(1, "One");
  table.insert(2, "Two");
  table.insert(3, "Three");

  EXPECT_FALSE(table.erase(6));
}

TEST(TestUnsortedTableOnListLib, IsEmptyTrue) {
  UnsortedTableOnList<int, std::string> table;

  EXPECT_TRUE(table.is_empty());

  table.insert(1, "One");
  table.erase(1);

  EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnListLib, IsEmptyFalse) {
  UnsortedTableOnList<int, std::string> table;

  EXPECT_TRUE(table.is_empty());

  table.insert(1, "One");

  EXPECT_FALSE(table.is_empty());
}
