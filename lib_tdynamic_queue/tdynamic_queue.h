// Copyright 2025 Smirnov Nikita

#ifndef LIB_TDYNAMIC_QUEUE_TDYNAMIC_QUEUE_H_
#define LIB_TDYNAMIC_QUEUE_TDYNAMIC_QUEUE_H_

#include <stdexcept>

template <class T>
class TDynamicQueue {
  T* _data;
  size_t _size;
  size_t _count;
  size_t _head;
  size_t _tail;

 public:
   explicit TDynamicQueue(size_t size);
   TDynamicQueue(const TDynamicQueue<T>& other);

   ~TDynamicQueue();

   inline T head() const;
   inline T tail() const;
   inline bool is_empty() const noexcept;
   inline bool is_full() const noexcept;
   inline size_t size() const noexcept;

   void push(const T& val);
   void pop();

   void clear() noexcept;
};

template <class T>
TDynamicQueue<T>::TDynamicQueue(size_t size) : _size(size),
_head(0), _tail(0), _count(0) {
  _data = new T[_size];
}

template <class T>
TDynamicQueue<T>::TDynamicQueue(const TDynamicQueue<T>& other)
  : _size(other._size), _head(other._head),
  _tail(other._tail), _count(other._count) {
  _data = new T[_size];

  for (size_t i = 0; i < _size; i++) {
    _data[i] = other._data[i];
  }
}

template <class T>
TDynamicQueue<T>::~TDynamicQueue() {
  delete[] _data;
}

template <class T>
inline T TDynamicQueue<T>::head() const {
  if (is_empty()) throw std::underflow_error("Queue is empty!");

  return _data[_head];
}

template <class T>
inline T TDynamicQueue<T>::tail() const {
  if (is_empty()) throw std::underflow_error("Queue is empty!");

  return _data[(_tail + _size - 1) % _size];
}

template <class T>
inline bool TDynamicQueue<T>::is_empty() const noexcept {
  return _count == 0;
}

template <class T>
inline bool TDynamicQueue<T>::is_full() const noexcept {
  return _count == _size;
}

template <class T>
inline size_t TDynamicQueue<T>::size() const noexcept {
  return _size;
}

template <class T>
void TDynamicQueue<T>::push(const T& val) {
  if (is_full()) throw std::overflow_error("Queue is full!");
  _data[_tail] = val;
  _tail = (_tail + 1) % _size;
  _count++;
}

template <class T>
void TDynamicQueue<T>::pop() {
  if (is_empty()) throw std::underflow_error("Queue is empty!");
  _head = (_head + 1) % _size;
  _count--;
}

template <class T>
void TDynamicQueue<T>::clear() noexcept {
  _head = 0;
  _tail = 0;
  _count = 0;
}

#endif  // LIB_TDYNAMIC_QUEUE_TDYNAMIC_QUEUE_H_
