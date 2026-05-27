// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <set>
#include <memory>
#include <random>
#include <vector>
#include "../lib_avltree/avltree.h"

TEST(TestAVLTreeLib, CreateDefaultAVLTree) {
  AVLTree<int, std::string> tree;

  EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTreeLib, InsertRotationLL) {
  AVLTree<int, std::string> tree;

  tree.insert(7, "grandpa");
  tree.insert(5, "parent");
  tree.insert(4, "child");

  EXPECT_TRUE(tree.is_valid_avl());
}

TEST(TestAVLTreeLib, InsertRotationRR) {
  AVLTree<int, std::string> tree;

  tree.insert(5, "grandpa");
  tree.insert(6, "parent");
  tree.insert(7, "child");

  EXPECT_TRUE(tree.is_valid_avl());
}

TEST(TestAVLTreeLib, InsertRotationLR) {
  AVLTree<int, std::string> tree;

  tree.insert(10, "root");
  tree.insert(9, "grandpa");
  tree.insert(11, "random");
  tree.insert(7, "parent");
  tree.insert(8, "child");

  EXPECT_TRUE(tree.is_valid_avl());
}

TEST(TestAVLTreeLib, InsertRotationRL) {
  AVLTree<int, std::string> tree;

  tree.insert(10, "root");
  tree.insert(9, "random");
  tree.insert(11, "grandpa");
  tree.insert(13, "parent");
  tree.insert(12, "child");

  EXPECT_TRUE(tree.is_valid_avl());
}

TEST(TestAVLTreeLib, SibSaveRightRotation) {
  AVLTree<int, std::string> tree;

  tree.insert(15, "grandpa");
  tree.insert(10, "parent");
  tree.insert(20, "random");
  tree.insert(5, "child");
  tree.insert(12, "sib");
  tree.insert(2, "trigger");

  EXPECT_NE(tree.find(12), nullptr);
  EXPECT_EQ(*tree.find(12), "sib");
  EXPECT_TRUE(tree.is_valid_avl());
}

TEST(TestAVLTreeLib, SibSaveLeftRotation) {
  AVLTree<int, std::string> tree;

  tree.insert(10, "grandpa");
  tree.insert(20, "parent");
  tree.insert(5, "random");
  tree.insert(25, "child");
  tree.insert(18, "sib");
  tree.insert(30, "trigger");

  EXPECT_NE(tree.find(18), nullptr);
  EXPECT_EQ(*tree.find(18), "sib");
  EXPECT_TRUE(tree.is_valid_avl());
}


TEST(TestAVLTreeLib, GreatGrandpaLeftRotationLeftConnect) {
  AVLTree<int, std::string> tree;

  tree.insert(50, "great_grandpa");
  tree.insert(60, "uncle");
  tree.insert(30, "grandpa");
  tree.insert(40, "parent");

  tree.insert(45, "child");

  EXPECT_TRUE(tree.is_valid_avl());
  EXPECT_NE(tree.find(40), nullptr);
  EXPECT_NE(tree.find(30), nullptr);
  EXPECT_NE(tree.find(45), nullptr);
}

TEST(TestAVLTreeLib, GreatGrandpaRightRotationRightConnect) {
  AVLTree<int, std::string> tree;

  tree.insert(50, "great_grandpa");
  tree.insert(40, "uncle");
  tree.insert(70, "grandpa");
  tree.insert(60, "parent");

  tree.insert(55, "child");

  EXPECT_TRUE(tree.is_valid_avl());

  EXPECT_NE(tree.find(60), nullptr);
  EXPECT_NE(tree.find(70), nullptr);
  EXPECT_NE(tree.find(55), nullptr);
}

TEST(TestAVLTreeLib, GreatGrandpaRightConnectLeftRotation) {
  AVLTree<int, std::string> tree;

  tree.insert(10, "great_grandpa");
  tree.insert(5, "uncle");
  tree.insert(20, "grandpa");
  tree.insert(30, "parent");
  tree.insert(40, "child");

  EXPECT_TRUE(tree.is_valid_avl());

  EXPECT_NE(tree.find(30), nullptr);
  EXPECT_NE(tree.find(20), nullptr);
  EXPECT_NE(tree.find(40), nullptr);
}

