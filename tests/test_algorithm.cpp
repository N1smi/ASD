// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include<stdexcept>
#include<iostream>
#include <set>
#include "../lib_algorithm/algorithm.h"

TEST(TestAlgorithmLib, FLMNormal) {
  int data[] = { 3, 1, 2, 5, 8, 4, 7, 6, 9 };
  Matrix<int> matrix(3, 3, data, 9);

  int result = find_local_min(matrix);
  EXPECT_TRUE(result == 1 || result == 6);
}

TEST(TestAlgorithmLib, FLMThrowWhenDifferentDimension) {
  int data[] = { 3, 1, 2, 5, 8, 4 };
  Matrix<int> matrix(3, 2, data, 6);

  EXPECT_ANY_THROW(find_local_min(matrix));
}

TEST(TestAlgorithmLib, FLMThrowWhenZeroDimension) {
  Matrix<int> matrix(0, 0);

  EXPECT_ANY_THROW(find_local_min(matrix));
}

TEST(TestAlgorithmLib, FLMSingleElement) {
  int data[] = { 5 };
  Matrix<int> matrix(1, 1, data, 1);

  EXPECT_EQ(find_local_min(matrix), 5);
}

TEST(TestAlgorithmLib, FLM2X2) {
  int data[] = { 2, 3, 4, 1 };
  Matrix<int> matrix(2, 2, data, 4);
  int result = find_local_min(matrix);

  EXPECT_TRUE(result == 1 || result == 2);
}

TEST(TestAlgorithmLib, FLMMoreMins) {
  int data[] = { 2, 5, 3, 6, 4, 7, 8, 9, 1 };
  Matrix<int> matrix(3, 3, data, 9);
  int result = find_local_min(matrix);

  EXPECT_TRUE(result == 4 || result == 2 || result == 3 || result == 1);
}

TEST(TestAlgorithmLib, FLM4X4) {
  int data[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 10, 20, 30, 40, 50, 60 };
  Matrix<int> matrix(4, 4, data, 16);
  int result = find_local_min(matrix);

  EXPECT_TRUE(result == 0 || result == 2);
}

TEST(TestAlgorithmLib, MultipleRunsFindDifferentMins) {
  int data[] = { 3, 1, 2, 5, 8, 4, 7, 6, 9 };
  Matrix<int> matrix(3, 3, data, 9);

  std::set<int> results;
  for (int i = 0; i < 100; i++) {
    results.insert(find_local_min(matrix));
  }

  EXPECT_GT(results.count(1), 0);
  EXPECT_GT(results.count(6), 0);
}

TEST(TestAlgorithmLib, CheckBracketsOddNumberFalse) {
  std::string str = "(()()";

  EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsEasyExampleTrue) {
  std::string str = "()()";

  EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsHardExampleTrue) {
  std::string str = "[(()())({})]";

  EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsHardExampleFalse) {
  std::string str = "((()()(()))(";

  EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsWithoutStart) {
  std::string str = "(()))))";

  EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsWithoutEnd) {
  std::string str = "(((((())";

  EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsEmptryStr) {
  std::string str = "";

  EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsAlpha) {
  std::string str = "a b c d";

  EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsAlphaAndBracketsTrue) {
  std::string str = "(a b c d)";

  EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmLib, CheckBracketsAlphaAndBracketsFalse) {
  std::string str = "(a b c d))";

  EXPECT_FALSE(check_breckets(str));
}