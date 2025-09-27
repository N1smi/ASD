// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_mathvector/mathvector.h"

TEST(TestMathVectorLib, CreateVectorWithStartIndex) {
  MVector<int> vec(5, 2);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec.start_index(), 2);
  EXPECT_NE(vec.data(), nullptr);
}

TEST(TestMathVectorLib, OperatorPlusEqual) {
  MVector<int> vec1 = { 1, 2, 3 };
  MVector<int> vec2 = { 4, 5, 6 };

  vec1 += vec2;

  EXPECT_EQ(vec1.size(), 3);
  EXPECT_EQ(vec1[0], 5);
  EXPECT_EQ(vec1[1], 7);
  EXPECT_EQ(vec1[2], 9);

  EXPECT_EQ(vec2[0], 4);
  EXPECT_EQ(vec2[1], 5);
  EXPECT_EQ(vec2[2], 6);
}

TEST(TestMathVectorLib, PlusEqualWithStartIndex) {
  MVector<int> vec1(3, 1);
  MVector<int> vec2(3, 1);

  vec1[1] = 10; vec1[2] = 20; vec1[3] = 30;
  vec2[1] = 5; vec2[2] = 6; vec2[3] = 7;

  vec1 += vec2;

  EXPECT_EQ(vec1[0], 0);
  EXPECT_EQ(vec1[1], 15);
  EXPECT_EQ(vec1[2], 26);
  EXPECT_EQ(vec1[3], 37);
}

TEST(TestMathVectorLib, PlusEqualWithStartIndexThrowWhenDifferent) {
  MVector<int> vec1(3, 1);
  MVector<int> vec2(3, 2);

  vec1[1] = 10; vec1[2] = 20; vec1[3] = 30;
  vec2[2] = 5; vec2[3] = 6; vec2[4] = 7;

  EXPECT_ANY_THROW(vec1 += vec2);
}

TEST(TestMathVectorLib, OperatorPlusEqualThrowWhenDifferentSizes) {
  MVector<int> vec1 = { 1, 2, 3 };
  MVector<int> vec2 = { 1, 2 };

  EXPECT_ANY_THROW(vec1 += vec2);
}

TEST(TestMathVectorLib, OperatorPlus) {
  MVector<int> vec1 = { 1, 2, 3 };
  MVector<int> vec2 = { 4, 5, 6 };

  MVector<int> result = vec1 + vec2;

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], 5);
  EXPECT_EQ(result[1], 7);
  EXPECT_EQ(result[2], 9);

  EXPECT_EQ(vec1[0], 1);
  EXPECT_EQ(vec1[1], 2);
  EXPECT_EQ(vec1[2], 3);
  EXPECT_EQ(vec2[0], 4);
  EXPECT_EQ(vec2[1], 5);
  EXPECT_EQ(vec2[2], 6);
}

TEST(TestMathVectorLib, OperatorMinusEqual) {
  MVector<int> vec1 = { 10, 20, 30 };
  MVector<int> vec2 = { 4, 5, 6 };

  vec1 -= vec2;

  EXPECT_EQ(vec1.size(), 3);
  EXPECT_EQ(vec1[0], 6);
  EXPECT_EQ(vec1[1], 15);
  EXPECT_EQ(vec1[2], 24);

  EXPECT_EQ(vec2[0], 4);
  EXPECT_EQ(vec2[1], 5);
  EXPECT_EQ(vec2[2], 6);
}

TEST(TestMathVectorLib, MinusEqualWithStartIndex) {
  MVector<int> vec1(3, 1);
  MVector<int> vec2(3, 1);

  vec1[1] = 10; vec1[2] = 20; vec1[3] = 30;
  vec2[1] = 5; vec2[2] = 6; vec2[3] = 7;

  vec1 -= vec2;

  EXPECT_EQ(vec1[0], 0);
  EXPECT_EQ(vec1[1], 5);
  EXPECT_EQ(vec1[2], 14);
  EXPECT_EQ(vec1[3], 23);
}

