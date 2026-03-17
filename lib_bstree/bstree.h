// Copyright 2026 Smirnov Nikita

#ifndef LIB_BSTREE_BSTREE_H_
#define LIB_BSTREE_BSTREE_H_

#include<utility>
#include<stdexcept>
#include<iostream>

template <class TKey, class TValue>
class BSTree {
 private:
  struct Node {
    std::pair<TKey, TValue> _data;
    Node* _left;
    Node* _right;

    explicit Node(const std::pair<TKey, TValue>& value_)
      : _data(value_), _left(nullptr), _right(nullptr) {}
  };

 private:
  Node* _root;

 public:
  BSTree();
  BSTree(const BSTree&) = delete;
  BSTree& operator=(const BSTree&) = delete;

  ~BSTree();

  bool is_empty() const noexcept { return _root == nullptr; }

  TValue* find(const TKey& key) noexcept;
  const TValue* find(const TKey& key) const noexcept;
  void insert(const TKey& key, const TValue& val);
  void erase(const TKey& key);

  void print() const;

 private:
  void clear(Node* node);
  Node* find_parent(const TKey& key) const noexcept;
  void print_DLCR_rec(Node* node) const;
  Node* find_max_left(Node* node) const noexcept;
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree() : _root(nullptr) {}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() {
  clear(_root);
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) noexcept {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TKey, class TValue>
const TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
  if (is_empty()) return nullptr;

  if (_root->_data.first == key) {
    return &_root->_data.second;
  }

  Node* parent = find_parent(key);

  if (!parent) return nullptr;

  if (parent->_left && parent->_left->_data.first == key) {
    return &parent->_left->_data.second;
  }

  if (parent->_right && parent->_right->_data.first == key) {
    return &parent->_right->_data.second;
  }

  return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
  if (is_empty()) {
    _root = new Node({ key, val });
    return;
  }

  Node* cur = _root;
  Node* parent = nullptr;

  while (cur) {
    parent = cur;

    if (cur->_data.first > key) {
      cur = cur->_left;
    } else if (cur->_data.first < key) {
      cur = cur->_right;
    } else {
      throw std::invalid_argument("The element with the inserted "
        "key already exists!");
    }
  }

  if (parent->_data.first > key) {
    parent->_left = new Node({ key, val });
  } else {
    parent->_right = new Node({ key, val });
  }
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
  if (is_empty()) throw
    std::invalid_argument("You cannot delete element in empty tree!");

  Node** targetPtr = &_root;

  if (_root->_data.first != key) {
    Node* parent = find_parent(key);

    if (!parent) {
      throw std::invalid_argument("The element with this key does not exist!");
    }

    targetPtr = (parent->_left && parent->_left->_data.first == key) ? &parent->_left
      : &parent->_right;
  }

  Node* toDelete = *targetPtr;

  if (!toDelete->_left) {
    *targetPtr = toDelete->_right;
    delete toDelete;
  } else if (!toDelete->_right) {
    *targetPtr = toDelete->_left;
    delete toDelete;
  } else {
    Node* successor = find_max_left(toDelete->_left);

    TKey sKey = successor->_data.first;
    TValue sValue = successor->_data.second;

    erase(sKey);

    const_cast<TKey&>(toDelete->_data.first) = sKey;
    toDelete->_data.second = sValue;
  }
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print() const {
  print_DLCR_rec(_root);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear(Node* node) {
  if (node) {
    clear(node->_left);
    clear(node->_right);
    delete node;
  }
}

template <class TKey, class TValue>
typename BSTree<TKey, TValue>::Node*
BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
  if (is_empty() || _root->_data.first == key) return nullptr;

  Node* cur = _root;

  while (cur) {
    if (cur->_left && cur->_left->_data.first == key) return cur;
    if (cur->_right && cur->_right->_data.first == key) return cur;

    if (cur->_data.first > key) cur = cur->_left;
    else cur = cur->_right;
  }

  return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR_rec(Node* node) const {
  if (node == nullptr) return;

  print_DLCR_rec(node->_left);

  std::cout << "[key: " << node->_data.first << ", val: "
    << node->_data.second << "]";

  print_DLCR_rec(node->_right);
}

template <class TKey, class TValue>
typename BSTree<TKey, TValue>::Node*
BSTree<TKey, TValue>::find_max_left(Node* node) const noexcept {
  if (!node) return nullptr;

  while (node->_right) {
    node = node->_right;
  }

  return node;
}

#endif  // LIB_BSTREE_BSTREE_H_
