// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <iostream>
#include <string>
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

TEST(TestAVLTreeLib, InsertSibSaveRightRotation) {
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

TEST(TestAVLTreeLib, InsertSibSaveLeftRotation) {
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
