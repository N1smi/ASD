// Copyright 2026 Smirnov Nikita

#ifndef LIB_RBTREE_RBTREE_H_
#define LIB_RBTREE_RBTREE_H_

#include <utility>
#include "../lib_bstree/bstree.h"

enum Color { RED, BLACK };

template <typename TKey, typename TValue>
struct RBNode : public BSTNode<TKey, TValue> {
  RBNode* _parent = nullptr;
  Color _color = RED;

  explicit RBNode(const std::pair<TKey, TValue>& val)
    : BSTNode<TKey, TValue>(val) {}
};

template <typename TKey, typename TValue>
class RBTree : public BSTree<TKey, TValue, RBNode<TKey, TValue>> {
 private:
  using Node = RBNode<TKey, TValue>;

  using BSTree<TKey, TValue, Node>::_root;

 public:
  RBTree() = default;
  ~RBTree() = default;

  void insert(const TKey& key, const TValue& val);
  void erase(const TKey& key);

  bool is_valid_rb() const;

 protected:
  void setupParent(Node* child, Node* parent) override {
    if (child) {
      child->_parent = parent;
    }
  }

 private:
  Color color_of(Node* node) const {
    return node == nullptr ? BLACK : node->_color;
  }
  void set_color(Node* node, Color color) {
    if (node != nullptr) node->_color = color;
  }
  void swap_colors(Node* first, Node* second) {
    Color temp = first->_color;
    first->_color = second->_color;
    second->_color = temp;
  }
  void recolor(Node* node) {
    node->_color = node->_color == BLACK ? RED : BLACK;
  }

  bool check_validity_recursive(Node* node,
    int current_black_count, int& expected_black_height) const;

  void left_rotate(Node* grandpa);
  void right_rotate(Node* grandpa);

  void insert_fixup(Node* child);
  void erase_fixup(Node* succesor_child, Node* parent);
};

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
  Node* inserted_node = static_cast<Node*>
    (BSTree<TKey, TValue, Node>::insert(key, val));

  set_color(inserted_node, RED);

  insert_fixup(inserted_node);
}

template <typename TKey, typename TValue>
bool RBTree<TKey, TValue>::is_valid_rb() const {
  if (_root == nullptr) return true;

  if (_root->_color != BLACK) return false;

  int black_height = -1;
  return check_validity_recursive(_root, 0, black_height);
}

template <typename TKey, typename TValue>
bool RBTree<TKey, TValue>::check_validity_recursive(Node* node,
  int current_black_count, int& expected_black_height) const {
  if (node == nullptr) {
    current_black_count++;

    if (expected_black_height == -1) {
      expected_black_height = current_black_count;
      return true;
    }

    return current_black_count == expected_black_height;
  }

  if (node->_color == RED) {
    if (color_of(static_cast<Node*>(node->_left)) == RED ||
      color_of(static_cast<Node*>(node->_right)) == RED) {
      return false;
    }
  }

  if (node->_color == BLACK) {
    current_black_count++;
  }

  return check_validity_recursive(static_cast<Node*>(node->_left),
    current_black_count, expected_black_height) &&
    check_validity_recursive(static_cast<Node*>(node->_right),
      current_black_count, expected_black_height);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::left_rotate(Node* grandpa) {
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
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::right_rotate(Node* grandpa) {
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
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::insert_fixup(Node* child) {
  while (child != _root && color_of(child->_parent) == RED) {
    Node* parent = child->_parent;
    Node* grandpa = parent->_parent;

    if (parent == grandpa->_left) {
      Node* uncle = static_cast<Node*>(grandpa->_right);

      if (color_of(uncle) == RED) {
        set_color(parent, BLACK);
        set_color(uncle, BLACK);
        set_color(grandpa, RED);
        child = grandpa;
      } else {
        if (child == parent->_right) {
          child = parent;
          left_rotate(parent);
          parent = child->_parent;
        }
        set_color(parent, BLACK);
        set_color(grandpa, RED);
        right_rotate(grandpa);
      }
    } else if (parent == grandpa->_right) {
      Node* uncle = static_cast<Node*>(grandpa->_left);

      if (color_of(uncle) == RED) {
        set_color(parent, BLACK);
        set_color(uncle, BLACK);
        set_color(grandpa, RED);
        child = grandpa;
      } else {
        if (child == parent->_left) {
          child = parent;
          right_rotate(parent);
          parent = child->_parent;
        }
        set_color(parent, BLACK);
        set_color(grandpa, RED);
        left_rotate(grandpa);
      }
    }
  }

  set_color(_root, BLACK);
}

#endif  // LIB_RBTREE_RBTREE_H_
