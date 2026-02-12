// Copyright 2025 Smirnov Nikita

#ifndef LIB_TLIST_QUEUE_TLIST_QUEUE_H_
#define LIB_TLIST_QUEUE_TLIST_QUEUE_H_

#include <stdexcept>
#include "../lib_tlist/tlist.h"

template<class T>
class TListQueue {
  TList<T> _data;
  size_t _max_size;

 public:
  explicit TListQueue(size_t max_size = -1) : _max_size(max_size) {}
  TListQueue(const TListQueue<T>& other) = default;

  inline T head() const;
  inline T tail() const;
  bool is_empty() const noexcept { return _data.is_empty(); }
  bool is_full() const noexcept { return _max_size == _data.size(); }
  size_t size() const noexcept { return _data.size(); }

  void push(const T& val);
  void pop();

  void clear() noexcept { _data.clear(); }
};

template<class T>
inline T TListQueue<T>::head() const {
  if (is_empty()) throw std::underflow_error("Queue is empty!");

  return _data.head()->value;
}

template<class T>
inline T TListQueue<T>::tail() const {
  if (is_empty()) throw std::underflow_error("Queue is empty!");

  return _data.tail()->value;
}

template<class T>
void TListQueue<T>::pop() {
  if (is_empty()) throw std::underflow_error("Queue is empty!");

  _data.pop_front();
}

template<class T>
void TListQueue<T>::push(const T& val) {
  if (is_full()) throw std::logic_error("Queue is full!");
  _data.push_back(val);
}

#endif  // LIB_TLIST_QUEUE_TLIST_QUEUE_H_