TEST(TestMathVectorLib, MinusEqualWithStartIndexThrowWhenDifferent) {
  MVector<int> vec1(3, 1);
  MVector<int> vec2(3, 2);

  vec1[1] = 10; vec1[2] = 20; vec1[3] = 30;
  vec2[2] = 5; vec2[3] = 6; vec2[4] = 7;

  EXPECT_ANY_THROW(vec1 -= vec2);
}

TEST(TestMathVectorLib, OperatorMinusEqualThrowWhenDifferentSizes) {
  MVector<int> vec1 = { 1, 2, 3 };
  MVector<int> vec2 = { 1, 2 };

  EXPECT_ANY_THROW(vec1 -= vec2);
}

TEST(TestMathVectorLib, OperatorMinus) {
  MVector<int> vec1 = { 10, 20, 30 };
  MVector<int> vec2 = { 4, 5, 6 };

  MVector<int> result = vec1 - vec2;

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], 6);
  EXPECT_EQ(result[1], 15);
  EXPECT_EQ(result[2], 24);

  EXPECT_EQ(vec1[0], 10);
  EXPECT_EQ(vec1[1], 20);
  EXPECT_EQ(vec1[2], 30);
  EXPECT_EQ(vec2[0], 4);
  EXPECT_EQ(vec2[1], 5);
  EXPECT_EQ(vec2[2], 6);
}

TEST(TestMathVectorLib, OperatorMultiplyEqualScalar) {
  MVector<int> vec = { 1, 2, 3, 4 };

  vec *= 2;

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 2);
  EXPECT_EQ(vec[1], 4);
  EXPECT_EQ(vec[2], 6);
  EXPECT_EQ(vec[3], 8);
}

TEST(TestMathVectorLib, OperatorMultiplyScalar) {
  MVector<int> vec = { 1, 2, 3 };

  MVector<int> result = vec * 3;

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], 3);
  EXPECT_EQ(result[1], 6);
  EXPECT_EQ(result[2], 9);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(TestMathVectorLib, OperatorMultiply) {
  MVector<int> vec1 = { 1, 2, 3 };
  MVector<int> vec2 = { 4, 5, 6 };

  int result = vec1 * vec2;

  EXPECT_EQ(result, 32);
}

TEST(TestMathVectorLib, OperatorMultiplyThrowWhenDifferentSizes) {
  MVector<int> vec1 = { 1, 2, 3 };
  MVector<int> vec2 = { 1, 2 };

  EXPECT_ANY_THROW(vec1 * vec2);
}

TEST(TestMathVectorLib, OperatorBracketsWithStartIndex) {
  MVector<int> vec(3, 2);

  vec[2] = 10;
  vec[3] = 20;
  vec[4] = 30;

  EXPECT_EQ(vec[2], 10);
  EXPECT_EQ(vec[3], 20);
  EXPECT_EQ(vec[4], 30);
}

TEST(TestMathVectorLib, OperatorBracketsWithStartIndexZero) {
  MVector<int> vec(3, 2);

  vec[2] = 10;
  vec[3] = 20;
  vec[4] = 30;

  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 0);
}

TEST(TestMathVectorLib, AtWithSrartIndexZero) {
  MVector<int> vec(3, 2);

  EXPECT_EQ(vec.at(0), 0);
  EXPECT_EQ(vec.at(1), 0);
}

TEST(TestMathVectorLib, AtWithSrartIndexThrowWhenUpperIndices) {
  MVector<int> vec(3, 2);

  EXPECT_THROW(vec.at(5), std::out_of_range);
  EXPECT_THROW(vec.at(6), std::out_of_range);
  EXPECT_THROW(vec.at(100), std::out_of_range);
}

TEST(TestMathVectorLib, AtWithStartIndex) {
  MVector<int> vec(3, 2);

  vec.at(2) = 10;
  vec.at(3) = 20;
  vec.at(4) = 30;

  EXPECT_EQ(vec.at(2), 10);
  EXPECT_EQ(vec.at(3), 20);
  EXPECT_EQ(vec.at(4), 30);
}


