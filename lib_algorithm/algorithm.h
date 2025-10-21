// Copyright 2025 Smirnov Nikita

#ifndef LIB_ALGORITHM_ALGORITHM_H_
#define LIB_ALGORITHM_ALGORITHM_H_

#include <iostream>
#include<stdexcept>
#include "../lib_matrix/matrix.h"
#include "../lib_tdynamic_stack/tdynamic_stack.h"

int find_local_min(const Matrix<int>& matrix);

void find_best_neighbor(const Matrix<int>& matrix, size_t i, size_t j,
  size_t& new_i, size_t& new_j);

bool check_breckets(const std::string& str);

void read_expression(const std::string& expression);

#endif  // LIB_ALGORITHM_ALGORITHM_H_
