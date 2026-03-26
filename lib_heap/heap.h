// Copyright 2026 Smirnov Nikita

#ifndef LIB_HEAP_HEAP_H_
#define LIB_HEAP_HEAP_H_

#include<iostream>
#include<stdexcept>

#include "../lib_tvector/tvector.h"

template <class T>
class Heap {
  TVector<T> _data;

 public:
  Heap() = default;
  ~Heap() = default;

  size_t get_parent(size_t pos) {
    if (pos == 0) {
      return 0;
    }
    return (pos - 1) / 2;
  }
  size_t get_right(size_t pos) { return 2 * pos + 2; }
  size_t get_left(size_t pos) { return 2 * pos + 1; }

  void insert(const T& val);
  T pop();

  TVector<T> sort();

  void print();

 private:
  void siftup(size_t pos);
  void siftdown(size_t pos);
};

template <class T>
void Heap<T>::insert(const T& val) {
  _data.push_back(val);

  if (_data.size() > 1) {
    siftup(_data.size() - 1);
  }
}

template <class T>
T Heap<T>::pop() {
  if (_data.is_empty()) throw std::runtime_error("Heap is empty!");

  T root = _data[0];

  _data[0] = _data[_data.size() - 1];
  _data.pop_back();

  if (!_data.is_empty()) {
    siftdown(0);
  }

  return root;
}

template <class T>
TVector<T> Heap<T>::sort() {
  TVector<T> sorted_data;

  while (!_data.is_empty()) {
    sorted_data.push_back(this->pop());
  }

  return sorted_data;
}

template <class T>
void Heap<T>::siftup(size_t pos) {
  while (pos > 0) {
    size_t parent = get_parent(pos);

    if (_data[pos] < _data[parent]) {
      T_swap(_data[parent], _data[pos]);
      pos = parent;
    } else {
      break;
    }
  }
}

template <class T>
void Heap<T>::siftdown(size_t pos) {
  while (true) {
    size_t left = get_left(pos);
    size_t right = get_right(pos);
    size_t smallest = pos;

    if (left < _data.size() && _data[left] < _data[smallest]) {
      smallest = left;
    }

    if (right < _data.size() && _data[right] < _data[smallest]) {
      smallest = right;
    }

    if (smallest != pos) {
      T_swap(_data[smallest], _data[pos]);
      pos = smallest;
    } else {
      break;
    }
  }
}

template <class T>
void Heap<T>::print() {
  if (_data.is_empty()) return;
  for (size_t i = 0; i < _data.size() - 1; i++) {
    std::cout << _data[i] << " ";
  }

  std::cout << _data[_data.size() - 1];
}

#endif  // LIB_HEAP_HEAP_H_
