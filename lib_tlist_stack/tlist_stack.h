// Copyright 2025 Smirnov Nikita

#ifndef LIB_TLIST_STACK_TLIST_STACK_H_
#define LIB_TLIST_STACK_TLIST_STACK_H_

#include <stdexcept>
#include "../lib_tlist/tlist.h"

template<class T>
class TListStack {
  TList<T> _data;
  size_t _max_size;

 public:
  explicit TListStack(size_t max_size = -1) : _max_size(max_size) {}
  TListStack(const TListStack<T>& other) = default;

  inline T top() const;
  bool is_empty() const noexcept { return _data.is_empty(); }
  bool is_full() const noexcept { return _max_size == _data.size(); }
  size_t size() const noexcept { return _data.size(); }

  void push(const T& val);
  void pop();

  void clear() noexcept { _data.clear(); }
};

template<class T>
inline T TListStack<T>::top() const {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  return _data.head()->value;
}

template<class T>
void TListStack<T>::pop() {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  _data.pop_front();
}

template<class T>
void TListStack<T>::push(const T& val) {
  if (is_full()) throw std::logic_error("Stack is full!");
  _data.push_front(val);
}

#endif  // LIB_TLIST_STACK_TLIST_STACK_H_
