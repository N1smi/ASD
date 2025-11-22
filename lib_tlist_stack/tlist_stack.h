// Copyright 2025 Smirnov Nikita

#ifndef LIB_TLIST_STACK_TLIST_STACK_H_
#define LIB_TLIST_STACK_TLIST_STACK_H_

#include <stdexcept>
#include "../lib_tlist/tlist.h"

template<class T>
class TListStack {
  TList<T> _data;

 public:
  TListStack() = default;
  TListStack(const TListStack<T>& other) = default;

  inline T top() const;
  bool is_empty() const noexcept { return _data.is_empty(); }
  size_t size() const noexcept { return _data.size(); }

  void push(const T& val) { _data.push_back(val); }
  void pop();

  void clear() noexcept { _data.clear(); }
};

template<class T>
inline T TListStack<T>::top() const {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  return _data.tail()->value;
}

template<class T>
void TListStack<T>::pop() {
  if (is_empty()) throw std::logic_error("Stack is empty!");

  _data.pop_back();
}

#endif  // LIB_TLIST_STACK_TLIST_STACK_H_
