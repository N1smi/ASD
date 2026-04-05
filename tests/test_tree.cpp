// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "../lib_tree/tree.h"

TEST(TestTreeLib, CreateDefaultTree) {
  Tree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());
}

TEST(TestTreeLib, InsertInEmptyTree) {
  Tree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());

  tree.insert(1, "first");

  auto* val1 = tree.find(1);
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(*val1, "first");

  EXPECT_FALSE(tree.is_empty());
}

TEST(TestTreeLib, MultiplyInsertWithFindKeys) {
  Tree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());

  tree.insert(2, "second");
  tree.insert(1, "first");
  tree.insert(5, "five");
  tree.insert(6, "six");
  tree.insert(5, "five?");
  tree.insert(11, "eleven");

  auto* val1 = tree.find(1);
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(*val1, "first");

  auto* val2 = tree.find(2);
  EXPECT_NE(val2, nullptr);
  EXPECT_EQ(*val2, "second");

  auto* val3 = tree.find(5);
  EXPECT_NE(val3, nullptr);
  EXPECT_EQ(*val3, "five");

  auto* val4 = tree.find(6);
  EXPECT_NE(val4, nullptr);
  EXPECT_EQ(*val4, "six");

  auto* val5 = tree.find(11);
  EXPECT_NE(val5, nullptr);
  EXPECT_EQ(*val5, "eleven");

  EXPECT_FALSE(tree.is_empty());
}

TEST(TestTreeLib, IsEmpty) {
  Tree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());

  tree.insert(1, "first");

  EXPECT_FALSE(tree.is_empty());
}

TEST(TestTreeLib, Clear) {
  Tree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());

  tree.insert(2, "second");
  tree.insert(1, "first");
  tree.insert(5, "five");
  tree.insert(6, "six");
  tree.insert(5, "five?");
  tree.insert(11, "eleven");


  EXPECT_FALSE(tree.is_empty());

  tree.clear();

  EXPECT_TRUE(tree.is_empty());
}

TEST(TestTreeLib, FindNonExistentKey) {
  Tree<int, std::string> tree;
  tree.insert(1, "one");

  EXPECT_EQ(tree.find(404), nullptr);
}

TEST(TestTreeLib, ModifyValueViaFind) {
  Tree<int, std::string> tree;
  tree.insert(10, "old_value");

  auto* val = tree.find(10);
  ASSERT_NE(val, nullptr);
  *val = "new_value";

  EXPECT_EQ(*tree.find(10), "new_value");
}

TEST(TestTreeLib, FindInEmptyTree) {
  Tree<int, std::string> tree;

  EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TestTreeLib, FindOnConstTree) {
  Tree<int, std::string> tree;
  tree.insert(1, "data");
  const Tree<int, std::string>& const_tree = tree;

  const std::string* val = const_tree.find(1);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "data");
}

TEST(TestTreeLib, EraseInEmptyTree) {
  Tree<int, std::string> tree;

  ASSERT_ANY_THROW(tree.erase(1));
}

TEST(TestTreeLib, EraseNonExistentKey) {
  Tree<int, std::string> tree;
  tree.insert(1, "first");
  tree.insert(2, "second");

  ASSERT_ANY_THROW(tree.erase(3));
}

TEST(TestTreeLib, EraseRoot) {
  Tree<int, std::string> tree;
  tree.insert(1, "first");

  tree.erase(1);

  EXPECT_TRUE(tree.is_empty());

  auto* val = tree.find(1);

  EXPECT_EQ(val, nullptr);
}

TEST(TestTreeLib, EraseLeaf) {
  Tree<int, std::string> tree;
  tree.insert(1, "first");
  tree.insert(2, "second");
  tree.insert(55, "five_five");

  tree.erase(55);

  auto* val = tree.find(55);

  auto* val1 = tree.find(1);
  auto* val2 = tree.find(2);

  ASSERT_NE(val1, nullptr);
  ASSERT_NE(val2, nullptr);

  EXPECT_EQ(val, nullptr);
}

