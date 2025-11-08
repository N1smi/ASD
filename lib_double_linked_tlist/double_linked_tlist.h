// Copyright 2025 Smirnov Nikita

#ifndef LIB_DOUBLE_LINKED_TLIST_DOUBLE_LINKED_TLIST_H_
#define LIB_DOUBLE_LINKED_TLIST_DOUBLE_LINKED_TLIST_H_

#include <stdexcept>

template <class T>
class DoubleLinkedTList {
 public:
  struct Node {
    T value;
    Node* next;
    Node* prev;
    explicit Node(T value_, Node* next_ = nullptr, Node* prev_ = nullptr) :
      value(value_), next(next_), prev(prev_) {
    }
  };

 private:
  Node* _head;
  Node* _tail;
  size_t _size;

 public:
  DoubleLinkedTList();
  DoubleLinkedTList(const DoubleLinkedTList<T>& other);
  ~DoubleLinkedTList();

  inline Node* head() noexcept { return _head; }
  inline Node* tail() noexcept { return _tail; }
  inline const Node* head() const noexcept { return _head; }
  inline const Node* tail() const noexcept { return _tail; }

  inline bool is_empty() const noexcept { return _head == nullptr; }

  inline size_t size() const noexcept { return _size; }

  void push_front(const T& value) noexcept;
  void push_back(const T& value) noexcept;
  void insert(size_t pos, const T& value);
  void insert(Node* node, const T& value);

  void pop_front();
  void pop_back();
  void erase(size_t pos);
  void erase(Node* node);

  void clear() noexcept;

  DoubleLinkedTList<T>& operator=(const DoubleLinkedTList<T>& other);

 private:
  Node* find_node(Node* target) const {
     if (target == nullptr) return nullptr;

     Node* current = _head;
     while (current != nullptr) {
       if (current == target) {
         return current;
       }
       current = current->next;
     }
     return nullptr;
  }
};

template <class T>
DoubleLinkedTList<T>::DoubleLinkedTList() : _head(nullptr),
_tail(nullptr), _size(0) {}

template <class T>
DoubleLinkedTList<T>::DoubleLinkedTList(const DoubleLinkedTList<T>& other)
  : _head(nullptr),
_tail(nullptr), _size(0) {
  Node* current = other._head;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }
}

template <class T>
DoubleLinkedTList<T>::~DoubleLinkedTList() {
  while (_head) {
    Node* temp = _head;
    _head = _head->next;
    delete temp;
  }
}

template <class T>
void DoubleLinkedTList<T>::push_front(const T& value) noexcept {
  Node* node = new Node(value);
  if (is_empty()) {
    _head = node;
    _tail = node;
    _size++;
    return;
  }
  _head->prev = node;
  node->next = _head;
  _head = node;
  _size++;
}

template <class T>
void DoubleLinkedTList<T>::push_back(const T& value) noexcept {
  Node* node = new Node(value);
  if (is_empty()) {
    _head = node;
    _tail = node;
    _size++;
    return;
  }
  _tail->next = node;
  node->prev = _tail;
  _tail = node;
  _size++;
}

template <class T>
void DoubleLinkedTList<T>::insert(Node* node, const T& value) {
  if (node == nullptr) {
    throw std::invalid_argument("Node cannot be null");
  }
  if (is_empty()) {
    throw std::logic_error("Cannot insert into empty list");
  }

  if (find_node(node) == nullptr) {
    throw std::invalid_argument("Node not found in list");
  }

  if (node == _tail) {
    push_back(value);
    return;
  }

  Node* new_node = new Node(value);
  new_node->next = node->next;
  node->next->prev = new_node;
  node->next = new_node;
  new_node->prev = node;
  _size++;
}

template <class T>
void DoubleLinkedTList<T>::insert(size_t pos, const T& value) {
  if (pos > _size) {
    throw std::out_of_range("Position out of range");
  }
  if (pos == 0) {
    push_front(value);
    return;
  }
  if (pos == _size) {
    push_back(value);
    return;
  }

  Node* current = _head;
  for (size_t i = 0; i < pos - 1; i++) {
    current = current->next;
  }

  insert(current, value);
}

template <class T>
void DoubleLinkedTList<T>::pop_front() {
  if (is_empty()) throw std::logic_error("Cannot pop_front from empty list");

  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    _size--;
    return;
  }

  Node* cur = _head;
  _head = _head->next;
  _head->prev = nullptr;

  delete cur;

  _size--;
}

template <class T>
void DoubleLinkedTList<T>::pop_back() {
  if (is_empty()) throw std::logic_error("Cannot pop_back from empty list");

  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    _size--;
    return;
  }

  Node* new_tail = _tail->prev;

  delete _tail;
  _tail = new_tail;
  _tail->next = nullptr;

  _size--;
}

template <class T>
void DoubleLinkedTList<T>::erase(Node* node) {
  if (node == nullptr) {
    throw std::invalid_argument("Node cannot be null");
  }

  if (is_empty()) {
    throw std::logic_error("Cannot erase from empty list");
  }

  if (find_node(node) == nullptr) {
    throw std::invalid_argument("Node not found in list");
  }

  if (node == _head) {
    pop_front();
    return;
  }

  if (node == _tail) {
    pop_back();
    return;
  }

  node->prev->next = node->next;
  node->next->prev = node->prev;

  delete node;
  _size--;
}

template <class T>
void DoubleLinkedTList<T>::erase(size_t pos) {
  if (pos >= _size) {
    throw std::out_of_range("Position out of range");
  }

  if (pos == 0) {
    pop_front();
    return;
  }

  if (pos == _size - 1) {
    pop_back();
    return;
  }

  Node* current = _head;
  for (size_t i = 0; i < pos; ++i) {
    current = current->next;
  }

  erase(current);
}

template <class T>
void DoubleLinkedTList<T>::clear() noexcept {
  while (_head != nullptr) {
    Node* temp = _head;
    _head = _head->next;
    delete temp;
  }
  _tail = nullptr;
  _size = 0;
}

template <class T>
DoubleLinkedTList<T>& DoubleLinkedTList<T>::operator=
(const DoubleLinkedTList<T>& other) {
  if (this == &other) {
    return *this;
  }

  clear();

  Node* current = other._head;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }

  return *this;
}

#endif  // LIB_DOUBLE_LINKED_TLIST_DOUBLE_LINKED_TLIST_H_