TEST(TestAVLTreeLib, GreatGrandpaLeftConnectRightRotation) {
  AVLTree<int, std::string> tree;

  tree.insert(100, "great_grandpa");
  tree.insert(110, "uncle");
  tree.insert(80, "grandpa");
  tree.insert(60, "parent");
  tree.insert(40, "child");

  EXPECT_TRUE(tree.is_valid_avl());

  EXPECT_NE(tree.find(60), nullptr);
  EXPECT_NE(tree.find(80), nullptr);
  EXPECT_NE(tree.find(40), nullptr);
}

TEST(TestAVLTreeLib, InsertExistentKey) {
  AVLTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(20, "twenty");

  EXPECT_ANY_THROW(tree.insert(20, "twenty"));
}

TEST(TestAVLTreeLib, EraseWithSingleRotate) {
  AVLTree<int, int> tree;

  std::vector<int> keys = { 50, 25, 80, 15, 35, 90, 10 };
  for (int k : keys) tree.insert(k, k);

  tree.erase(90);

  EXPECT_TRUE(tree.is_valid_avl());
  EXPECT_NE(tree.find(35), nullptr);
  EXPECT_NE(tree.find(50), nullptr);
  EXPECT_NE(tree.find(25), nullptr);
}

TEST(TestAVLTreeLib, EraseWithDoubleRotate) {
  AVLTree<int, int> tree;

  std::vector<int> keys = { 50, 25, 100, 11, 30, 90, 150,
  8, 12, 27, 31, 80, 120, 160, 2, 9, 13, 28, 180, 1};
  for (int k : keys) tree.insert(k, k);

  tree.erase(150);

  EXPECT_TRUE(tree.is_valid_avl());
  EXPECT_NE(tree.find(120), nullptr);
  EXPECT_NE(tree.find(160), nullptr);
  EXPECT_NE(tree.find(50), nullptr);
  EXPECT_NE(tree.find(30), nullptr);
}

TEST(TestAVLTreeLib, EraseNonExistentKey) {
  AVLTree<int, std::string> tree;
  tree.insert(10, "ten");
  tree.insert(20, "twenty");

  EXPECT_ANY_THROW(tree.erase(99));
}

TEST(TestAVLTreeLib, EraseRootWithChilds) {
  AVLTree<int, std::string> tree;
  tree.insert(20, "twenty");
  tree.insert(10, "ten");
  tree.insert(5, "five");

  tree.erase(20);

  EXPECT_TRUE(tree.is_valid_avl());

  EXPECT_NE(tree.find(10), nullptr);
  EXPECT_NE(tree.find(5), nullptr);
}

TEST(TestAVLTreeLib, EraseNodeWithDeepSuccessor) {
  AVLTree<int, int> tree;

  std::vector<int> keys = { 50, 25, 100, 11, 30, 90, 150,
  8, 12, 27, 31, 80, 120, 160, 2, 9, 13, 28, 180, 1 };
  for (int k : keys) tree.insert(k, k);

  tree.erase(50);

  EXPECT_TRUE(tree.is_valid_avl());

  EXPECT_NE(tree.find(31), nullptr);
  EXPECT_NE(tree.find(28), nullptr);
  EXPECT_NE(tree.find(11), nullptr);
  EXPECT_NE(tree.find(25), nullptr);
}

TEST(TestAVLTreeLib, EraseToEmpty) {
  AVLTree<int, int> tree;
  tree.insert(10, 10);
  tree.erase(10);

  EXPECT_TRUE(tree.is_empty());
  EXPECT_TRUE(tree.is_valid_avl());
}

TEST(TestAVLTreeLib, InsertRandomStressTest) {
  AVLTree<int, int> tree;
  std::mt19937 gen(42);
  std::uniform_int_distribution<> distrib(1, 100000);

  std::set<int> unique_keys;

  for (int i = 0; i < 1000; ++i) {
    int val = distrib(gen);

    if (unique_keys.find(val) == unique_keys.end()) {
      tree.insert(val, i);
      unique_keys.insert(val);

      ASSERT_TRUE(tree.is_valid_avl());
    }
  }

  for (int key : unique_keys) {
    EXPECT_NE(tree.find(key), nullptr);
  }
}


TEST(TestAVLTreeLib, EraseRandomStressTest) {
  AVLTree<int, int> tree;
  std::vector<int> values;
  for (int i = 0; i < 1000; ++i) values.push_back(i);

  std::mt19937 rng(1337);

  std::shuffle(values.begin(), values.end(), rng);

  for (int v : values) {
    tree.insert(v, v);
    ASSERT_TRUE(tree.is_valid_avl());
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int v : values) {
    tree.erase(v);
    ASSERT_TRUE(tree.is_valid_avl());
  }
}
