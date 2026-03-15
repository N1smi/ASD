// Copyright 2026 Smirnov Nikita // NOLINT

#ifndef LIB_SKIP_LIST_SKIP_LIST_H_
#define LIB_SKIP_LIST_SKIP_LIST_H_

#include <windows.h>

#include <iostream>
#include <random>
#include <string>
#include <utility>

#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class SkipList {
 private:
  struct Node {
    std::pair<TKey, TValue> data;
    Node** next;
    size_t level;

    Node(const std::pair<TKey, TValue>& value_, size_t level_)
        : data(value_), level(level_) {
      next = new Node*[level + 1];
      for (size_t i = 0; i <= level; i++) {
        next[i] = nullptr;
      }
    }

    ~Node() { delete[] next; }

    TKey getKey() const { return data.first; }
    TValue getValue() const { return data.second; }
  };

 private:
  Node* _head;
  size_t _MAX_LEVELS;
  size_t _current_level;
  std::mt19937 _rng;

 public:
  explicit SkipList(size_t max_levels = 5);
  ~SkipList();

  bool contains(const TKey& key) const noexcept;

  inline bool is_empty() const noexcept { return _head->next[0] == nullptr; }

  void insert(const TKey& key, const TValue& value);
  void print() const noexcept;

 private:
  size_t flip_coin() noexcept;
  TVector<Node*> find_prev_nodes(const TKey&) const noexcept;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_levels)
    : _MAX_LEVELS(max_levels), _current_level(0), _rng(std::random_device{}()) {
  _head = new Node(std::make_pair(TKey(), TValue()), max_levels);
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
  Node* current = _head->next[0];

  while (current != nullptr) {
    Node* next = current->next[0];
    delete current;
    current = next;
  }

  delete _head;
}

template <class TKey, class TValue>
bool SkipList<TKey, TValue>::contains(const TKey& key) const noexcept {
  Node* current = _head->next[0];

  while (current != nullptr && current->getKey() < key) {
    current = current->next[0];
  }

  return (current != nullptr && current->getKey() == key);
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
  TVector<Node*> prevs = find_prev_nodes(key);

  Node* next = prevs[0]->next[0];
  if (next != nullptr && next->getKey() == key) {
    throw std::invalid_argument(
        "The SkipList already "
        "contains an element with the given key!");
  }

  size_t new_level = 0;
  while (flip_coin() && new_level != _MAX_LEVELS - 1) {
    new_level++;
  }

  Node* new_node = new Node(std::make_pair(key, value), new_level);

  if (new_level > _current_level) {
    _current_level = new_level;
  }

  for (size_t i = 0; i <= new_level; i++) {
    new_node->next[i] = prevs[i]->next[i];
    prevs[i]->next[i] = new_node;
  }
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  if (is_empty()) {
    std::cout << "SkipList is empty\n";
    return;
  }

  std::cout << "\n=== Skip List (levels: " << _current_level
            << ", max: " << _MAX_LEVELS << ") ===\n";

  TVector<Node*> all_nodes;
  Node* current = _head->next[0];
  while (current != nullptr) {
    all_nodes.push_back(current);
    current = current->next[0];
  }

  for (size_t level = _current_level; level > 0; level--) {
    std::cout << "L" << level << ": ";

    size_t node_index = 0;
    current = _head->next[level];
    bool arrow_active = false;
    size_t arrow_start = 0;

    while (node_index < all_nodes.size()) {
      if (current != nullptr &&
          all_nodes[node_index]->getKey() == current->getKey()) {
        if (arrow_active) {
          for (size_t i = arrow_start; i < node_index; i++) {
            std::cout << "─────────";
          }
          std::cout << "→ ";
          arrow_active = false;
        }

        std::string key_str = std::to_string(current->getKey());
        if (key_str.length() >= 3) {
          std::cout << "[" << key_str.substr(0, 2) << "..] ";
        } else {
          std::cout << "[" << key_str;
          for (size_t i = key_str.length(); i < 4; i++) {
            std::cout << " ";
          }
          std::cout << "] ";
        }

        if (current->next[level] != nullptr) {
          arrow_active = true;
          arrow_start = node_index + 1;
        }

        current = current->next[level];
      } else {
        if (!arrow_active) {
          std::cout << "         ";
        }
      }
      node_index++;
    }
    std::cout << "\n";
  }

  std::cout << "L0: ";
  current = _head->next[0];
  while (current) {
    std::string key_str = std::to_string(current->getKey());
    if (key_str.length() >= 3) {
      std::cout << "[" << key_str.substr(0, 2) << "..]";
    } else {
      std::cout << "[" << key_str;
      for (size_t i = key_str.length(); i < 4; i++) {
        std::cout << " ";
      }
      std::cout << "]";
    }
    if (current->next[0] != nullptr) {
      std::cout << " → ";
    }
    current = current->next[0];
  }
  std::cout << "\n=====================================\n" << std::endl;
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() noexcept {
  return (_rng() & 1);
}

template <class TKey, class TValue>
TVector<typename SkipList<TKey, TValue>::Node*>
SkipList<TKey, TValue>::find_prev_nodes(const TKey& key) const noexcept {
  TVector<Node*> prevs(_MAX_LEVELS);
  Node* current = _head;

  for (size_t i = 0; i < _MAX_LEVELS; i++) {
    prevs[i] = _head;
  }

  for (size_t level = _current_level; level > 0; level--) {
    while (current->next[level] != nullptr &&
           current->next[level]->getKey() < key) {
      current = current->next[level];
    }
    prevs[level] = current;
  }

  while (current->next[0] != nullptr && current->next[0]->getKey() < key) {
    current = current->next[0];
  }
  prevs[0] = current;

  return prevs;
}

#endif  // LIB_SKIP_LIST_SKIP_LIST_H_
