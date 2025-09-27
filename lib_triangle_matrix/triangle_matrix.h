// Copyright 2025 Smirnov Nikita

#ifndef LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#define LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_

#include<iostream>
#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
  size_t _dimension;

 public:
  explicit TriangleMatrix(size_t dimension = 0);

  TriangleMatrix(size_t dimension, const T* data, size_t data_size);

  TriangleMatrix(const TriangleMatrix<T>& other) = default;

  ~TriangleMatrix() = default;

  inline size_t get_dimension() const {
    return _dimension;
  }

  TriangleMatrix<T>& operator+=(const TriangleMatrix<T>& other);

  TriangleMatrix<T>& operator-=(const TriangleMatrix<T>& other);

  TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const;

  TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const;

  TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) const;

  TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);

  friend std::istream& operator>>(std::istream& is,
    TriangleMatrix<T>& tmatrix) {
    std::cout << "\n[Work istream function TM]\n\n";

    return is;
  }

  friend std::ostream& operator<<(std::ostream& os,
    const TriangleMatrix<T>& tmatrix) {
    return os;
  }
};

template <class T>
TriangleMatrix<T>::TriangleMatrix(size_t dimension)
  : Matrix<T>(dimension, dimension), _dimension(dimension) {
  for (size_t i = 0; i < dimension; i++) {
    (*this)[i] = MVector<T>(dimension - i, i);
  }
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(size_t dimension, const T* data, size_t data_size)
: Matrix<T>(dimension, dimension), _dimension(dimension) {

  if (!data) {
    throw std::invalid_argument("Data pointer cannot be null in "
      "TriangleMatrix constructor");
  }

  size_t required_size = dimension * dimension;
  if (data_size < required_size) {
    throw std::invalid_argument("Data array too small in "
      "TriangleMatrix constructor");
  }

  for (size_t i = 0; i < dimension; i++) {
    (*this)[i] = MVector<T>(dimension - i, i);
    for (size_t j = i; j < dimension; j++) {
      (*this)[i][j] = data[i * dimension + j];
    }
  }
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have equal "
      "dimensions for addition");
  }

  Matrix<T>::operator+=(other);
  return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have equal "
      "dimensions for subtraction");
  }

  Matrix<T>::operator-=(other);
  return *this;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+
(const TriangleMatrix<T>& other) const {
  TriangleMatrix<T> result = *this;
  result += other;
  return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-
(const TriangleMatrix<T>& other) const  {
  TriangleMatrix<T> result = *this;
  result -= other;
  return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) const {
  return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=
(const TriangleMatrix<T>& other) {
  if (this != &other) {
    Matrix<T>::operator=(other);
    _dimension = other._dimension;
  }
  return *this;
}

#endif  // LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
