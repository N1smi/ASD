// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_matrix/matrix.h"

TEST(TestMatrixLib, CreateDefaultMatrix) {
  Matrix<int> matrix;

  EXPECT_EQ(matrix.get_lines(), 0);
  EXPECT_EQ(matrix.get_columns(), 0);
  EXPECT_TRUE(matrix.is_empty());
}

TEST(TestMatrixLib, CreateMatrixWithDimensions) {
  size_t lines = 3;
  size_t columns = 4;
  Matrix<int> matrix(lines, columns);

  EXPECT_EQ(matrix.get_lines(), lines);
  EXPECT_EQ(matrix.get_columns(), columns);
  EXPECT_EQ(matrix.size(), lines);
}

TEST(TestMatrixLib, CreateMatrixFromDataArray) {
  int data[] = { 1, 2, 3, 4, 5, 6 };
  Matrix<int> matrix(2, 3, data);

  EXPECT_EQ(matrix.get_lines(), 2);
  EXPECT_EQ(matrix.get_columns(), 3);

  EXPECT_EQ(matrix[0][0], 1);
  EXPECT_EQ(matrix[0][1], 2);
  EXPECT_EQ(matrix[0][2], 3);
  EXPECT_EQ(matrix[1][0], 4);
  EXPECT_EQ(matrix[1][1], 5);
  EXPECT_EQ(matrix[1][2], 6);
}

TEST(TestMatrixLib, CreateMatrixWithCopy) {
  Matrix<int> original(2, 3);
  original[0][0] = 1; original[0][1] = 2; original[0][2] = 3;
  original[1][0] = 4; original[1][1] = 5; original[1][2] = 6;

  Matrix<int> Itcopy(original);

  EXPECT_EQ(Itcopy.get_lines(), original.get_lines());
  EXPECT_EQ(Itcopy.get_columns(), original.get_columns());
  EXPECT_EQ(Itcopy.size(), original.size());

  for (size_t i = 0; i < original.get_lines(); i++) {
    for (size_t j = 0; j < original.get_columns(); j++) {
      EXPECT_EQ(Itcopy[i][j], original[i][j]);
    }
  }
}

TEST(TestMatrixLib, OperatorPlusEqual) {
  int data1[] = {1, 2, 3, 4};
  Matrix<int> matrix1(2, 2, data1);

  int data2[] = {5, 6, 7, 8};
  Matrix<int> matrix2(2, 2, data2);

  matrix1 += matrix2;

  EXPECT_EQ(matrix1[0][0], 6);
  EXPECT_EQ(matrix1[0][1], 8);
  EXPECT_EQ(matrix1[1][0], 10);
  EXPECT_EQ(matrix1[1][1], 12);
}

TEST(TestMatrixLib, OperatorPlusEqualThrowWhenDifferentSizes) {
  Matrix<int> matrix1(2, 2);
  Matrix<int> matrix2(3, 3);

  EXPECT_ANY_THROW(matrix1 += matrix2);
}

TEST(TestMatrixLib, OperatorEqualMatrix) {
  int data1[] = { 1, 2, 3, 4, 5, 6 };
  Matrix<int> original(2, 3, data1);

  Matrix<int> assigned(1, 1);
  assigned = original;

  EXPECT_EQ(assigned.get_lines(), original.get_lines());
  EXPECT_EQ(assigned.get_columns(), original.get_columns());

  for (size_t i = 0; i < original.get_lines(); ++i) {
    for (size_t j = 0; j < original.get_columns(); ++j) {
      EXPECT_EQ(assigned[i][j], original[i][j]);
    }
  }
}

TEST(TestMatrixLib, OperatorPlus) {
  int data1[] = { 1, 2, 3, 4 };
  int data2[] = { 5, 6, 7, 8 };

  Matrix<int> matrix1(2, 2, data1);
  Matrix<int> matrix2(2, 2, data2);

  Matrix<int> result = matrix1 + matrix2;

  EXPECT_EQ(result[0][0], 6);
  EXPECT_EQ(result[0][1], 8);
  EXPECT_EQ(result[1][0], 10);
  EXPECT_EQ(result[1][1], 12);

  EXPECT_EQ(matrix1[0][0], 1);
  EXPECT_EQ(matrix1[1][1], 4);
  EXPECT_EQ(matrix2[0][0], 5);
  EXPECT_EQ(matrix2[1][1], 8);
}

TEST(TestMatrixLib, OperatorMinusEqual) {
  int data1[] = { 10, 20, 30, 40 };
  int data2[] = { 1, 2, 3, 4 };

  Matrix<int> matrix1(2, 2, data1);
  Matrix<int> matrix2(2, 2, data2);

  matrix1 -= matrix2;

  EXPECT_EQ(matrix1[0][0], 9);
  EXPECT_EQ(matrix1[0][1], 18);
  EXPECT_EQ(matrix1[1][0], 27);
  EXPECT_EQ(matrix1[1][1], 36);
}

TEST(TestMatrixLib, OperatorMinusEqualThrowWhenDifferentSizes) {
  Matrix<int> matrix1(2, 2);
  Matrix<int> matrix2(3, 3);

  EXPECT_ANY_THROW(matrix1 -= matrix2);
}

