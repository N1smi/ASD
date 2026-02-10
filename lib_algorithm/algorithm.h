// Copyright 2025 Smirnov Nikita

#ifndef LIB_ALGORITHM_ALGORITHM_H_
#define LIB_ALGORITHM_ALGORITHM_H_

#include <iostream>
#include<stdexcept>
#include <string>
#include "../lib_matrix/matrix.h"
#include "../lib_tdynamic_stack/tdynamic_stack.h"
#include "../lib_tlist/tlist.h"
#include "../lib_dsu/dsu.h"

int find_local_min(const Matrix<int>& matrix);

void find_best_neighbor(const Matrix<int>& matrix, size_t i, size_t j,
  size_t& new_i, size_t& new_j);

bool check_breckets(const std::string& str);

void read_expression(const std::string& expression);

template <class T>
bool is_looped_hare(const TList<T>& list) {
  if (list.is_empty()) return false;

  auto turtle = list.begin();
  auto hare = list.begin();

  while (hare != list.end()) {
    ++turtle;
    if (turtle == list.end()) break;

    hare += 2;

    if (turtle == hare) {
      return true;
    }
  }

  return false;
}

template <class T>
bool is_looped_reverse(TList<T>& list) {
  if (list.is_empty()) return false;

  TVector<typename TList<T>::Node*> nodes;
  TVector<typename TList<T>::Node*> original_nexts;

  nodes.reserve(list.size());
  original_nexts.reserve(list.size());

  typename TList<T>::Node* current = list.head();
  for (size_t i = 0; i < list.size() && current != nullptr; i++) {
    nodes.push_back(current);
    original_nexts.push_back(current->next);
    current = current->next;
  }

  typename TList<T>::Node* prev = nullptr;
  current = list.head();
  typename TList<T>::Node* next_to = nullptr;
  typename TList<T>::Node* original_head = list.head();

  bool has_cycle = false;

  while (current != nullptr) {
    next_to = current->next;
    current->next = prev;
    prev = current;
    current = next_to;

    if (current == original_head) {
      has_cycle = true;
      break;
    }
  }

  for (size_t i = 0; i < nodes.size(); i++) {
    nodes[i]->next = original_nexts[i];
  }

  return has_cycle;
}

template <class T>
typename TList<T>::Node* find_loop(TList<T>& list) {
  if (list.is_empty()) return nullptr;

  typename TList<T>::Node* turtle = list.head();
  typename TList<T>::Node* hare = list.head();

  bool has_cycle = false;
  while (hare != nullptr && hare->next != nullptr) {
    turtle = turtle->next;
    hare = hare->next->next;

    if (turtle == hare) {
      has_cycle = true;
      break;
    }
  }

  if (!has_cycle) return nullptr;

  turtle = list.head();
  while (turtle != hare) {
    turtle = turtle->next;
    hare = hare->next;
  }

  return turtle;
}

int countIslands(const Matrix<int>& matrix);

Matrix<bool> generate_maze(size_t entry, size_t exit, size_t lines, size_t columns);

void print_maze(const Matrix<bool>& maze);

void print_maze_with_color(const Matrix<bool>& maze,
  size_t entry, size_t exit,
  size_t lines, size_t columns);

#endif  // LIB_ALGORITHM_ALGORITHM_H_
