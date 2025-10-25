// Copyright 2025 Smirnov Nikita

#ifndef LIB_TLIST_TLIST_H_
#define LIB_TLIST_TLIST_H_

#include <stdexcept>

template <class T>
struct Node {
  T value;
  Node<T>* next;
  explicit Node(T value_, Node<T>* next_ = nullptr) : value(value_),
    next(next_) {}
};

template <class T>
class TList {
  Node<T>* _head;
  Node<T>* _tail;
  size_t _size;

 public:
  TList();
  TList(const TList<T>& other);
  ~TList();

  inline Node<T>* head() noexcept { return _head; }
  inline Node<T>* tail() noexcept { return _tail; }
  inline const Node<T>* head() const noexcept { return _head; }
  inline const Node<T>* tail() const noexcept { return _tail; }

  inline bool is_empty() const noexcept { return _head == nullptr; }

  inline size_t size() const noexcept { return _size; }

  void push_front(const T& value) noexcept;
  void push_back(const T& value) noexcept;
  void insert(size_t pos, const T& value);
  void insert(Node<T>* node, const T& value);

  void pop_front();
  void pop_back();
  void erase(size_t pos);
  void erase(Node<T>* node);

 private:
  Node<T>* find_previous_node(Node<T>* node) const;
};

template <class T>
TList<T>::TList() : _head(nullptr), _tail(nullptr), _size(0) {}

template <class T>
TList<T>::TList(const TList<T>& other) : _head(nullptr),
_tail(nullptr), _size(0) {
  Node<T>* current = other._head;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }
}

template <class T>
TList<T>::~TList() {
  while (_head) {
    Node<T>* temp = _head;
    _head = _head->next;
    delete temp;
  }
}

template <class T>
void TList<T>::push_front(const T& value) noexcept {
  Node<T>* node = new Node<T>(value);
  if (is_empty()) {
    _head = node;
    _tail = node;
    _size++;
    return;
  }
  node->next = _head;
  _head = node;
  _size++;
}

template <class T>
void TList<T>::push_back(const T& value) noexcept {
  Node<T>* node = new Node<T>(value);
  if (is_empty()) {
    _head = node;
    _tail = node;
    _size++;
    return;
  }
  _tail->next = node;
  _tail = node;
  _size++;
}

template <class T>
void TList<T>::insert(Node<T>* node, const T& value) {
  if (node == nullptr) {
    throw std::invalid_argument("Node cannot be null");
  }
  if (is_empty()) {
    throw std::logic_error("Cannot insert into empty list");
  }

  if (node != _head) {
    Node<T>* prev = find_previous_node(node);
    if (prev == nullptr) {
      throw std::invalid_argument("Node not found in list");
    }
  }

  Node<T>* new_node = new Node<T>(value);
  new_node->next = node->next;
  node->next = new_node;
  if (node == _tail) {
    _tail = new_node;
  }
  _size++;
}

template <class T>
void TList<T>::insert(size_t pos, const T& value) {
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

  Node<T>* current = _head;
  for (size_t i = 0; i < pos - 1; i++) {
    current = current->next;
  }

  insert(current, value);
}

template <class T>
void TList<T>::pop_front() {
  if (is_empty()) throw std::logic_error("Cannot pop_front from empty list");

  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    _size--;
    return;
  }

  Node<T>* cur = _head;
  _head = _head->next;

  if (_head == nullptr) {
    _tail = nullptr;
  }

  delete cur;

  _size--;
}

template <class T>
void TList<T>::pop_back() {
  if (is_empty()) throw std::logic_error("Cannot pop_back from empty list");

  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    _size--;
    return;
  }

  Node<T>* cur = _head;

  while (cur->next != _tail) {
    cur = cur->next;
  }

  delete _tail;
  _tail = cur;
  cur->next = nullptr;
  _size--;
}

template <class T>
void TList<T>::erase(Node<T>* node) {
  if (node == nullptr) {
    throw std::invalid_argument("Node cannot be null");
  }
  if (is_empty()) {
    throw std::logic_error("Cannot erase from empty list");
  }

  if (node == _head) {
    pop_front();
    return;
  }

  if (node == _tail) {
    pop_back();
    return;
  }

  Node<T>* current = find_previous_node(node);

  if (current == nullptr) {
    throw std::invalid_argument("Node not found in list");
  }

  current->next = node->next;
  delete node;
  _size--;
}

template <class T>
void TList<T>::erase(size_t pos) {
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

  Node<T>* current = _head;
  for (size_t i = 0; i < pos - 1; ++i) {
    current = current->next;
  }

  Node<T>* to_delete = current->next;
  current->next = to_delete->next;
  delete to_delete;
  _size--;
}

template <class T>
Node<T>* TList<T>::find_previous_node(Node<T>* node) const {
  if (node == nullptr || _head == nullptr) {
    return nullptr;
  }

  if (node == _head) {
    return nullptr;
  }

  Node<T>* current = _head;
  while (current != nullptr && current->next != node) {
    current = current->next;
  }

  return current;
}

#endif  // LIB_TLIST_TLIST_H_
