// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <string>
#include <set>

#include "../lib_rbtree/rbtree.h"

TEST(TestRBTreeLib, CreateDefaultRBTree) {
  RBTree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTreeLib, InsertParentLeftUncleRed) {
  RBTree<int, std::string> tree;

  tree.insert(11, "grandpa");
  tree.insert(10, "parent");
  tree.insert(12, "uncle");

  tree.insert(9, "child");

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, InsertParentLeftUncleBlackChildRight) {
  RBTree<int, std::string> tree;

  tree.insert(10, "grandpa");
  tree.insert(7, "parent");

  tree.insert(8, "child");

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, InsertParentLeftUncleBlackChildLeft) {
  RBTree<int, std::string> tree;

  tree.insert(10, "grandpa");
  tree.insert(7, "parent");

  tree.insert(6, "child");

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, InsertParentRightUncleRed) {
  RBTree<int, std::string> tree;

  tree.insert(10, "grandpa");
  tree.insert(7, "uncle");
  tree.insert(11, "parent");

  tree.insert(12, "child");

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, InsertParentRightUncleBlackChildLeft) {
  RBTree<int, std::string> tree;

  tree.insert(10, "grandpa");
  tree.insert(12, "parent");

  tree.insert(11, "child");

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, InsertParentRightUncleBlackChildRight) {
  RBTree<int, std::string> tree;

  tree.insert(10, "grandpa");
  tree.insert(12, "parent");

  tree.insert(13, "child");

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, InsertCascadeCorrection) {
  RBTree<int, std::string> tree;

  tree.insert(50, "grandpa_2");
  tree.insert(25, "parent_2");
  tree.insert(100, "uncle_2");
  tree.insert(12, "grandpa_1");
  tree.insert(35, "sib");
  tree.insert(75, "random");
  tree.insert(125, "random");
  tree.insert(6, "parent_1");
  tree.insert(14, "uncle_1");

  tree.insert(3, "child_1");

  EXPECT_TRUE(tree.is_valid_rb());
  EXPECT_NE(tree.find(35), nullptr);
}

TEST(TestRBTreeLib, InsertExistentKey) {
  RBTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(20, "twenty");

  EXPECT_ANY_THROW(tree.insert(20, "twenty"));
}

TEST(TestRBTreeLib, InsertRandomStressTest) {
  RBTree<int, int> tree;
  std::mt19937 gen(42);
  std::uniform_int_distribution<> distrib(1, 100000);

  std::set<int> unique_keys;

  for (int i = 0; i < 1000; ++i) {
    int val = distrib(gen);

    if (unique_keys.find(val) == unique_keys.end()) {
      tree.insert(val, i);
      unique_keys.insert(val);

      ASSERT_TRUE(tree.is_valid_rb());
    }
  }

  for (int key : unique_keys) {
    EXPECT_NE(tree.find(key), nullptr);
  }
}
