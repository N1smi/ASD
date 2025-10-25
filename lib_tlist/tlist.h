// Copyright 2025 Smirnov Nikita

#ifndef LIB_TLIST_TLIST_H_
#define LIB_TLIST_TLIST_H_

#include <stdexcept>

template <class T>
struct Node {
  T value;
  Node<T>* next;
  Node(T value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
};

template <class T>
class TList {
  Node<T>* _head;
  Node<T>* _tail;

 public:
   TList();

   ~TList();

   inline Node<T>* head() noexcept { return _head; }
   inline Node<T>* tail() noexcept { return _tail; }
   inline const Node<T>* head() const noexcept { return _head; }
   inline const Node<T>* tail() const noexcept { return _tail; }

   inline bool is_empty() const noexcept { return _head == nullptr; }
};

template <class T>
TList<T>::TList() : _head(nullptr), _tail(nullptr) {}

template <class T>
TList<T>::~TList() {
  while (_head) {
    Node<T>* temp = _head;
    _head = _head->next;
    delete temp;
  }
}

#endif  // LIB_TLIST_TLIST_H_
