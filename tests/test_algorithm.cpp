// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include <string>
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

TEST(TestAlgorithmLib, ReadExprValidExpr) {
  EXPECT_NO_THROW(read_expression("3 * (15 + (x + y)*(2*x - 7*y^2))"));
  EXPECT_NO_THROW(read_expression("x + y"));
  EXPECT_NO_THROW(read_expression("(a + b) * (c - d)"));
  EXPECT_NO_THROW(read_expression("x^2 + y^2"));
  EXPECT_NO_THROW(read_expression("a + b + c + d"));
}

TEST(TestAlgorithmLib, ReadExprMissOperation) {
  EXPECT_THROW({
     try {
         read_expression("3 * (15 + (x y)*(2*x - 7*y^2))");
     }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing operation", e.what());
  throw;
}
    }, std::invalid_argument);
}

TEST(TestAlgorithmLib, ReadExprMissFirstOperand) {
  EXPECT_THROW({
      try {
          read_expression("+ 5");
      }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing first operand in operation +", e.what());
  throw;
}
    }, std::invalid_argument);
}

TEST(TestAlgorithmLib, ReadExprMissSecondOperand) {
  EXPECT_THROW({
      try {
          read_expression("3 * (15 + (x + y)*(2*x - 7*y^))");
      }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing second operand in operation ^", e.what());
  throw;
}
    }, std::invalid_argument);

  EXPECT_THROW({
    try {
        read_expression("(x * )");
    }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing second operand in operation *", e.what());
  throw;
}
    }, std::invalid_argument);

  EXPECT_THROW({
     try {
         read_expression("x + y + ");
     }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing second operand in operation +", e.what());
  throw;
}
    }, std::invalid_argument);
}

TEST(TestAlgorithmLib, ReadExprMissClosedBracket) {
  EXPECT_THROW({
    try {
        read_expression("((x + y)*(x - y)");
    }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing closed bracket", e.what());
  throw;
}
    }, std::invalid_argument);
}

TEST(TestAlgorithmLib, ReadExprMissOpenedBracket) {
  EXPECT_THROW({
    try {
        read_expression("(x * x + y ^ 2))*(8 + (y - 3))");
    }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing opened bracket", e.what());
  throw;
}
    }, std::invalid_argument);

  EXPECT_THROW({
      try {
          read_expression("(x + y]");
      }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Missing opened bracket", e.what());
  throw;
}
    }, std::invalid_argument);
}

TEST(TestAlgorithmLib, ReadExprInvalidCharacter) {
  EXPECT_THROW({
    try {
        read_expression("x $ y");
    }
catch (const std::invalid_argument& e) {
  EXPECT_STREQ("Invalid character in expression", e.what());
  throw;
}
    }, std::invalid_argument);
}

TEST(TestAlgorithmLib, IsLoopedTListHareAndTurtleTrue) {
  TList<int> list;

  for (size_t i = 0; i < 5; i++) {
    list.push_back(1 + i);
  }

  list.tail()->next = list.head()->next;

  EXPECT_TRUE(is_looped_hare(list));

  list.tail()->next = nullptr;
}

TEST(TestAlgorithmLib, IsLoopedTListHareAndTurtleFalse) {
  TList<int> list;

  for (size_t i = 0; i < 5; i++) {
    list.push_back(1 + i);
  }

  EXPECT_FALSE(is_looped_hare(list));
}

TEST(TestAlgorithmLib, IsLoopedTListHareAndTurtleEmptyList) {
  TList<int> list;

  EXPECT_FALSE(is_looped_hare(list));
}

TEST(TestAlgorithmLib, IsLoopedTListHareAndTurtleSingleElementFalse) {
  TList<int> list;

  list.push_back(1);

  EXPECT_FALSE(is_looped_hare(list));
}

TEST(TestAlgorithmLib, IsLoopedTListHareAndTurtleSingleElementTrue) {
  TList<int> list;

  list.push_back(1);

  list.tail()->next = list.head();

  EXPECT_TRUE(is_looped_hare(list));

  list.tail()->next = nullptr;
}

TEST(TestAlgorithmLib, IsLoopedReversedAlgorithmTrue) {
  TList<int> list;

  for (size_t i = 0; i < 5; i++) {
    list.push_back(1 + i);
  }

  list.tail()->next = list.head()->next;

  EXPECT_TRUE(is_looped_reverse(list));

  auto* current = list.head();
  EXPECT_EQ(current->value, 1);
  current = current->next;
  EXPECT_EQ(current->value, 2);
  current = current->next;
  EXPECT_EQ(current->value, 3);
  current = current->next;
  EXPECT_EQ(current->value, 4);
  current = current->next;
  EXPECT_EQ(current->value, 5);
  EXPECT_EQ(current->next, list.head()->next);

  list.tail()->next = nullptr;
}

TEST(TestAlgorithmLib, IsLoopedReversedAlgorithmFalse) {
  TList<int> list;

  for (size_t i = 0; i < 5; i++) {
    list.push_back(1 + i);
  }

  EXPECT_FALSE(is_looped_reverse(list));

  auto* current = list.head();
  EXPECT_EQ(current->value, 1);
  current = current->next;
  EXPECT_EQ(current->value, 2);
  current = current->next;
  EXPECT_EQ(current->value, 3);
  current = current->next;
  EXPECT_EQ(current->value, 4);
  current = current->next;
  EXPECT_EQ(current->value, 5);
  EXPECT_EQ(current->next, nullptr);
}


TEST(TestAlgorithmLib, IsLoopedReversedAlgorithmEmptyList) {
  TList<int> list;

  EXPECT_FALSE(is_looped_reverse(list));
}

TEST(TestAlgorithmLib, IsLoopedReversedAlgorithmSingleElementFalse) {
  TList<int> list;

  list.push_back(1);

  EXPECT_FALSE(is_looped_reverse(list));
}

TEST(TestAlgorithmLib, IsLoopedReversedAlgorithmSingleElementTrue) {
  TList<int> list;

  list.push_back(1);

  list.tail()->next = list.head();

  EXPECT_TRUE(is_looped_reverse(list));

  list.tail()->next = nullptr;
}

TEST(TestAlgorithmLib, FindLoopStart) {
  TList<int> list;

  for (size_t i = 0; i < 5; i++) {
    list.push_back(1 + i);
  }

  list.tail()->next = list.head()->next;

  EXPECT_EQ(list.head()->next, find_loop(list));

  list.tail()->next = nullptr;
}

TEST(TestAlgorithmLib, FindLoopStartNoCycleBase) {
  TList<int> list;
  for (int i = 1; i <= 5; i++) {
    list.push_back(i);
  }

  auto* loop_start = find_loop(list);
  EXPECT_EQ(loop_start, nullptr);
}

TEST(TestAlgorithmLib, FindLoopStartAlgorithmEmptyList) {
  TList<int> list;

  EXPECT_EQ(find_loop(list), nullptr);
}

TEST(TestAlgorithmLib, FindLoopStartSingleElementFalse) {
  TList<int> list;

  list.push_back(1);

  EXPECT_EQ(find_loop(list), nullptr);
}

TEST(TestAlgorithmLib, FindLoopStartSingleElementTrue) {
  TList<int> list;

  list.push_back(1);

  list.tail()->next = list.head();

  EXPECT_EQ(find_loop(list), list.head());

  list.tail()->next = nullptr;
}
