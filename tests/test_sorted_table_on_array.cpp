// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <string>

#include "../lib_sorted_table_on_array/sorted_table_on_array.h"

TEST(TestSortedTableOnArrayLib, CreateDefaultTable) {
  SortedTableOnArr<int, std::string> table;

  EXPECT_TRUE(table.is_empty());
  // std::cout << table;
}

TEST(TestSortedTableOnArrayLib, InsertElements) {
  SortedTableOnArr<int, std::string> table;

  EXPECT_TRUE(table.insert(3, "Three"));

  EXPECT_TRUE(table.insert(1, "One"));

  EXPECT_TRUE(table.insert(4, "Four"));

  // std::cout << table;

  EXPECT_FALSE(table.is_empty());

  auto* val1 = table.find(1);
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(*val1, "One");

  auto* val2 = table.find(3);
  EXPECT_NE(val2, nullptr);
  EXPECT_EQ(*val2, "Three");

  auto* val3 = table.find(4);
  EXPECT_NE(val3, nullptr);
  EXPECT_EQ(*val3, "Four");

  EXPECT_TRUE(val1 < val2 && val2 < val3);
}

TEST(TestSortedTableOnArrayLib, InsertExistentKey) {
  UnsortedTableOnArr<int, std::string> table;

  EXPECT_TRUE(table.insert(1, "One"));

  EXPECT_EQ(*table.find(1), "One");

  EXPECT_FALSE(table.insert(1, "Uno"));
}

TEST(TestSortedTableOnArrayLib, EraseElements) {
  SortedTableOnArr<int, std::string> table;
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

TEST(TestSortedTableOnArrayLib, EraseElementsNonExistentKey) {
  UnsortedTableOnArr<int, std::string> table;
  table.insert(1, "One");
  table.insert(2, "Two");
  table.insert(3, "Three");

  EXPECT_FALSE(table.erase(6));
}

TEST(TestSortedTableOnArrayLib, FindElements) {
  SortedTableOnArr<int, std::string> table;

  EXPECT_EQ(table.find(1), nullptr);

  table.insert(5, "Five");
  table.insert(2, "Two");
  table.insert(8, "Eight");

  EXPECT_EQ(*table.find(5), "Five");

  EXPECT_EQ(table.find(3), nullptr);

  const auto& const_table = table;
  EXPECT_EQ(*const_table.find(5), "Five");
  EXPECT_EQ(const_table.find(3), nullptr);

  *table.find(5) = "Pyterka";
  EXPECT_EQ(*table.find(5), "Pyterka");

  table.erase(5);
  EXPECT_EQ(table.find(5), nullptr);
  EXPECT_NE(table.find(8), nullptr);
}
