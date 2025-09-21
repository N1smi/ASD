// Copyright 2025 Smirnov Nikita

#ifndef LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#define LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_

#include<iostream>
#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
 public:
  explicit TriangleMatrix(size_t dimension = 0);
  TriangleMatrix(size_t dimension, const T* data);
  TriangleMatrix(const TriangleMatrix<T>& other);
  ~TriangleMatrix();

  TriangleMatrix<T> operator+(const TriangleMatrix<T>& other);

  TriangleMatrix<T> operator-(const TriangleMatrix<T>& other);

  TriangleMatrix<T> operator*(TriangleMatrix<T> matr);

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
TriangleMatrix<T>::TriangleMatrix(size_t dimension) {
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(size_t dimension, const T* data) {
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) {
}

template <class T>
TriangleMatrix<T>::~TriangleMatrix() {
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+
(const TriangleMatrix<T>& other) {
  return *this;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-
(const TriangleMatrix<T>& other) {
  return *this;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(TriangleMatrix<T> matr) {
  return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=
(const TriangleMatrix<T>& other) {
  return *this;
}

#endif  // LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
