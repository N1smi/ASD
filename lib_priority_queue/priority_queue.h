// Copyright 2026 Smirnov Nikita

#ifndef LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#include "../lib_heap/heap.h"

template <class T>
class PriorityQueue {
  struct QueueElement {
    size_t _id;
    size_t _priority;
    T _value;

    bool operator<(const QueueElement& other) const {
      if (_priority == other._priority) {
        return _id < other._id;
      }

      return _priority > other._priority;
    }

    bool operator>(const QueueElement& other) const {
      if (_priority == other._priority) {
        return _id > other._id;
      }

      return _priority < other._priority;
    }

    bool operator==(const QueueElement& other) const {
      return _priority == other._priority && _value == other._value;
    }
  };
  Heap<QueueElement> _data;
  size_t _cur_id;

 public:
   PriorityQueue() : _cur_id(0), _data() {}
   ~PriorityQueue() = default;

   inline const T& top() { return _data.top()._value; }
   void push(size_t priority, const T& val);

   void pop();
};

template <class T>
void PriorityQueue<T>::push(size_t priority, const T& val) {
  _data.insert({ _cur_id, priority, val });
  _cur_id++;
}

template <class T>
void PriorityQueue<T>::pop() {
  _data.pop();
}

#endif  // LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_