// Copyright 2025 Smirnov Nikita

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include<iostream>
#include "../lib_mathvector/mathvector.h"

template <class T>
class Matrix : public MVector<MVector<T>> {
  size_t _lines, _columns;

 public:
  Matrix(size_t lines = 0, size_t columns = 0);
  Matrix(size_t lines, size_t columns, const T* data);
  Matrix(const Matrix<T>& other);
  ~Matrix();

  inline size_t get_lines() {
    return _lines;
  }

  inline size_t get_columns() {
    return _columns;
  }

  Matrix<T> operator+(const Matrix<T>& other);

  Matrix<T> operator-(const Matrix<T>& other);

  Matrix<T> operator*(T val);

  MVector<T> operator*(MVector<T> vec);

  Matrix<T> operator*(Matrix<T> matr);

  Matrix<T>& operator=(const Matrix<T>& other);

  friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
    std::cout << "\n[Work istream function M]\n\n";

    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    return os;
  }
};

template <class T>
Matrix<T>::Matrix(size_t lines, size_t columns) {
}

template <class T>
Matrix<T>::Matrix(size_t lines, size_t columns, const T* data) {
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other) {
}


template <class T>
Matrix<T>::~Matrix() {
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(T val) {
  return *this;
}

template <class T>
MVector<T> Matrix<T>::operator*(MVector<T> vec) {
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> matr) {
  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
  return *this;
}

#endif  // LIB_MATRIX_MATRIX_H_
