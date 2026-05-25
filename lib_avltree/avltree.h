// Copyright 2026 Smirnov Nikita

#ifndef LIB_AVLTREE_AVLTREE_H_
#define LIB_AVLTREE_AVLTREE_H_

#include<utility>
#include <iostream>
#include <algorithm>
#include "../lib_bstree/bstree.h"

template <typename TKey, typename TValue>
struct AVLNode : public BSTNode<TKey, TValue> {
  AVLNode* _parent = nullptr;
  int _height = 1;

  explicit AVLNode(const std::pair<TKey, TValue>& val)
    : BSTNode<TKey, TValue>(val) {}
};

template <typename TKey, typename TValue>
class AVLTree : public BSTree<TKey, TValue, AVLNode<TKey, TValue>> {
 private:
  using Node = AVLNode<TKey, TValue>;

  using BSTree<TKey, TValue, Node>::_root;

 public:
  AVLTree() = default;
  ~AVLTree() = default;

  void insert(const TKey& key, const TValue& val);
  void erase(const TKey& key);

  bool is_valid_avl() const {
    return is_balanced_recursive(_root);
  }

 protected:
  void setup_parent(Node* child, Node* parent) override {
    if (child) {
      child->_parent = parent;
    }
  }

 private:
  void left_rotate(Node* grandpa);
  void right_rotate(Node* grandpa);

  void RR(Node* grandpa);
  void LL(Node* grandpa);
  void LR(Node* grandpa);
  void RL(Node* grandpa);

  int get_height(Node* node) const;
  int get_balance(Node* node) const;

  void recalc_height(Node* node);
  void recover_balance(Node* node);

  bool is_balanced_recursive(Node* node) const;
};

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
  Node* newNode = BSTree<TKey, TValue, Node>::insert(key, val);

  recover_balance(newNode->_parent);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
  Node* balanceStart =
    static_cast<Node*>(BSTree<TKey, TValue, Node>::erase(key));

  if (balanceStart) {
    recover_balance(balanceStart);
  }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::left_rotate(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_right);
  Node* sib = static_cast<Node*>(parent->_left);
  Node* great_grandpa = grandpa->_parent;

  parent->_left = grandpa;
  grandpa->_right = sib;

  if (sib) sib->_parent = grandpa;

  parent->_parent = great_grandpa;
  grandpa->_parent = parent;

  if (!great_grandpa) {
    _root = parent;
  } else if (great_grandpa->_left == grandpa) {
    great_grandpa->_left = parent;
  } else {
    great_grandpa->_right = parent;
  }

  recalc_height(grandpa);
  recalc_height(parent);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::right_rotate(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_left);
  Node* sib = static_cast<Node*>(parent->_right);
  Node* great_grandpa = grandpa->_parent;

  parent->_right = grandpa;

  grandpa->_left = sib;

  if (sib) sib->_parent = grandpa;

  parent->_parent = great_grandpa;

  grandpa->_parent = parent;

  if (!great_grandpa) {
    _root = parent;
  } else if (great_grandpa->_left == grandpa) {
    great_grandpa->_left = parent;
  } else if (great_grandpa->_right == grandpa) {
    great_grandpa->_right = parent;
  }

  recalc_height(grandpa);
  recalc_height(parent);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RR(Node* grandpa) {
  left_rotate(grandpa);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LL(Node* grandpa) {
  right_rotate(grandpa);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LR(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_left);

  left_rotate(parent);

  right_rotate(grandpa);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RL(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_right);

  right_rotate(parent);

  left_rotate(grandpa);
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::get_height(Node* node) const {
  if (node == nullptr) return 0;

  return node->_height;
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::get_balance(Node* node) const {
  if (node == nullptr) return 0;

  return get_height(static_cast<Node*>(node->_left))
    - get_height(static_cast<Node*>(node->_right));
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::recalc_height(Node* node) {
  if (node != nullptr) {
    node->_height = std::max(get_height(static_cast<Node*>(node->_left)),
      get_height(static_cast<Node*>(node->_right))) + 1;
  }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::recover_balance(Node* node) {
  while (node) {
    recalc_height(node);
    int balance = get_balance(node);

    if (balance > 1) {
      if (get_balance(static_cast<Node*>(node->_left)) >= 0) {
        LL(node);
      } else {
        LR(node);
      }
    } else if (balance < -1) {
      if (get_balance(static_cast<Node*>(node->_right)) <= 0) {
        RR(node);
      } else {
        RL(node);
      }
    }

    node = node->_parent;
  }
}

template <typename TKey, typename TValue>
bool AVLTree<TKey, TValue>::is_balanced_recursive(Node* node) const {
  if (node == nullptr) return true;

  int bf = const_cast<AVLTree*>(this)->get_balance(node);
  if (bf < -1 || bf > 1) {
    return false;
  }

  int real_h = std::max(
    const_cast<AVLTree*>(this)->get_height(static_cast<Node*>(node->_left)),
    const_cast<AVLTree*>(this)->get_height(static_cast<Node*>(node->_right)))
    + 1;

  if (node->_height != real_h) {
    return false;
  }

  return is_balanced_recursive(static_cast<Node*>(node->_left)) &&
    is_balanced_recursive(static_cast<Node*>(node->_right));
}

#endif  // LIB_AVLTREE_AVLTREE_H_
