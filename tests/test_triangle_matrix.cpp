// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_triangle_matrix/triangle_matrix.h"

TEST(TestTriangleMatrixLib, CreateDefaultTriangleMatrix) {
  TriangleMatrix<int> matrix;

  EXPECT_EQ(matrix.get_lines(), 0);
  EXPECT_EQ(matrix.get_columns(), 0);
  EXPECT_EQ(matrix.get_dimension(), 0);
}

TEST(TestTriangleMatrixLib, CreateTriangleMatrixWithParams) {
  size_t dimension = 4;
  TriangleMatrix<int> matrix(dimension);

  EXPECT_EQ(matrix.get_dimension(), dimension);
  EXPECT_EQ(matrix.get_lines(), dimension);
  EXPECT_EQ(matrix.get_columns(), dimension);

  EXPECT_EQ(matrix[0].size(), 4);
  EXPECT_EQ(matrix[1].size(), 3);
  EXPECT_EQ(matrix[2].size(), 2);
  EXPECT_EQ(matrix[3].size(), 1);

  EXPECT_EQ(matrix[0].start_index(), 0);
  EXPECT_EQ(matrix[1].start_index(), 1);
  EXPECT_EQ(matrix[2].start_index(), 2);
  EXPECT_EQ(matrix[3].start_index(), 3);
}

TEST(TestTriangleMatrixLib, CreateTriangleMatrixFromData) {
  size_t dimension = 3;
  int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  const TriangleMatrix<int> matrix(dimension, data, 9);

  EXPECT_EQ(matrix[0][0], 1);
  EXPECT_EQ(matrix[0][1], 2);
  EXPECT_EQ(matrix[0][2], 3);

  EXPECT_EQ(matrix[1][0], 0);
  EXPECT_EQ(matrix[1][1], 5);
  EXPECT_EQ(matrix[1][2], 6);

  EXPECT_EQ(matrix[2][1], 0);
  EXPECT_EQ(matrix[2][0], 0);
  EXPECT_EQ(matrix[2][2], 9);
}

TEST(TestTriangleMatrixLib, CreateTriangleMatrixFromDataArrayThrowWhenNullptr) {
  int* data = nullptr;

  EXPECT_ANY_THROW(TriangleMatrix<int> matrix(3, data, 9));
}

TEST(TestTriangleMatrixLib,
  CreateTriangleMatrixFromDataArrayThrowWhenIncorrectSize) {
  int data[] = { 1, 2, 3, 4, 5, 6, 7, 8};

  EXPECT_ANY_THROW(TriangleMatrix<int> matrix(3, data, 8));
}

TEST(TestTriangleMatrixLib, CreateTriangleMatrixWithCopy) {
  int data1[] = {1, 2, 0, 4};
  TriangleMatrix<int> original(2, data1, 4);

  const TriangleMatrix<int> copyIt(original);

  EXPECT_EQ(copyIt[0].size(), 2);
  EXPECT_EQ(copyIt[1].size(), 1);

  EXPECT_EQ(copyIt.get_lines(), 2);
  EXPECT_EQ(copyIt.get_columns(), 2);
  EXPECT_EQ(copyIt.get_dimension(), 2);

  EXPECT_EQ(copyIt[0][0], 1);
  EXPECT_EQ(copyIt[0][1], 2);
  EXPECT_EQ(copyIt[1][0], 0);
  EXPECT_EQ(copyIt[1][1], 4);
}

TEST(TestTriangleMatrixLib, EqualyOperator) {
  TriangleMatrix<int> A(2);
  A[0][0] = 1; A[0][1] = 2; A[1][1] = 3;

  const TriangleMatrix<int> B = A;

  EXPECT_EQ(B.get_dimension(), 2);
  EXPECT_EQ(B[0][0], 1);
  EXPECT_EQ(B[0][1], 2);
  EXPECT_EQ(B[1][0], 0);
  EXPECT_EQ(B[1][1], 3);
}

TEST(TestTriangleMatrixLib, PlusEqualOperator) {
  int data1[] = { 1, 2, 0, 3 };
  int data2[] = { 4, 5, 0, 6 };

  TriangleMatrix<int> A(2, data1, 4);
  TriangleMatrix<int> B(2, data2, 4);

  A += B;

  const TriangleMatrix<int> C = A;

  EXPECT_EQ(C[0][0], 5);
  EXPECT_EQ(C[0][1], 7);
  EXPECT_EQ(C[1][0], 0);
  EXPECT_EQ(C[1][1], 9);
}

TEST(TestTriangleMatrixLib, PlusEqualOperatorThrowWhenDifferentDimensions) {
  int data1[] = { 1, 2, 0, 3 };
  int data2[] = { 4, 5, 6, 0, 7, 8, 0, 0, 11 };

  TriangleMatrix<int> A(2, data1, 4);
  TriangleMatrix<int> B(3, data2, 9);

  EXPECT_ANY_THROW(A += B);
}

