// Copyright 2025 Smirnov Nikita

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include "../lib_tvector/tvector.h"

template <class T>
class Stack {
  TVector<T> _data;
  size_t _capacity;
  size_t _size;

 public:
  explicit Stack(size_t capacity = 0);
  Stack(const Stack<T>& other);

  ~Stack() = default;

  inline T top() const;
  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
  inline size_t capacity() const noexcept;
  inline size_t size() const noexcept;

  void push(T val);
  void pop();

  void clear() noexcept;
};

template<class T>
Stack<T>::Stack(size_t capacity) : _data(), _size(0), _capacity(capacity) {
  _data.reserve(capacity);
}

template<class T>
Stack<T>::Stack(const Stack<T>& other) : _data(other._data),
_size(other._size), _capacity(other._capacity) {}

template<class T>
inline T Stack<T>::top() const {
  if (is_empty()) throw std::logic_error("You can't get"
    "a top from an empty stack");

  return _data.back();
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
  return _data.is_empty();
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
  return _data.is_full();
}

template<class T>
inline size_t Stack<T>::capacity() const noexcept {
  return _capacity;
}

template<class T>
inline size_t Stack<T>::size() const noexcept {
  return _size;
}

template<class T>
void Stack<T>::push(T val) {
  if (is_full()) throw std::logic_error("You can't push"
    "an item to the filled stack");
  _data.push_back(val);
  _size++;
}

template<class T>
void Stack<T>::pop() {
  if (is_empty()) throw std::logic_error("You can't pop"
    "in empty stack");
  _data.pop_back();
  _size--;
}

template<class T>
void Stack<T>::clear() noexcept {
  _data.clear();
  _size = 0;
}

#endif  // LIB_STACK_STACK_H_
