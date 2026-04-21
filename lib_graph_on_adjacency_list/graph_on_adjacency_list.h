// Copyright 2026 Smirnov Nikita

#ifndef LIB_GRAPH_ON_ADJACENCY_LIST_GRAPH_ON_ADJACENCY_LIST_H_
#define LIB_GRAPH_ON_ADJACENCY_LIST_GRAPH_ON_ADJACENCY_LIST_H_

#include <utility>
#include <cstdint>
#include <stdexcept>
#include <iostream>

#include "../lib_tvector/tvector.h"
#include "../lib_tlist/tlist.h"

template <class T>
class GraphOnAdjacencyList {
  TVector<TList<std::pair<T, size_t>>> _data;
  bool _oriented;
  bool _weighted;

 public:
  GraphOnAdjacencyList(const TVector<std::pair<std::pair<T, T>, size_t>>& data,
    bool oriented, bool weighted);
  ~GraphOnAdjacencyList() = default;

  void add_edge(const T& vertex_1, const T& vertex_2, size_t weight = SIZE_MAX);
  void delete_edge(const T& vertex_1, const T& vertex_2);
  void delete_vertex(const T& vertex);

  void print();

 private:
  size_t get_or_create_vertex_index(const T& vertex);
  size_t find_edge(const TList<std::pair<T, size_t>>& list, const T& vertex);
  size_t get_vertex_index(const T& vertex);
};

template<class T>
GraphOnAdjacencyList<T>::GraphOnAdjacencyList(const
  TVector<std::pair<std::pair<T, T>, size_t>>& data,
  bool oriented, bool weighted) :
  _oriented(oriented), _weighted(weighted) {
  for (size_t i = 0; i < data.size(); i++) {
    add_edge(data[i].first.first, data[i].first.second, data[i].second);
  }
}

template <class T>
void GraphOnAdjacencyList<T>::add_edge(const T& vertex_1,
  const T& vertex_2, size_t weight) {
  size_t idx1 = get_or_create_vertex_index(vertex_1);
  size_t idx2 = get_or_create_vertex_index(vertex_2);

  if (find_edge(_data[idx1], vertex_2) != SIZE_MAX) {
    throw std::logic_error("Edge already exists");
  }

  size_t final_weight = _weighted ? weight : SIZE_MAX;

  _data[idx1].push_back(std::make_pair(vertex_2, final_weight));

  if (!_oriented && idx1 != idx2) {
    _data[idx2].push_back(std::make_pair(vertex_1, final_weight));
  }
}

template <class T>
void GraphOnAdjacencyList<T>::delete_edge(const T& vertex_1,
  const T& vertex_2) {
  size_t idx1 = get_vertex_index(vertex_1);
  size_t idx2 = get_vertex_index(vertex_2);

  if (idx1 == SIZE_MAX || idx2 == SIZE_MAX) {
    throw std::logic_error("One or both vertices do not exist");
  }

  size_t idx_del = find_edge(_data[idx1], vertex_2);

  if (idx_del == SIZE_MAX) {
    throw std::logic_error("Edge does not exist");
  }

  _data[idx1].erase(idx_del);

  if (!_oriented && idx1 != idx2) {
    idx_del = find_edge(_data[idx2], vertex_1);
    _data[idx2].erase(idx_del);
  }
}

template <class T>
void GraphOnAdjacencyList<T>::delete_vertex(const T& vertex) {
  size_t idx1 = get_vertex_index(vertex);

  if (idx1 == SIZE_MAX) {
    throw std::logic_error("Vertex does not exist");
  }

  _data.erase(idx1);

  for (size_t i = 0; i < _data.size(); i++) {
    size_t idx_del = find_edge(_data[i], vertex);

    if (idx_del != SIZE_MAX) {
      _data[i].erase(idx_del);
    }
  }
}

template<class T>
void GraphOnAdjacencyList<T>::print() {
  if (_data.is_empty()) {
    std::cout << "Graph is empty." << std::endl;
    return;
  }

  for (size_t i = 0; i < _data.size(); i++) {
    auto it = _data[i].begin();

    std::cout << "[" << (*it).first << "]:";

    ++it;

    if (it == _data[i].end()) {
      std::cout << " no edges";
    } else {
      while (it != _data[i].end()) {
        std::cout << " " << (*it).first;

        if (_weighted && (*it).second != SIZE_MAX) {
          std::cout << " (w: " << (*it).second << ")";
        }
        ++it;
      }
    }
    std::cout << std::endl;
  }
}

template<class T>
size_t GraphOnAdjacencyList<T>::get_or_create_vertex_index(const T& vertex) {
  size_t index = get_vertex_index(vertex);

  if (index != SIZE_MAX) return index;

  TList<std::pair<T, size_t>> tlist;

  auto core_vertex = std::make_pair(vertex, SIZE_MAX);

  tlist.push_back(core_vertex);

  _data.push_back(tlist);

  return _data.size() - 1;
}

template<class T>
size_t GraphOnAdjacencyList<T>::find_edge(const TList<std::pair<T,
  size_t>>& list, const T& vertex) {
  if (list.is_empty()) return SIZE_MAX;

  size_t index = 0;
  auto it = list.begin();

  ++it;
  ++index;

  for (; it != list.end(); ++it) {
    if ((*it).first == vertex) {
      return index;
    }
    ++index;
  }

  return SIZE_MAX;
}

template<class T>
size_t GraphOnAdjacencyList<T>::get_vertex_index(const T& vertex) {
  for (size_t i = 0; i < _data.size(); i++) {
    if ((*_data[i].begin()).first == vertex) {
      return i;
    }
  }

  return SIZE_MAX;
}

#endif  // LIB_GRAPH_ON_ADJACENCY_LIST_GRAPH_ON_ADJACENCY_LIST_H_
