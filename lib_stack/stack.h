// Copyright 2025 Smirnov Nikita

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include "../lib_tvector/tvector.h"

template <class T>
class Stack {
  T* _data;
  size_t _size;
  size_t _top;

 public:
  explicit Stack(size_t size);

  Stack(const Stack<T>& other);

  ~Stack();

  inline T top() const;
  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
  inline size_t size() const noexcept;

  void push(T val);
  void pop();

  void clear() noexcept;

  Stack<T>& operator=(const Stack<T>& other);
};

template<class T>
Stack<T>::Stack(size_t size) : _size(size), _top(0) {
  _data = new T[size];
}

template<class T>
Stack<T>::Stack(const Stack<T>& other) : _size(other._size), _top(other._top) {
  _data = new T[_size];

  for (size_t i = 0; i < _top; i++) {
    _data[i] = other._data[i];
  }
}

template<class T>
Stack<T>::~Stack() {
  delete[] _data;
}

template<class T>
inline size_t Stack<T>::size() const noexcept {
  return _size;
}


template<class T>
inline T Stack<T>::top() const {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  return _data[_top - 1];
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
  return _top == 0;
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
  return _top == _size;
}


template<class T>
void Stack<T>::push(T val) {
  if (is_full()) throw std::logic_error("Stack is full!");

  ++_top;

  _data[_top - 1] = val;
}

template<class T>
void Stack<T>::pop() {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  --_top;
}

template<class T>
void Stack<T>::clear() noexcept {
  _top = 0;
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
  if (this == &other) {
    return *this;
  }

  delete[] _data;
  _size = other._size;
  _top = other._top;
  _data = new T[_size];

  for (size_t i = 0; i < _top; i++) {
    _data[i] = other._data[i];
  }

  return *this;
}

#endif  // LIB_STACK_STACK_H_
