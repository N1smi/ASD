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
  void setup_parent(Node* child, Node* parent) override {
    if (child) {
      child->_parent = parent;
    }
  }

  Node* erase_node(Node* toDelete, Node* parent) override {
    Node* child = toDelete->_left ? static_cast<Node*>(toDelete->_left)
      : static_cast<Node*>(toDelete->_right);

    Color deletedColor = toDelete->_color;

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

    if (deletedColor == BLACK) {
      fix_after_erase(child, parent);
    }

    return parent;
  }

 private:
  Color color_of(Node* node) const {
    return node == nullptr ? BLACK : node->_color;
  }
  void set_color(Node* node, Color color) {
    if (node != nullptr) node->_color = color;
  }

  bool check_validity_recursive(Node* node,
    int current_black_count, int& expected_black_height) const;

  void left_rotate(Node* grandpa);
  void right_rotate(Node* grandpa);

  void RR(Node* grandpa);
  void LL(Node* grandpa);
  void LR(Node* grandpa);
  void RL(Node* grandpa);

  void fix_after_insert(Node* child);
  void fix_after_erase(Node* child, Node* parent);
};

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
  Node* inserted_node = static_cast<Node*>
    (BSTree<TKey, TValue, Node>::insert(key, val));

  set_color(inserted_node, RED);

  fix_after_insert(inserted_node);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::erase(const TKey& key) {
  BSTree<TKey, TValue, Node>::erase(key);
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
void RBTree<TKey, TValue>::LL(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_left);

  set_color(parent, BLACK);
  set_color(grandpa, RED);
  right_rotate(grandpa);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::RR(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_right);

  set_color(parent, BLACK);
  set_color(grandpa, RED);
  left_rotate(grandpa);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::LR(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_left);

  left_rotate(parent);
  LL(grandpa);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::RL(Node* grandpa) {
  Node* parent = static_cast<Node*>(grandpa->_right);

  right_rotate(parent);
  RR(grandpa);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::fix_after_insert(Node* child) {
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
          LR(grandpa);
        } else {
          LL(grandpa);
        }
        break;
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
          RL(grandpa);
        } else {
          RR(grandpa);
        }
        break;
      }
    }
  }

  set_color(_root, BLACK);
}

template <typename TKey, typename TValue>
void RBTree<TKey, TValue>::fix_after_erase(Node* child, Node* parent) {
  while (child != _root && color_of(child) == BLACK) {
    if (child == parent->_left) {
      Node* sib = static_cast<Node*>(parent->_right);

      if (color_of(sib) == RED) {
        set_color(sib, BLACK);
        set_color(parent, RED);
        left_rotate(parent);
        sib = static_cast<Node*>(parent->_right);
      }

      if (color_of(static_cast<Node*>(sib->_left)) == BLACK &&
        color_of(static_cast<Node*>(sib->_right)) == BLACK) {
        set_color(sib, RED);
        child = parent;
        parent = child->_parent;
      } else {
        if (color_of(static_cast<Node*>(sib->_right)) == BLACK) {
          set_color(static_cast<Node*>(sib->_left), BLACK);
          set_color(sib, RED);
          right_rotate(sib);
          sib = static_cast<Node*>(parent->_right);
        }

        set_color(sib, color_of(parent));
        set_color(parent, BLACK);
        set_color(static_cast<Node*>(sib->_right), BLACK);
        left_rotate(parent);
        child = _root;
      }
    } else {
      Node* sib = static_cast<Node*>(parent->_left);

      if (color_of(sib) == RED) {
        set_color(sib, BLACK);
        set_color(parent, RED);
        right_rotate(parent);
        sib = static_cast<Node*>(parent->_left);
      }

      if (color_of(static_cast<Node*>(sib->_right)) == BLACK &&
        color_of(static_cast<Node*>(sib->_left)) == BLACK) {
        set_color(sib, RED);
        child = parent;
        parent = child->_parent;
      } else {
        if (color_of(static_cast<Node*>(sib->_left)) == BLACK) {
          set_color(static_cast<Node*>(sib->_right), BLACK);
          set_color(sib, RED);
          left_rotate(sib);
          sib = static_cast<Node*>(parent->_left);
        }

        set_color(sib, color_of(parent));
        set_color(parent, BLACK);
        set_color(static_cast<Node*>(sib->_left), BLACK);
        right_rotate(parent);
        child = _root;
      }
    }
  }

  set_color(child, BLACK);
}

#endif  // LIB_RBTREE_RBTREE_H_