TEST(TestTriangleMatrixLib, MinusEqualOperator) {
  int data1[] = { 1, 2, 0, 3 };
  int data2[] = { 4, 5, 0, 6 };

  TriangleMatrix<int> A(2, data1, 4);
  TriangleMatrix<int> B(2, data2, 4);

  B -= A;

  const TriangleMatrix<int> C = B;

  EXPECT_EQ(C[0][0], 3);
  EXPECT_EQ(C[0][1], 3);
  EXPECT_EQ(C[1][0], 0);
  EXPECT_EQ(C[1][1], 3);
}

TEST(TestTriangleMatrixLib, MinusEqualOperatorThrowWhenDifferentDimensions) {
  int data1[] = { 1, 2, 0, 3 };
  int data2[] = { 4, 5, 6, 0, 7, 8, 0, 0 , 11 };

  TriangleMatrix<int> A(2, data1, 4);
  TriangleMatrix<int> B(3, data2, 9);

  EXPECT_ANY_THROW(B -= A);
}

TEST(TestTriangleMatrixLib, OperatorPlus) {
  int data1[] = { 1, 2, 0, 3 };
  int data2[] = { 4, 5, 0, 6 };

  TriangleMatrix<int> A(2, data1, 4);
  TriangleMatrix<int> B(2, data2, 4);

  const TriangleMatrix<int> result = A + B;

  EXPECT_EQ(result.get_dimension(), 2);
  EXPECT_EQ(result[0][0], 5);
  EXPECT_EQ(result[0][1], 7);
  EXPECT_EQ(result[1][0], 0);
  EXPECT_EQ(result[1][1], 9);
}

TEST(TestTriangleMatrixLib, OperatorMinus) {
  int data1[] = { 10, 20, 4, 30 };
  int data2[] = { 4, 5, 4, 6 };

  TriangleMatrix<int> A(2, data1, 4);
  TriangleMatrix<int> B(2, data2, 4);

  const TriangleMatrix<int> result = A - B;

  EXPECT_EQ(result.get_dimension(), 2);
  EXPECT_EQ(result[0][0], 6);
  EXPECT_EQ(result[0][1], 15);
  EXPECT_EQ(result[1][0], 0);
  EXPECT_EQ(result[1][1], 24);
}

TEST(TestTriangleMatrixLib, MultiplyEqualScalar) {
  int data[] = { 1, 2, 0, 3 };
  TriangleMatrix<int> matrix(2, data, 4);

  matrix *= 3;

  const TriangleMatrix<int> Cmatrix = matrix;

  EXPECT_EQ(Cmatrix[0][0], 3);
  EXPECT_EQ(Cmatrix[0][1], 6);
  EXPECT_EQ(Cmatrix[1][0], 0);
  EXPECT_EQ(Cmatrix[1][1], 9);
}

TEST(TestTriangleMatrixLib, MultiplyScalarOperator) {
  int data[] = { 1, 2, 0, 3 };
  TriangleMatrix<int> original(2, data, 4);

  const TriangleMatrix<int> result = original * 3;

  EXPECT_EQ(result[0][0], 3);
  EXPECT_EQ(result[0][1], 6);
  EXPECT_EQ(result[1][0], 0);
  EXPECT_EQ(result[1][1], 9);

  EXPECT_EQ(original[0][0], 1);
  EXPECT_EQ(original[0][1], 2);
  EXPECT_EQ(original[1][1], 3);
}

TEST(TestTriangleMatrixLib, EqualityOperator) {
  int data1[] = { 1, 2, 0, 3 };
  int data2[] = { 1, 2, 0, 3 };
  int data3[] = { 1, 2, 0, 4 };

  TriangleMatrix<int> A(2, data1, 4);
  TriangleMatrix<int> B(2, data2, 4);
  TriangleMatrix<int> C(2, data3, 4);

  EXPECT_TRUE(A == B);
  EXPECT_FALSE(A == C);
  EXPECT_TRUE(A != C);
}

TEST(TestTriangleMatrixLib, EqualityDifferentDimensions) {
  TriangleMatrix<int> A(2);
  TriangleMatrix<int> B(3);

  EXPECT_FALSE(A == B);
  EXPECT_TRUE(A != B);
}

TEST(TestTriangleMatrixLib, EqualityWithItself) {
  TriangleMatrix<int> A(2);
  A[0][0] = 5; A[0][1] = 6; A[1][1] = 7;

  EXPECT_TRUE(A == A);
  EXPECT_FALSE(A != A);
}

TEST(TestTriangleMatrixLib, MultiplicationTriangleMatrix) {
  TriangleMatrix<int> A(2), B(2);
  A[0][0] = 1; A[0][1] = 2;
  A[1][1] = 3;
  B[0][0] = 4; B[0][1] = 5;
  B[1][1] = 6;

  const TriangleMatrix<int> result = A * B;

  EXPECT_EQ(result[0][0], 4);
  EXPECT_EQ(result[0][1], 17);
  EXPECT_EQ(result[1][0], 0);
  EXPECT_EQ(result[1][1], 18);
}

TEST(TestTriangleMatrixLib, MultiplicationTriangleMatrixDifferentDimensions) {
  TriangleMatrix<int> A(2);
  TriangleMatrix<int> B(3);

  EXPECT_ANY_THROW(TriangleMatrix<int> result = A * B);
}
