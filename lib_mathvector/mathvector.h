// Copyright 2025 Smirnov Nikita

#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#include<stdexcept>
#include "../lib_tvector/tvector.h"

template <class T>
class MVector : public TVector<T> {
  size_t _start_index = 0;

 public:
  MVector(size_t size, size_t start_index);
  explicit MVector(size_t size = 0);
  MVector(std::initializer_list<T>);
  MVector(const MVector<T>& other);
  ~MVector();

  inline size_t start_index() const noexcept;

  const T& operator[](size_t index) const;
  T& operator[](size_t index);

  inline T& at(size_t index);

  MVector<T>& operator+=(const MVector<T>& vec);
  MVector<T>& operator-=(const MVector<T>& vec);
  MVector<T>& operator*=(T val);
  MVector<T> operator+(MVector<T> vec);
  MVector<T> operator-(MVector<T> vec);
  MVector<T> operator*(T val);
  T operator*(MVector<T> vec);
};

template <class T>
MVector<T>::MVector(size_t size, size_t start_index)
  : TVector<T>(size), _start_index(start_index) {}

template <class T>
MVector<T>::MVector(size_t size) : TVector<T>(size) {}

template <class T>
MVector<T>::MVector(std::initializer_list<T> initList) : TVector<T>(initList) {}

template <class T>
MVector<T>::MVector(const MVector<T>& other)
  : TVector<T>(other), _start_index(other._start_index) {}

template <class T>
MVector<T>::~MVector() = default;

template <class T>
inline size_t MVector<T>::start_index() const noexcept {
  return _start_index;
}

template <class T>
const T& MVector<T>::operator[](size_t index) const {
  if (index < _start_index) {
    static const T zero = T();
    return zero;
  }
  return TVector<T>::operator[](index - _start_index);
}

template <class T>
T& MVector<T>::operator[](size_t index) {
  if (index < _start_index) {
    static T zero = T();
    return zero;
  }
  return TVector<T>::operator[](index - _start_index);
}

template <class T>
inline T& MVector<T>::at(size_t index) {
  if (index >= _start_index + this->size()) {
    throw std::out_of_range("Index out of range in at()");
  }
  if (index < _start_index) {
    static T zero = T();
    return zero;
  }

  return TVector<T>::at(index - _start_index);
}

template <class T>
MVector<T>& MVector<T>::operator+=(const MVector<T>& vec) {
  if (this->size() != vec.size()) {
    throw std::logic_error
    ("Size error: vectors have different sizes in the addition operation!");
  }
  for (size_t i = 0; i < vec.size(); i++) {
    (*this)[i] += vec[i];
  }

  return *this;
}

template <class T>
MVector<T>& MVector<T>::operator-=(const MVector<T>& vec) {
  if (this->size() != vec.size()) {
    throw std::logic_error
    ("Size error: vectors have different sizes in the subtraction operation!");
  }

  for (size_t i = 0; i < vec.size(); i++) {
    (*this)[i] -= vec[i];
  }

  return *this;
}

template <class T>
MVector<T>& MVector<T>::operator*=(T val) {
  for (size_t i = 0; i < (*this).size(); i++) {
    (*this)[i] *= val;
  }
  return *this;
}

template <class T>
MVector<T> MVector<T>::operator+(MVector<T> vec) {
  MVector<T> result = *this;
  result += vec;
  return result;
}

template <class T>
MVector<T> MVector<T>::operator-(MVector<T> vec) {
  MVector<T> result = *this;
  result -= vec;
  return result;
}

template <class T>
MVector<T> MVector<T>::operator*(T val) {
  MVector<T> result = *this;
  result *= val;
  return result;
}

template <class T>
T MVector<T>::operator*(MVector<T> vec) {
  if (this->size() != vec.size()) {
    throw std::logic_error
    ("Size error: vectors have different sizes "
      "in the multiplication operation!");
  }

  T result = T();

  for (size_t i = 0; i < vec.size(); i++) {
    result += (*this)[i] * vec[i];
  }

  return result;
}

#endif  // LIB_MATHVECTOR_MATHVECTOR_H_
