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

  TriangleMatrix<T>& operator*=(T val);

  TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const;

  TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const;

  TriangleMatrix<T> operator*(T val) const;

  TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) const;

  TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);

  bool operator==(const TriangleMatrix<T>& other) const;

  bool operator!=(const TriangleMatrix<T>& other) const;

  friend std::istream& operator>>(std::istream& is,
    TriangleMatrix<T>& tmatrix) {
    T* data = new T[tmatrix._dimension * tmatrix._dimension];
    for (size_t i = 0; i < tmatrix._dimension * tmatrix._dimension; i++) {
      is >> data[i];
    }

    for (size_t i = 0; i < tmatrix._dimension; i++) {
      for (size_t j = i; j < tmatrix._dimension; j++) {
        tmatrix[i][j] = data[i * tmatrix._dimension + j];
      }
    }

    return is;
  }

  friend std::ostream& operator<<(std::ostream& os,
    const TriangleMatrix<T>& tmatrix) {
    for (size_t i = 0; i < tmatrix._dimension; i++) {
      for (size_t j = 0; j < tmatrix._dimension; j++) {
        os << tmatrix[i][j];
        if (j < tmatrix._dimension - 1) {
          os << " ";
        }
      }
      if (i < tmatrix._dimension - 1) {
        os << "\n";
      }
    }
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
TriangleMatrix<T>::TriangleMatrix(size_t dimension,
  const T* data, size_t data_size)
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
TriangleMatrix<T>& TriangleMatrix<T>::operator+=
(const TriangleMatrix<T>& other) {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have equal "
      "dimensions for addition");
  }

  Matrix<T>::operator+=(other);
  return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=
(const TriangleMatrix<T>& other) {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have equal "
      "dimensions for subtraction");
  }

  Matrix<T>::operator-=(other);
  return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(T val) {
  Matrix<T>::operator*=(val);
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
TriangleMatrix<T> TriangleMatrix<T>::operator*
(const TriangleMatrix<T>& other) const {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have same "
      "dimension for multiplication");
  }

  TriangleMatrix<T> result(_dimension);

  for (size_t i = 0; i < _dimension; i++) {
    for (size_t j = i; j < _dimension; j++) {
      T sum = T();
      for (size_t k = i; k <= j; k++) {
        sum += (*this)[i][k] * other[k][j];
      }
      result[i][j] = sum;
    }
  }

  return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(T val) const {
  TriangleMatrix<T> result = *this;
  result *= val;
  return result;
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

template <class T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other) const {
  if (_dimension != other._dimension) {
    return false;
  }

  return Matrix<T>::operator==(other);
}

template <class T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other) const {
  return !(*this == other);
}

#endif  // LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
