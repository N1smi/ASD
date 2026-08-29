// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <string>
#include "../lib_unsorted_table_on_tree/unsorted_table_on_tree.h"

TEST(TestUnsortedTableOnTreeLib, CreateDefaultTable) {
  UnsortedTableOnTree<int, std::string> table;

  EXPECT_TRUE(table.is_empty());
  // std::cout << table;
}

TEST(TestUnsortedTableOnTreeLib, InsertElements) {
  UnsortedTableOnTree<int, std::string> table;

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

TEST(TestUnsortedTableOnTreeLib, InsertExistentKey) {
  UnsortedTableOnTree<int, std::string> table;

  EXPECT_TRUE(table.insert(1, "One"));

  EXPECT_EQ(*table.find(1), "One");

  // std::cout << table;

  EXPECT_FALSE(table.insert(1, "Uno"));
}

TEST(TestUnsortedTableOnTreeLib, FindElements) {
  UnsortedTableOnTree<int, std::string> table;
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

TEST(TestUnsortedTableOnTreeLib, EraseElements) {
  UnsortedTableOnTree<int, std::string> table;
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

TEST(TestUnsortedTableOnTreeLib, EraseElementsNonExistentKey) {
  UnsortedTableOnTree<int, std::string> table;
  table.insert(1, "One");
  table.insert(2, "Two");
  table.insert(3, "Three");

  EXPECT_FALSE(table.erase(6));
}

TEST(TestUnsortedTableOnTreeLib, IsEmptyTrue) {
  UnsortedTableOnTree<int, std::string> table;

  EXPECT_TRUE(table.is_empty());

  table.insert(1, "One");
  table.erase(1);

  EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnTreeLib, IsEmptyFalse) {
  UnsortedTableOnTree<int, std::string> table;

  EXPECT_TRUE(table.is_empty());

  table.insert(1, "One");

  EXPECT_FALSE(table.is_empty());
}
