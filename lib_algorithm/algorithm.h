// Copyright 2025 Smirnov Nikita

#ifndef LIB_ALGORITHM_ALGORITHM_H_
#define LIB_ALGORITHM_ALGORITHM_H_

#include <iostream>
#include <utility>
#include<stdexcept>
#include <string>
#include "../lib_matrix/matrix.h"
#include "../lib_tdynamic_stack/tdynamic_stack.h"
#include "../lib_tlist/tlist.h"
#include "../lib_dsu/dsu.h"
#include "../lib_priority_queue/priority_queue.h"
#include "../lib_tvector/tvector.h"
#include "../lib_hash_table_oa/hash_table_oa.h"
#include "../lib_graph_on_adjacency_list/graph_on_adjacency_list.h"

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

Matrix<bool> generate_maze(size_t entry, size_t exit,
  size_t lines, size_t columns);

void print_maze(const Matrix<bool>& maze);

void print_maze_with_color(const Matrix<bool>& maze,
  size_t entry, size_t exit,
  size_t lines, size_t columns);

template <class T>
void find_most_important(const TVector<std::pair<size_t, T>> data, size_t K) {
  PriorityQueue<T> q;
  for (size_t i = 0; i < data.size(); i++) {
    q.push(data[i].first, data[i].second);
  }

  std::cout << K <<  " important: " << std::endl;

  for (size_t i = 0; i < K; i++) {
    try {
      std::cout << q.top() << std::endl;
      q.pop();
    }
    catch (const std::runtime_error& e) {
      break;
    }
  }
}

template <class T>
HashTableOA<T> dictionary_merge(const TVector<std::pair<std::string,
  T>>& first_d, const TVector<std::pair<std::string, T>>& second_d) {
  HashTableOA<T> table(first_d.size() + second_d.size());

  for (size_t i = 0; i < first_d.size(); i++) {
    table.insert(first_d[i].first, first_d[i].second);
  }

  for (size_t i = 0; i < second_d.size(); i++) {
    table.insert(second_d[i].first, second_d[i].second);
  }

  return table;
}

template <class T>
std::pair<TVector<size_t>, TVector<size_t>> dijkstra(const T& start, const GraphOnAdjacencyList<T>& graph) {
  size_t vertex_count = graph.get_count_vertex();
  size_t start_idx = graph.get_vertex_index(start);

  if (start_idx == SIZE_MAX) {
    throw std::logic_error("Start vertex does not exist!");
  }

  TVector<size_t> distance(vertex_count);
  TVector<bool> visited(vertex_count);
  TVector<size_t> parent(vertex_count);

  for (size_t i = 0; i < vertex_count; i++) {
    distance[i] = SIZE_MAX;
    visited[i] = false;
    parent[i] = SIZE_MAX;
  }

  distance[start_idx] = 0;

  for (size_t i = 0; i < vertex_count; i++) {
    size_t min_dist = SIZE_MAX;
    size_t vertex_index = SIZE_MAX;

    for (size_t j = 0; j < vertex_count; j++) {
      if (!visited[j] && distance[j] <= min_dist) {
        min_dist = distance[j];
        vertex_index = j;
      }
    }

    if (vertex_index == SIZE_MAX || distance[vertex_index] == SIZE_MAX) {
      break;
    }

    visited[vertex_index] = true;

    const auto& adj_list = graph.get_adjacency_list(vertex_index);
    auto it = adj_list.begin();

    ++it;

    for (; it != adj_list.end(); ++it) {
      T neighbor_vertex = (*it).first;
      size_t weight = (*it).second;

      size_t neighbor_vertex_idx = graph.get_vertex_index(neighbor_vertex);

      if (!visited[neighbor_vertex_idx]
        && distance[vertex_index] + weight < distance[neighbor_vertex_idx]) {
        distance[neighbor_vertex_idx] = distance[vertex_index] + weight;
        parent[neighbor_vertex_idx] = vertex_index;
      }
    }
  }

  return std::make_pair(distance, parent);
}

#endif  // LIB_ALGORITHM_ALGORITHM_H_
