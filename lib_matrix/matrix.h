// Copyright 2025 Smirnov Nikita  // NOLINT

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include<iostream>
#include<stdexcept>
#include "../lib_mathvector/mathvector.h"

template <class T>
class Matrix : public MVector<MVector<T>> {
  size_t _lines, _columns;

 public:
  explicit Matrix(size_t lines = 0, size_t columns = 0);

  Matrix(size_t lines, size_t columns, const T* data, size_t data_size);

  Matrix(const Matrix<T>& other);

  ~Matrix();

  inline size_t get_lines() const {
    return _lines;
  }

 inline size_t get_columns() const {
    return _columns;
  }

  Matrix<T>& operator+=(const Matrix<T>& other);

  Matrix<T>& operator-=(const Matrix<T>& other);

  Matrix<T>& operator*=(T val);

  Matrix<T> operator+(const Matrix<T>& other) const;

  Matrix<T> operator-(const Matrix<T>& other) const;

  Matrix<T> operator*(T val) const;

  MVector<T> operator*(const MVector<T>& vec) const;

  Matrix<T> operator*(const Matrix<T>& other) const;

  Matrix<T>& operator=(const Matrix<T>& other);

  Matrix<T>& operator=(const MVector<T>& vec);

  Matrix<T>& operator=(T val);

  bool operator==(const Matrix<T>& other) const;

  bool operator!=(const Matrix<T>& other) const;

  friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix._lines; i++) {
      for (size_t j = 0; j < matrix._columns; j++) {
        is >> matrix[i][j];
      }
    }
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix._lines; ++i) {
      for (size_t j = 0; j < matrix._columns; ++j) {
        os << matrix[i][j];
        if (j < matrix._columns - 1) {
          os << " ";
        }
      }
      if (i < matrix._lines - 1) {
        os << "\n";
      }
    }
    return os;
  }

 private:
  MVector<T> get_column(size_t column_index) const;
};

template <class T>
Matrix<T>::Matrix(size_t lines, size_t columns)
  : MVector<MVector<T>>(lines), _lines(lines), _columns(columns) {
  for (size_t i = 0; i < lines; i++) {
    (*this)[i] = MVector<T>(columns);
  }
}

template <class T>
Matrix<T>::Matrix(size_t lines, size_t columns, const T* data, size_t data_size)
  : MVector<MVector<T>>(lines), _lines(lines), _columns(columns) {

  if (!data) {
    throw std::invalid_argument("Data pointer cannot be null in Matrix "
      "constructor");
  }

  size_t required_size = lines * columns;
  if (data_size < required_size) {
    throw std::invalid_argument("Data array too small in Matrix "
      "constructor");
  }

  for (size_t i = 0; i < lines; i++) {
    (*this)[i] = MVector<T>(columns);
    for (size_t j = 0; j < columns; j++) {
      (*this)[i][j] = data[i * columns + j];
    }
  }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other)
  : MVector<MVector<T>>(other._lines), _lines(other._lines),
  _columns(other._columns) {
  for (size_t i = 0; i < _lines; i++) {
    (*this)[i] = other[i];
  }
}

template <class T>
Matrix<T>::~Matrix() {
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
  if (_lines != other._lines || _columns != other._columns) {
    throw std::logic_error("Size error: the matrices must have equal sizes "
      "in the addition operation!");
  }
  for (size_t i = 0; i < _lines; i++) {
    (*this)[i] += other[i];
  }
  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
  if (_lines != other._lines || _columns != other._columns) {
    throw std::logic_error("Size error: the matrices must have equal sizes "
      "in the subtraction operation!");
  }
  for (size_t i = 0; i < _lines; i++) {
    (*this)[i] -= other[i];
  }
  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(T val) {
  for (size_t i = 0; i < _lines; i++) {
    (*this)[i] *= val;
  }
  return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
  Matrix<T> result = *this;
  result += other;
  return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
  Matrix<T> result = *this;
  result -= other;
  return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(T val) const {
  Matrix<T> result = *this;
  result *= val;
  return result;
}

template <class T>
MVector<T> Matrix<T>::operator*(const MVector<T>& vec) const {
  if (_columns != vec.size()) {
    throw std::logic_error("Matrix columns must match "
      "vector size for multiplication");
  }

  MVector<T> result(_lines);

  for (size_t i = 0; i < _lines; i++) {
    result[i] = (*this)[i] * vec;
  }

  return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
  if (_columns != other._lines) {
    throw std::logic_error("Matrix dimensions "
      "must be compatible for multiplication");
  }

  Matrix<T> result(_lines, other._columns);

  for (size_t i = 0; i < _lines; i++) {
    for (size_t j = 0; j < other._columns; j++) {
      result[i][j] = (*this)[i] * other.get_column(j);
    }
  }
  return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
  if (this != &other) {
    _lines = other._lines;
    _columns = other._columns;

    MVector<MVector<T>>::operator=(other);
  }
  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const MVector<T>& vec) {
  _lines = vec.size();
  _columns = 1;

  MVector<MVector<T>>::operator=(MVector<MVector<T>>(vec.size()));

  for (size_t i = 0; i < _lines; i++) {
    (*this)[i] = MVector<T>(1);
    (*this)[i][0] = vec[i];
  }

  return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(T val) {
  _lines = 1;
  _columns = 1;

  MVector<MVector<T>>::operator=(MVector<MVector<T>>(1));

  (*this)[0] = MVector<T>(1);
  (*this)[0][0] = val;

  return *this;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
  if (_lines != other._lines || _columns != other._columns) {
    return false;
  }

  for (size_t i = 0; i < _lines; i++) {
    if ((*this)[i] != other[i]) {
      return false;
    }
  }
  return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
  return !((*this) == other);
}

template <class T>
MVector<T> Matrix<T>::get_column(size_t column_index) const {
  if (column_index >= _columns) {
    throw std::out_of_range("Column index out of range");
  }

  MVector<T> column(_lines);

  for (size_t i = 0; i < _lines; i++) {
    column[i] = (*this)[i][column_index];
  }

  return column;
}

#endif  // LIB_MATRIX_MATRIX_H_
