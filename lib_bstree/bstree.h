// Copyright 2026 Smirnov Nikita

#ifndef LIB_BSTREE_BSTREE_H_
#define LIB_BSTREE_BSTREE_H_

#include<utility>
#include<stack>
#include<stdexcept>
#include<iostream>

template <typename TKey, typename TValue>
struct BSTNode {
  std::pair<TKey, TValue> _data;
  BSTNode* _left = nullptr;
  BSTNode* _right = nullptr;

  explicit BSTNode(const std::pair<TKey, TValue>& val) : _data(val) {}
  virtual ~BSTNode() = default;
};

template <class TKey, class TValue, class Node = BSTNode<TKey, TValue>>
class BSTree {
 protected:
  Node* _root;

  Node* createNode(const TKey& key, const TValue& val) {
    return new Node({ key, val });
  }

  virtual void setupParent(Node* child, Node* parent) {}

 private:
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
    std::stack<NodeType*> _stack;

    void push_left(NodeType* node) {
      while (node) {
        _stack.push(node);
        node = static_cast<NodeType*>(node->_left);
      }
    }

   public:
    explicit IteratorBase(NodeType* root) {
      push_left(root);
    }

    IteratorBase() = default;

    Reference operator*() const {
      return _stack.top()->_data;
    }

    Pointer operator->() const {
      return &(_stack.top()->_data);
    }

    IteratorBase& operator++() {
      if (_stack.empty()) return *this;
      NodeType* node = _stack.top();
      _stack.pop();

      if (node->_right) {
        push_left(node->_right);
      }

      return *this;
    }

    bool operator==(const IteratorBase& other) const {
      if (_stack.empty() || other._stack.empty()) {
        return _stack.empty() == other._stack.empty();
      }
      return _stack.top() == other._stack.top();
    }

    bool operator!=(const IteratorBase& other) const {
      return !(*this == other);
    }
  };

 public:
  using iterator = IteratorBase<TValue>;
  using const_iterator = IteratorBase<const TValue>;

  BSTree();
  BSTree(const BSTree&) = delete;
  BSTree& operator=(const BSTree&) = delete;

  ~BSTree();

  iterator begin() noexcept { return iterator(_root); }
  iterator end() noexcept { return iterator(); }
  const_iterator begin() const noexcept { return const_iterator(_root); }

  const_iterator end() const noexcept { return const_iterator(); }

  bool is_empty() const noexcept { return _root == nullptr; }

  TValue* find(const TKey& key) noexcept;
  const TValue* find(const TKey& key) const noexcept;
  Node* insert(const TKey& key, const TValue& val);
  Node* erase(const TKey& key);

  void print() const;

 private:
  void clear(Node* node);
  Node* find_parent(const TKey& key) const noexcept;
  void print_DLCR_rec(Node* node) const;
  Node* find_max_left(Node* node) const noexcept;
};

template <class TKey, class TValue, class Node>
BSTree<TKey, TValue, Node>::BSTree() : _root(nullptr) {}

template <class TKey, class TValue, class Node>
BSTree<TKey, TValue, Node>::~BSTree() {
  clear(_root);
}

template <class TKey, class TValue, class Node>
TValue* BSTree<TKey, TValue, Node>::find(const TKey& key) noexcept {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TKey, class TValue, class Node>
const TValue* BSTree<TKey, TValue, Node>::find(const TKey& key) const noexcept {
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

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::insert(const TKey& key, const TValue& val) {
  if (is_empty()) return _root = createNode(key, val);

  Node* cur = _root;
  Node* parent = nullptr;

  while (cur) {
    parent = cur;

    if (cur->_data.first > key) {
      cur = static_cast<Node*>(cur->_left);
    } else if (cur->_data.first < key) {
      cur = static_cast<Node*>(cur->_right);
    } else {
      throw std::invalid_argument("The element with the inserted "
        "key already exists!");
    }
  }

  Node* newNode = createNode(key, val);
  if (parent->_data.first > key) {
    parent->_left = newNode;
  } else {
    parent->_right = newNode;
  }

  setupParent(newNode, parent);

  return newNode;
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::erase(const TKey& key) {
  if (is_empty()) throw
    std::invalid_argument("You cannot delete element in empty tree!");

  Node** targetPtr = &_root;
  Node* parent = nullptr;

  if (_root->_data.first != key) {
    parent = find_parent(key);

    if (!parent) {
      throw std::invalid_argument("The element with this key does not exist!");
    }

    targetPtr = (parent->_left && parent->_left->_data.first == key)
      ? &parent->_left : &parent->_right;
  }

  Node* toDelete = *targetPtr;

  if (!toDelete->_left || !toDelete->_right) {
    Node* child = toDelete->_left ? toDelete->_left : toDelete->_right;
    *targetPtr = child;

    if (child) {
      setupParent(child, parent);
    }

    delete toDelete;
    return parent;
  } else {
    Node* successor = find_max_left(toDelete->_left);

    TKey sKey = successor->_data.first;
    TValue sValue = successor->_data.second;

    Node* balanceStart = erase(sKey);

    toDelete->_data.first = sKey;
    toDelete->_data.second = sValue;

    return balanceStart;
  }
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print() const {
  print_DLCR_rec(_root);
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::clear(Node* node) {
  if (node) {
    clear(static_cast<Node*>(node->_left));
    clear(static_cast<Node*>(node->_right));
    delete node;
  }
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::find_parent(const TKey& key) const noexcept {
  if (is_empty() || _root->_data.first == key) return nullptr;

  Node* cur = _root;

  while (cur) {
    if (cur->_left && cur->_left->_data.first == key) return cur;
    if (cur->_right && cur->_right->_data.first == key) return cur;

    if (cur->_data.first > key) cur = static_cast<Node*>(cur->_left);
    else cur = static_cast<Node*>(cur->_right);
  }

  return nullptr;
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_DLCR_rec(Node* node) const {
  if (node == nullptr) return;

  print_DLCR_rec(static_cast<Node*>(node->_left));

  std::cout << "[key: " << node->_data.first << ", val: "
    << node->_data.second << "]";

  print_DLCR_rec(static_cast<Node*>(node->_right));
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::find_max_left(Node* node) const noexcept {
  if (!node) return nullptr;

  while (node->_right) {
    node = node->_right;
  }

  return node;
}

#endif  // LIB_BSTREE_BSTREE_H_
