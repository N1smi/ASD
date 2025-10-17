// Copyright 2025 Smirnov Nikita

#ifndef LIB_TDYNAMIC_STACK_TDYNAMIC_STACK_H_
#define LIB_TDYNAMIC_STACK_TDYNAMIC_STACK_H_

#include <stdexcept>

template <class T>
class TDynamicStack {
  T* _data;
  size_t _size;
  size_t _top;

 public:
  explicit TDynamicStack(size_t size);

  TDynamicStack(const TDynamicStack<T>& other);

  ~TDynamicStack();

  inline T top() const;
  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
  inline size_t size() const noexcept;

  void push(const T& val);
  void pop();

  void clear() noexcept;
};

template<class T>
TDynamicStack<T>::TDynamicStack(size_t size) : _size(size), _top(0) {
  _data = new T[size];
}

template<class T>
TDynamicStack<T>::TDynamicStack(const TDynamicStack<T>& other)
  : _size(other._size), _top(other._top) {
  _data = new T[_size];

  for (size_t i = 0; i < _top; i++) {
    _data[i] = other._data[i];
  }
}

template<class T>
TDynamicStack<T>::~TDynamicStack() {
  delete[] _data;
}

template<class T>
inline size_t TDynamicStack<T>::size() const noexcept {
  return _size;
}

template<class T>
inline T TDynamicStack<T>::top() const {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  return _data[_top - 1];
}

template<class T>
inline bool TDynamicStack<T>::is_empty() const noexcept {
  return _top == 0;
}

template<class T>
inline bool TDynamicStack<T>::is_full() const noexcept {
  return _top == _size;
}

template<class T>
void TDynamicStack<T>::push(const T& val) {
  if (is_full()) throw std::logic_error("Stack is full!");

  ++_top;

  _data[_top - 1] = val;
}

template<class T>
void TDynamicStack<T>::pop() {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  --_top;
}

template<class T>
void TDynamicStack<T>::clear() noexcept {
  _top = 0;
}

#endif  // LIB_TDYNAMIC_STACK_TDYNAMIC_STACK_H_
