// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
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

TEST(TestRBTreeLib, EraseChildLeftSibRedT1T2Black) {
  RBTree<int, std::string> tree;

  tree.insert(10, "parent");
  tree.insert(5, "toDelete");
  tree.insert(15, "sib");
  tree.insert(11, "");
  tree.insert(19, "");
  tree.insert(25, "");

  tree.erase(5);

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, EraseChildLeftInnerRed) {
  RBTree<int, std::string> tree;
  tree.insert(10, "parent");
  tree.insert(5, "child_to_delete");
  tree.insert(20, "sib_black");
  tree.insert(15, "inner_red");

  tree.erase(5);
  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, EraseChildLeftOuterRed) {
  RBTree<int, std::string> tree;
  tree.insert(10, "parent");
  tree.insert(5, "child_to_delete");
  tree.insert(15, "sib_black");
  tree.insert(20, "outer_red");

  tree.erase(5);
  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, EraseCascade) {
  RBTree<int, std::string> tree;

  tree.insert(40, "global_root");
  tree.insert(20, "");
  tree.insert(60, "");
  tree.insert(10, "");
  tree.insert(32, "");
  tree.insert(15, "");
  tree.insert(50, "");
  tree.insert(70, "");
  tree.insert(55, "");
  tree.insert(45, "");
  tree.insert(42, "");

  tree.erase(42);
  tree.erase(45);
  tree.erase(55);

  tree.erase(50);

  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, EraseChildRightSibRedT1T2Black) {
  RBTree<int, std::string> tree;
  tree.insert(10, "parent");
  tree.insert(15, "child_to_delete");
  tree.insert(5, "sib_red");
  tree.insert(4, "sib_left_black");
  tree.insert(7, "sib_right_black");
  tree.insert(2, "");

  tree.erase(15);
  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, EraseChildRightInnerRed) {
  RBTree<int, std::string> tree;
  tree.insert(20, "parent");
  tree.insert(25, "child_to_delete");
  tree.insert(10, "sib_black");
  tree.insert(15, "inner_red");

  tree.erase(25);
  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, EraseChildRightOuterRed) {
  RBTree<int, std::string> tree;
  tree.insert(20, "parent");
  tree.insert(25, "child_to_delete");
  tree.insert(10, "sib_black");
  tree.insert(5, "outer_red");

  tree.erase(25);
  EXPECT_TRUE(tree.is_valid_rb());
}

TEST(TestRBTreeLib, EraseRootScenarios) {
  RBTree<int, std::string> tree;

  tree.insert(10, "root");
  tree.erase(10);
  EXPECT_TRUE(tree.is_empty());

  tree.insert(20, "root");
  tree.insert(15, "left");
  tree.erase(20);
  EXPECT_TRUE(tree.is_valid_rb());
  EXPECT_NE(tree.find(15), nullptr);
}

TEST(TestRBTreeLib, EraseRandomStressTest) {
  RBTree<int, int> tree;
  std::vector<int> values;
  for (int i = 0; i < 1000; ++i) values.push_back(i);

  std::mt19937 rng(1337);

  std::shuffle(values.begin(), values.end(), rng);

  for (int v : values) {
    tree.insert(v, v);
    ASSERT_TRUE(tree.is_valid_rb());
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int v : values) {
    tree.erase(v);
    ASSERT_TRUE(tree.is_valid_rb());
  }
}
