// Copyright 2026 Smirnov Nikita

#ifndef LIB_TREE_TREE_H_
#define LIB_TREE_TREE_H_

#include <utility>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "../lib_tlist_queue/tlist_queue.h"

template <class TKey, class TValue>
class Tree {
  struct Node {
    std::pair<TKey, TValue> _data;
    Node* _left;
    Node* _right;

    explicit Node(const std::pair<TKey, TValue>& pair)
      : _data(pair), _left(nullptr), _right(nullptr) {}
  };

  Node* _root;

  template <typename ValueType>
  class IteratorBase {
   public:
    using NodeType = typename std::conditional<
      std::is_const<ValueType>::value,
      const Node,
      Node
    >::type;

    using Reference = typename std::conditional<
      std::is_const<ValueType>::value,
      const std::pair<TKey, TValue>&,
      std::pair<TKey, TValue>&
    >::type;

    using Pointer = typename std::conditional<
      std::is_const<ValueType>::value,
      const std::pair<TKey, TValue>*,
      std::pair<TKey, TValue>*
    >::type;

   private:
    TListQueue<NodeType*> _queue;
    NodeType* _current;

   public:
    explicit IteratorBase(NodeType* root) : _current(root) {
      if (_current) _queue.push(_current);
    }

    IteratorBase() = default;

    Reference operator*() const {
      return _current->_data;
    }

    Pointer operator->() const {
      return &(_current->_data);
    }

    IteratorBase& operator++() {
      if (_queue.is_empty()) {
        _current = nullptr;
        return *this;
      }

      Node* old_node = _queue.head();
      _queue.pop();

      if (old_node->_left) _queue.push(old_node->_left);
      if (old_node->_right) _queue.push(old_node->_right);

      if (_queue.is_empty()) {
        _current = nullptr;
      } else {
        _current = _queue.head();
      }

      return *this;
    }

    bool operator==(const IteratorBase& other) const {
      return _current == other._current;
    }

    bool operator!=(const IteratorBase& other) const {
      return !(*this == other);
    }
  };

 public:
  using iterator = IteratorBase<TValue>;
  using const_iterator = IteratorBase<const TValue>;

  Tree() : _root(nullptr) {}
  Tree(const Tree&) = delete;
  Tree& operator=(const Tree&) = delete;
  ~Tree() { clear(); }

  iterator begin() noexcept { return iterator(_root); }
  iterator end() noexcept { return iterator(); }
  const_iterator begin() const noexcept { return const_iterator(_root); }
  const_iterator end() const noexcept { return const_iterator(); }

  bool is_empty() const noexcept { return !_root; }

  void insert(const TKey& key, const TValue& value);
  void erase(const TKey& key);

  TValue* find(const TKey& key) noexcept;
  const TValue* find(const TKey& key) const noexcept;

  void clear() noexcept;

  void print_width() const noexcept;
  void print_DLCR() const noexcept;
  void print_DLRC() const noexcept;
  void print_DCLR() const noexcept;

 private:
  void print_DLCR_rec(Node* node) const noexcept;
  void print_DLRC_rec(Node* node) const noexcept;
  void print_DCLR_rec(Node* node) const noexcept;
  void clear_rec(Node* node);
};

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
  Node* new_node = new Node({ key, value });
  if (is_empty()) {
    _root = new_node;
    return;
  }

  Node* cur = nullptr;

  TListQueue<Node*> q;

  q.push(_root);

  while (true) {
    cur = q.head();
    q.pop();

    if (!cur->_left) {
      cur->_left = new_node;
      return;
    }

    if (!cur->_right) {
      cur->_right = new_node;
      return;
    }

    q.push(cur->_left);
    q.push(cur->_right);
  }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
  if (is_empty()) throw
    std::invalid_argument("You cannot delete element in empty tree!");

  Node* target_node = nullptr;
  Node* last_node = nullptr;
  Node* last_node_parent = nullptr;

  TListQueue<Node*> q;

  q.push(_root);

  while (!q.is_empty()) {
    last_node = q.head();
    q.pop();

    if (last_node->_data.first == key && !target_node) {
      target_node = last_node;
    }

    if (last_node->_left) {
      last_node_parent = last_node;
      q.push(last_node->_left);
    }

    if (last_node->_right) {
      last_node_parent = last_node;
      q.push(last_node->_right);
    }
  }

  if (!target_node) {
    throw std::invalid_argument("The element with this key does not exist!");
  }

  if (target_node != last_node) {
    target_node->_data = std::move(last_node->_data);
  }

  if (last_node_parent) {
    if (last_node_parent->_right == last_node) {
      last_node_parent->_right = nullptr;
    } else {
      last_node_parent->_left = nullptr;
    }

    delete last_node;
  } else {
    delete _root;
    _root = nullptr;
  }
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find(const TKey& key) noexcept {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TKey, class TValue>
const TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
  if (is_empty()) return nullptr;

  Node* cur = nullptr;

  TListQueue<Node*> q;
  q.push(_root);

  while (!q.is_empty()) {
    cur = q.head();
    q.pop();

    if (cur->_data.first == key) {
      return &cur->_data.second;
    }

    if (cur->_left) q.push(cur->_left);
    if (cur->_right) q.push(cur->_right);
  }

  return nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
  clear_rec(_root);
  _root = nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_width() const noexcept {
  if (is_empty()) return;

  TListQueue<Node*> q;

  Node* cur = nullptr;
  q.push(_root);

  while (!q.is_empty()) {
    cur = q.head();
    q.pop();

    std::cout << cur->_data.second << " ";

    if (cur->_left) q.push(cur->_left);
    if (cur->_right) q.push(cur->_right);
  }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR() const noexcept {
  print_DLCR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC() const noexcept {
  print_DLRC_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR() const noexcept {
  print_DCLR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(Node* node) {
  if (node) {
    clear_rec(node->_left);
    clear_rec(node->_right);
    delete node;
  }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR_rec(Node* node) const noexcept {
  if (!node) return;

  print_DLCR_rec(node->_left);
  std::cout << node->_data.second << " ";
  print_DLCR_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC_rec(Node* node) const noexcept {
  if (!node) return;

  print_DLRC_rec(node->_left);
  print_DLRC_rec(node->_right);
  std::cout << node->_data.second << " ";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR_rec(Node* node) const noexcept {
  if (!node) return;

  std::cout << node->_data.second << " ";
  print_DCLR_rec(node->_left);
  print_DCLR_rec(node->_right);
}

#endif  // LIB_TREE_TREE_H_