TEST(TestTreeLib, Erase) {
  Tree<int, std::string> tree;
  tree.insert(1, "first");
  tree.insert(2, "second");
  tree.insert(5, "five");
  tree.insert(6, "six");
  tree.insert(7, "seven");

  tree.erase(2);

  auto* val = tree.find(2);

  EXPECT_EQ(val, nullptr);

  auto* val1 = tree.find(6);
  auto* val2 = tree.find(7);

  ASSERT_NE(val1, nullptr);
  ASSERT_NE(val2, nullptr);
}

TEST(TestTreeLib, InsertAfterErase) {
  Tree<int, std::string> tree;
  tree.insert(1, "1");
  tree.insert(2, "2");
  tree.insert(3, "3");

  tree.erase(1);
  tree.insert(4, "4");

  EXPECT_NE(tree.find(3), nullptr);
  EXPECT_NE(tree.find(4), nullptr);
  EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TestTreeLib, EraseAllOneByOne) {
  Tree<int, std::string> tree;
  tree.insert(1, "1");
  tree.insert(2, "2");

  tree.erase(1);
  tree.erase(2);

  EXPECT_TRUE(tree.is_empty());
  ASSERT_ANY_THROW(tree.erase(1));
}

TEST(TestTreeLib, Print_DLCR) {
  Tree<int, std::string> tree;

  tree.insert(1, "1");
  tree.insert(2, "2");
  tree.insert(3, "3");
  tree.insert(4, "4");
  tree.insert(5, "5");
  tree.insert(6, "6");
  tree.insert(7, "7");
  tree.insert(8, "8");
  tree.insert(9, "9");
  tree.insert(10, "10");
  tree.insert(11, "11");

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  tree.print_DLCR();

  std::cout.rdbuf(old_cout);

  std::string expected = "8 4 9 2 10 5 11 1 6 3 7 ";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestTreeLib, Print_DLRC) {
  Tree<int, std::string> tree;

  tree.insert(1, "1");
  tree.insert(2, "2");
  tree.insert(3, "3");
  tree.insert(4, "4");
  tree.insert(5, "5");
  tree.insert(6, "6");
  tree.insert(7, "7");
  tree.insert(8, "8");
  tree.insert(9, "9");
  tree.insert(10, "10");
  tree.insert(11, "11");

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  tree.print_DLRC();

  std::cout.rdbuf(old_cout);

  std::string expected = "8 9 4 10 11 5 2 6 7 3 1 ";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestTreeLib, Print_CLR) {
  Tree<int, std::string> tree;

  tree.insert(1, "1");
  tree.insert(2, "2");
  tree.insert(3, "3");
  tree.insert(4, "4");
  tree.insert(5, "5");
  tree.insert(6, "6");
  tree.insert(7, "7");
  tree.insert(8, "8");
  tree.insert(9, "9");
  tree.insert(10, "10");
  tree.insert(11, "11");

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  tree.print_DCLR();

  std::cout.rdbuf(old_cout);

  std::string expected = "1 2 4 8 9 5 10 11 3 6 7 ";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestTreeLib, Print_width) {
  Tree<int, std::string> tree;

  tree.insert(1, "1");
  tree.insert(2, "2");
  tree.insert(3, "3");
  tree.insert(4, "4");
  tree.insert(5, "5");
  tree.insert(6, "6");
  tree.insert(7, "7");
  tree.insert(8, "8");
  tree.insert(9, "9");
  tree.insert(10, "10");
  tree.insert(11, "11");

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  tree.print_width();

  std::cout.rdbuf(old_cout);

  std::string expected = "1 2 3 4 5 6 7 8 9 10 11 ";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestTreeLib, IteratorOrderMatchesWidth) {
  Tree<int, std::string> tree;
  tree.insert(1, "1");
  tree.insert(2, "2");
  tree.insert(3, "3");
  tree.insert(5, "5");
  tree.insert(55, "55");

  std::vector<int> keys;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    keys.push_back(it->first);
  }

  std::vector<int> expected = { 1, 2, 3, 5, 55 };
  EXPECT_EQ(keys, expected);
}
