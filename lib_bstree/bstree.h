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

  virtual void setup_parent(Node* child, Node* parent) {}

  virtual Node* erase_node(Node* toDelete, Node* parent);

 private:
  struct FindResult {
    Node* node = nullptr;
    Node* parent = nullptr;
  };

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
        push_left(static_cast<NodeType*>(node->_right));
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
  FindResult find_max_left_with_parent(Node* node, Node* parent) const noexcept {
    if (!node) return { nullptr, nullptr };
 
    while (node->_right) {
      parent = node;
      node = static_cast<Node*>(node->_right);
    }

    return { node, parent };
  }
  FindResult find_with_parent(const TKey& key) const noexcept {
    Node* cur = _root;
    Node* parent = nullptr;
    while (cur && cur->_data.first != key) {
      parent = cur;
      if (key < cur->_data.first) cur = static_cast<Node*>(cur->_left);
      else cur = static_cast<Node*>(cur->_right);
    }
    return { cur, parent };
  }
  Node* create_node(const TKey& key, const TValue& val) {
     return new Node({ key, val });
   }
  void clear(Node* node);
  void print_DLCR_rec(Node* node) const;
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

  FindResult result = find_with_parent(key);

  Node* node = result.node;

  if (!node) return nullptr;

  return &node->_data.second;
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::insert(const TKey& key, const TValue& val) {
  if (is_empty()) return _root = create_node(key, val);

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

  Node* newNode = create_node(key, val);
  if (parent->_data.first > key) {
    parent->_left = newNode;
  } else {
    parent->_right = newNode;
  }

  setup_parent(newNode, parent);

  return newNode;
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::erase(const TKey& key) {
  if (is_empty()) throw
    std::invalid_argument("You cannot delete element in empty tree!");

  FindResult result = find_with_parent(key);

  Node* toDelete = result.node;
  Node* del_parent = result.parent;

  if (!toDelete) {
    throw std::invalid_argument("The element with this key does not exist!");
  }

  if (toDelete->_left && toDelete->_right) {
    FindResult successor_result =
      find_max_left_with_parent(static_cast<Node*>(toDelete->_left),
        toDelete);
    
    Node* successor = successor_result.node;

    TKey sKey = successor->_data.first;
    TValue sValue = successor->_data.second;

    toDelete->_data.first = sKey;
    toDelete->_data.second = sValue;

    return erase_node(successor, successor_result.parent);;
  }

  return erase_node(toDelete, del_parent);
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
void BSTree<TKey, TValue, Node>::print_DLCR_rec(Node* node) const {
  if (node == nullptr) return;

  print_DLCR_rec(static_cast<Node*>(node->_left));

  std::cout << "[key: " << node->_data.first << ", val: "
    << node->_data.second << "]";

  print_DLCR_rec(static_cast<Node*>(node->_right));
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::erase_node(Node* toDelete, Node* parent) {
  Node* child = toDelete->_left ? static_cast<Node*>(toDelete->_left)
    : static_cast<Node*>(toDelete->_right);

  if (!parent) {
    _root = child;
  } else {
    if (parent->_left == toDelete) {
      parent->_left = child;
    } else {
      parent->_right = child;
    }
  }

  if (child) {
    setup_parent(child, parent);
  }

  delete toDelete;
  return parent;
}

#endif  // LIB_BSTREE_BSTREE_H_