TEST(TestMatrixLib, OperatorMinus) {
  int data1[] = { 10, 20, 30, 40 };
  int data2[] = { 1, 2, 3, 4 };

  Matrix<int> matrix1(2, 2, data1);
  Matrix<int> matrix2(2, 2, data2);

  Matrix<int> result = matrix1 - matrix2;

  EXPECT_EQ(result[0][0], 9);
  EXPECT_EQ(result[0][1], 18);
  EXPECT_EQ(result[1][0], 27);
  EXPECT_EQ(result[1][1], 36);

  EXPECT_EQ(matrix1[0][0], 10);
  EXPECT_EQ(matrix1[1][1], 40);
  EXPECT_EQ(matrix2[0][0], 1);
  EXPECT_EQ(matrix2[1][1], 4);
}

TEST(TestMatrixLib, OperatorMultiplyEqualScalar) {
  int data[] = { 1, 2, 3, 4 };
  Matrix<int> matrix(2, 2, data);

  matrix *= 3;

  EXPECT_EQ(matrix[0][0], 3);
  EXPECT_EQ(matrix[0][1], 6);
  EXPECT_EQ(matrix[1][0], 9);
  EXPECT_EQ(matrix[1][1], 12);
}

TEST(TestMatrixLib, OperatorMultiplyScalar) {
  int data[] = { 1, 2, 3, 4 };
  Matrix<int> matrix(2, 2, data);

  Matrix<int> result = matrix * 3;

  EXPECT_EQ(result[0][0], 3);
  EXPECT_EQ(result[0][1], 6);
  EXPECT_EQ(result[1][0], 9);
  EXPECT_EQ(result[1][1], 12);

  EXPECT_EQ(matrix[0][0], 1);
  EXPECT_EQ(matrix[0][1], 2);
  EXPECT_EQ(matrix[1][0], 3);
  EXPECT_EQ(matrix[1][1], 4);
}

TEST(TestMatrixLib, OperatorStrictlyEqual) {
  int data1[] = { 1, 2, 3, 4 };
  int data2[] = { 1, 2, 3, 4 };
  int data3[] = { 1, 2, 3, 5 };

  Matrix<int> matrix1(2, 2, data1);
  Matrix<int> matrix2(2, 2, data2);
  Matrix<int> matrix3(2, 2, data3);

  EXPECT_TRUE(matrix1 == matrix2);
  EXPECT_FALSE(matrix1 == matrix3);
}

TEST(TestMatrixLib, OperatorStrictlyNotEqual) {
  int data1[] = { 1, 2, 3, 4 };
  int data2[] = { 1, 2, 3, 5 };

  Matrix<int> matrix1(2, 2, data1);
  Matrix<int> matrix2(2, 2, data2);

  EXPECT_TRUE(matrix1 != matrix2);
  EXPECT_FALSE(matrix1 != matrix1);
}

TEST(TestMatrixLib, MatrixAndVectorMultiplication) {
  int matrixData[] = { 1, 2, 3, 4, 5, 6 };

  Matrix<int> matrix(3, 2, matrixData);
  MVector<int> vector({ 2, 1 });

  MVector<int> result = matrix * vector;

  EXPECT_EQ(result[0], 4);
  EXPECT_EQ(result[1], 10);
  EXPECT_EQ(result[2], 16);
}

TEST(TestMatrixLib, MatrixAndVectorMultiplicationThrowWhenIncorrectSize) {
  int matrixData[] = { 1, 2, 3, 4, 5, 6 };

  Matrix<int> matrix(3, 2, matrixData);
  MVector<int> vector({ 1, 2, 3 });

  EXPECT_ANY_THROW(MVector<int> result = matrix * vector);
}

TEST(TestMatrixLib, MatrixMultiplication) {
  int data1[] = { 1, 2, 3, 4 };
  int data2[] = { 5, 6, 7, 8 };

  Matrix<int> matrix1(2, 2, data1);
  Matrix<int> matrix2(2, 2, data2);

  Matrix<int> result = matrix1 * matrix2;

  EXPECT_EQ(result.get_lines(), 2);
  EXPECT_EQ(result.get_columns(), 2);

  EXPECT_EQ(result[0][0], 19);
  EXPECT_EQ(result[0][1], 22);
  EXPECT_EQ(result[1][0], 43);
  EXPECT_EQ(result[1][1], 50);
}

TEST(TestMatrixLib, MatrixMultiplicationIncompatibleSizes) {
  int data1[] = { 1, 2, 3, 4 };
  int data2[] = { 1, 2, 3, 4, 5, 6 };

  Matrix<int> matrix1(2, 2, data1);
  Matrix<int> matrix2(3, 2, data2);

  EXPECT_ANY_THROW(Matrix<int> result = matrix1 * matrix2);
}

TEST(TestMatrixLib, OperatorEqualMatrixAndMVector) {
  MVector<int> vec({ 1, 2, 3, 4, 5 });
  Matrix<int> matrix;

  matrix = vec;

  EXPECT_EQ(matrix.get_lines(), 5);
  EXPECT_EQ(matrix.get_columns(), 1);

  EXPECT_EQ(matrix[0][0], 1);
  EXPECT_EQ(matrix[1][0], 2);
  EXPECT_EQ(matrix[2][0], 3);
  EXPECT_EQ(matrix[3][0], 4);
  EXPECT_EQ(matrix[4][0], 5);
}

TEST(TestMatrixLib, OperatorEqualMatrixAndScalar) {
  Matrix<int> matrix(3, 3);

  matrix = 42;

  EXPECT_EQ(matrix.get_lines(), 1);
  EXPECT_EQ(matrix.get_columns(), 1);
  EXPECT_EQ(matrix[0][0], 42);
}
