// Copyright 2026 Smirnov Nikita

#ifndef LIB_GRAPH_ON_ADJACENCY_MATRIX_GRAPH_ON_ADJACENCY_MATRIX_H_
#define LIB_GRAPH_ON_ADJACENCY_MATRIX_GRAPH_ON_ADJACENCY_MATRIX_H_

#include <utility>
#include <cstdint>
#include <stdexcept>
#include <iostream>

#include "../lib_tvector/tvector.h"
#include "../lib_matrix/matrix.h"

#define STEP_OF_CAPACITY 15

template <class T>
class GraphOnAdjacencyMatrix {
  Matrix<std::pair<bool, size_t>> _data;
  TVector<T> _vertices;
  bool _oriented;
  bool _weighted;

 public:
  GraphOnAdjacencyMatrix(const TVector<std::pair<std::pair<T, T>,
    size_t>>& data, bool oriented, bool weighted);
  ~GraphOnAdjacencyMatrix() = default;

  void add_edge(const T& vertex_1, const T& vertex_2, size_t weight = SIZE_MAX);
  void delete_edge(const T& vertex_1, const T& vertex_2);
  void delete_vertex(const T& vertex);

  void print();
 private:
  void reassemble_matrix(size_t index = SIZE_MAX);
  size_t get_or_create_vertex_index(const T& vertex);
  size_t get_vertex_index(const T& vertex);
};

template <class T>
GraphOnAdjacencyMatrix<T>::GraphOnAdjacencyMatrix(
  const TVector<std::pair<std::pair<T, T>, size_t>>& data,
  bool oriented, bool weighted) :
  _oriented(oriented),
  _weighted(weighted),
  _data(STEP_OF_CAPACITY, STEP_OF_CAPACITY) {
  for (size_t i = 0; i < STEP_OF_CAPACITY; ++i)
        for (size_t j = 0; j < STEP_OF_CAPACITY; ++j)
            _data[i][j] = {false, SIZE_MAX};

  for (size_t i = 0; i < data.size(); i++) {
    add_edge(data[i].first.first, data[i].first.second, data[i].second);
  }
}

template <class T>
void GraphOnAdjacencyMatrix<T>::add_edge(const T& vertex_1,
  const T& vertex_2, size_t weight) {
  size_t idx1 = get_or_create_vertex_index(vertex_1);
  size_t idx2 = get_or_create_vertex_index(vertex_2);

  if (idx1 >= _data.get_lines() || idx2 >= _data.get_lines()) {
    reassemble_matrix();
  }

  if (_data[idx1][idx2].first) {
    throw std::logic_error("Edge already exists");
  }

  size_t final_weight = _weighted ? weight : SIZE_MAX;

  _data[idx1][idx2] = { true, final_weight };

  if (!_oriented && idx1 != idx2) {
    _data[idx2][idx1] = { true, final_weight };
  }
}

template <class T>
void GraphOnAdjacencyMatrix<T>::delete_edge(const T& vertex_1,
  const T& vertex_2) {
  size_t idx1 = get_vertex_index(vertex_1);
  size_t idx2 = get_vertex_index(vertex_2);

  if (idx1 == SIZE_MAX || idx2 == SIZE_MAX) {
    throw std::logic_error("One or both vertices do not exist");
  }

  if (!_data[idx1][idx2].first) {
    throw std::logic_error("Edge does not exist");
  }

  _data[idx1][idx2] = { false, SIZE_MAX };

  if (!_oriented && idx1 != idx2) {
    _data[idx2][idx1] = { false, SIZE_MAX };
  }
}

template <class T>
void GraphOnAdjacencyMatrix<T>::delete_vertex(const T& vertex) {
  size_t idx = get_vertex_index(vertex);

  if (idx == SIZE_MAX) {
    throw std::logic_error("Vertex does not exist");
  }

  _vertices.erase(idx);

  reassemble_matrix(idx);
}

template <class T>
void GraphOnAdjacencyMatrix<T>::print() {
  if (_vertices.size() == 0) {
    std::cout << "Graph is empty." << std::endl;
    return;
  }

  for (size_t i = 0; i < _vertices.size(); i++) {
    std::cout << "[" << _vertices[i] << "]:";

    bool has_edges = false;

    for (size_t j = 0; j < _vertices.size(); j++) {
      if (_data[i][j].first) {
        std::cout << " " << _vertices[j];

        if (_weighted && (_data[i][j].second != SIZE_MAX)) {
          std::cout << " (w: " << _data[i][j].second << ")";
        }
        has_edges = true;
      }
    }
    if (!has_edges) {
      std::cout << " no edges";
    }
    std::cout << std::endl;
  }
}

template <class T>
void GraphOnAdjacencyMatrix<T>::reassemble_matrix(size_t index) {
  size_t new_dimension = _vertices.size() + STEP_OF_CAPACITY;
  Matrix<std::pair<bool, size_t>> new_data(new_dimension, new_dimension);

  for (size_t i = 0; i < new_dimension; i++)
    for (size_t j = 0; j < new_dimension; j++)
      new_data[i][j] = { false, SIZE_MAX };

  size_t new_i = 0;
  for (size_t i = 0; i < _data.get_lines(); i++) {
    if (i == index) continue;

    size_t new_j = 0;
    for (size_t j = 0; j < _data.get_columns(); j++) {
      if (j == index) continue;

      if (new_i < _vertices.size() && new_j < _vertices.size()) {
        new_data[new_i][new_j] = _data[i][j];
      }

      new_j++;
    }
    new_i++;
  }

  _data = new_data;
}

template <class T>
size_t GraphOnAdjacencyMatrix<T>::get_or_create_vertex_index(const T& vertex) {
  size_t index = get_vertex_index(vertex);

  if (index != SIZE_MAX) {
    return index;
  }

  _vertices.push_back(vertex);

  return _vertices.size() - 1;
}

template <class T>
size_t GraphOnAdjacencyMatrix<T>::get_vertex_index(const T& vertex) {
  for (size_t i = 0; i < _vertices.size(); i++) {
    if (_vertices[i] == vertex) {
      return i;
    }
  }

  return SIZE_MAX;
}

#endif  // LIB_GRAPH_ON_ADJACENCY_MATRIX_GRAPH_ON_ADJACENCY_MATRIX_H_
