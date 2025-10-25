// Copyright 2025 Smirnov Nikita

#include<random>
#include <string>
#include "../lib_algorithm/algorithm.h"

int find_local_min(const Matrix<int>& matrix) {
  if (matrix.get_lines() != matrix.get_columns()) {
    throw std::logic_error("Matrix lines and columns don't match!");
  }

  size_t dimension = matrix.get_lines();

  if (dimension == 0) {
    throw std::logic_error("Matrix is empty!");
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> dis(0, dimension - 1);

  size_t i = dis(gen);
  size_t j = dis(gen);

  while (true) {
    size_t new_i = i, new_j = j;

    find_best_neighbor(matrix, i, j, new_i, new_j);

    if (new_i == i && new_j == j) return matrix[i][j];

    i = new_i;
    j = new_j;
  }
}

void find_best_neighbor(const Matrix<int>& matrix, size_t i, size_t j,
  size_t& new_i, size_t& new_j) {
  size_t dimension = matrix.get_lines();

  if (i > 0 && matrix[i - 1][j] < matrix[new_i][new_j]) {
    new_i = i - 1;
    new_j = j;
  }

  if (i < dimension - 1 && matrix[i + 1][j] < matrix[new_i][new_j]) {
    new_i = i + 1;
    new_j = j;
  }

  if (j > 0 && matrix[i][j - 1] < matrix[new_i][new_j]) {
    new_i = i;
    new_j = j - 1;
  }

  if (j < dimension - 1 && matrix[i][j + 1] < matrix[new_i][new_j]) {
    new_i = i;
    new_j = j + 1;
  }
}

bool check_breckets(const std::string& str) {
  TDynamicStack<char> checker(str.length());

  for (char c : str) {
    if ((c != '(') && (c != ')')
      && (c != '{') && (c != '}')
      && (c != '[') && (c != ']')) {
      continue;
    }
    if (c == '(' || c == '[' || c == '{') {
      checker.push(c);
    } else {
      if (checker.is_empty()) {
        return false;
      }

      char top = checker.top();

      if ((c == ')' && top != '(') ||
        (c == ']' && top != '[') ||
        (c == '}' && top != '{')) {
        return false;
      }

      checker.pop();
    }
  }

  return checker.is_empty();
}

void read_expression(const std::string& expression) {
  for (char c : expression) {
  }
}
