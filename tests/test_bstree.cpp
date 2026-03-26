// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <sstream>
#include <iostream>
#include <string>

#include "../lib_bstree/bstree.h"

TEST(TestBSTreeLib, CreateDefaultBSTree) {
  BSTree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());
}

TEST(TestBSTreeLib, InsertInEmptyBSTree) {
  BSTree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());

  tree.insert(1, "first");

  auto* val1 = tree.find(1);
  EXPECT_NE(val1, nullptr);
  EXPECT_EQ(*val1, "first");

  EXPECT_FALSE(tree.is_empty());
}

TEST(TestBSTreeLib, InsertLeftRight) {
  BSTree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());

  tree.insert(7, "seven");
  tree.insert(5, "five");
  tree.insert(4, "four");
  tree.insert(6, "six");
  tree.insert(10, "ten");
  tree.insert(3, "three");
  tree.insert(20, "twenty");

  // tree.print();

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  tree.print();

  std::cout.rdbuf(old_cout);

  std::string expected =
    "[key: 3, val: three]"
    "[key: 4, val: four]"
    "[key: 5, val: five]"
    "[key: 6, val: six]"
    "[key: 7, val: seven]"
    "[key: 10, val: ten]"
    "[key: 20, val: twenty]";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestBSTreeLib, InsertThrowWhenKeyExist) {
  BSTree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());

  tree.insert(7, "seven");
  tree.insert(5, "five");
  tree.insert(10, "ten");
  EXPECT_ANY_THROW(tree.insert(10, "desyat"));
}

TEST(TestBSTreeLib, FindNonExistentKey) {
  BSTree<int, std::string> tree;
  tree.insert(10, "ten");

  EXPECT_EQ(tree.find(5), nullptr);
}

TEST(TestBSTreeLib, FindRootKey) {
  BSTree<int, std::string> tree;
  tree.insert(10, "ten");

  EXPECT_EQ(*tree.find(10), "ten");
}

TEST(TestBSTreeLib, FindInEmptyBSTree) {
  BSTree<int, std::string> tree;

  EXPECT_EQ(tree.find(5), nullptr);
}

TEST(TestBSTreeLib, FindLeftRightKey) {
  BSTree<int, std::string> tree;
  tree.insert(7, "seven");
  tree.insert(4, "four");
  tree.insert(9, "nine");

  EXPECT_EQ(*tree.find(4), "four");
  EXPECT_EQ(*tree.find(9), "nine");
}

TEST(TestBSTreeLib, EraseRootMaxLeftLeaf) {
  BSTree<int, std::string> tree;
  tree.insert(7, "seven");
  tree.insert(5, "five");
  tree.insert(4, "four");
  tree.insert(6, "six");
  tree.insert(10, "ten");
  tree.insert(3, "three");
  tree.insert(20, "twenty");

  tree.erase(7);

  EXPECT_EQ(tree.find(7), nullptr);
  EXPECT_NE(tree.find(6), nullptr);
}

TEST(TestBSTreeLib, EraseSingleRoot) {
  BSTree<int, std::string> tree;
  tree.insert(7, "seven");

  tree.erase(7);

  EXPECT_EQ(tree.find(7), nullptr);
}


TEST(TestBSTreeLib, EraseNodeWithOnlyLeftChild) {
  BSTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(3, "three");

  tree.erase(5);

  EXPECT_EQ(tree.find(5), nullptr);
  EXPECT_NE(tree.find(3), nullptr);
}

TEST(TestBSTreeLib, EraseNodeWithOnlyRightChild) {
  BSTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(7, "seven");

  tree.erase(5);

  EXPECT_EQ(tree.find(5), nullptr);
  EXPECT_NE(tree.find(7), nullptr);
}

TEST(TestBSTreeLib, EraseNodeWithTwoChildren) {
  BSTree<int, std::string> tree;

  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(15, "fifteen");
  tree.insert(3, "three");
  tree.insert(7, "seven");

  tree.erase(5);

  EXPECT_EQ(tree.find(5), nullptr);
  EXPECT_EQ(*tree.find(3), "three");
  EXPECT_EQ(*tree.find(7), "seven");
}

TEST(TestBSTreeLib, EraseInEmptyBSTree) {
  BSTree<int, std::string> tree;

  EXPECT_THROW(tree.erase(10), std::invalid_argument);
}

TEST(TestBSTreeLib, EraseWithNonExistentKey) {
  BSTree<int, std::string> tree;

  tree.insert(10, "ten");
  EXPECT_THROW(tree.erase(20), std::invalid_argument);
}

TEST(TestBSTreeLib, EraseNodeWhereSuccessorIsDirectChild) {
  BSTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(5, "five");
  tree.insert(8, "eight");
  tree.insert(3, "three");

  tree.erase(5);

  EXPECT_EQ(tree.find(5), nullptr);
  EXPECT_NE(tree.find(3), nullptr);
  EXPECT_NE(tree.find(8), nullptr);
}

TEST(TestBSTreeLib, EraseSuccessorWithLeftChild) {
  BSTree<int, std::string> tree;
  tree.insert(20, "root");
  tree.insert(10, "delete_me");
  tree.insert(30, "right");
  tree.insert(5, "left_child");
  tree.insert(8, "successor");
  tree.insert(7, "successor_left_child");
  tree.insert(15, "right_child_of_10");

  tree.erase(10);

  EXPECT_EQ(tree.find(10), nullptr);
  EXPECT_EQ(*tree.find(8), "successor");
  EXPECT_NE(tree.find(7), nullptr);
}
