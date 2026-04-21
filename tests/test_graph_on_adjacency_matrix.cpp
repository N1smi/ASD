// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstdint>
#include <string>

#include "../lib_graph_on_adjacency_matrix/graph_on_adjacency_matrix.h"

TEST(TestGraphOnAdjacencyMatrixLib, CreateNotOrientedGraph) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 3);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyMatrix<int> graph(vector, false, false);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: 2 3\n[2]: 1 3\n[3]: 1 2\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyMatrixLib, CreateOrientedGraph) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 3);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyMatrix<int> graph(vector, true, false);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: 2 3\n[2]: no edges\n[3]: 2\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyMatrixLib, CreateWeightedGraph) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 2);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyMatrix<int> graph(vector, true, true);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected =
    "[1]: 2 (w: 3) 3 (w: 4)\n[2]: no edges\n[3]: 2 (w: 2)\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyMatrixLib, AddEdgeThrowsOnDuplicate) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyMatrix<int> graph(empty_data, true, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.add_edge(1, 2), std::logic_error);
}

TEST(TestGraphOnAdjacencyMatrixLib, AddSelfLoop) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyMatrix<int> graph(empty_data, false, true);

  graph.add_edge(1, 1, 0);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  EXPECT_EQ(ss.str(), "[1]: 1 (w: 0)\n");
}

TEST(TestGraphOnAdjacencyMatrixLib, ResizeMatrixWhenCapacityExceeded) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyMatrix<int> graph(empty_data, true, false);

  for (int i = 0; i < 14; ++i) {
    graph.add_edge(i, i + 1);
  }

  EXPECT_NO_THROW(graph.add_edge(14, 15));

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  EXPECT_TRUE(ss.str().find("[14]: 15") != std::string::npos);
  EXPECT_TRUE(ss.str().find("[15]: no edges") != std::string::npos);
}

TEST(TestGraphOnAdjacencyMatrixLib, DeleteEdgeNotOriented) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;
  vector.push_back({ {1, 2}, 0 });

  GraphOnAdjacencyMatrix<int> graph(vector, false, false);

  graph.delete_edge(1, 2);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: no edges\n[2]: no edges\n";
  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyMatrixLib, DeleteEdgeOriented) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;
  vector.push_back({ {1, 2}, 0 });
  vector.push_back({ {2, 1}, 0 });

  GraphOnAdjacencyMatrix<int> graph(vector, true, false);

  graph.delete_edge(1, 2);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: no edges\n[2]: 1\n";
  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyMatrixLib, DeleteEdgeThrowsIfNotFoundVertex) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyMatrix<int> graph(empty_data, false, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.delete_edge(1, 3), std::logic_error);
}

TEST(TestGraphOnAdjacencyMatrixLib, DeleteEdgeThrowsIfNotFoundEdge) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyMatrix<int> graph(empty_data, true, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.delete_edge(2, 1), std::logic_error);
}

TEST(TestGraphOnAdjacencyMatrixLib, DeleteSelfLoop) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyMatrix<int> graph(empty_data, false, false);

  graph.add_edge(1, 1);
  graph.delete_edge(1, 1);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  EXPECT_EQ(ss.str(), "[1]: no edges\n");
}

TEST(TestGraphOnAdjacencyMatrixLib, DeleteVertex) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 3);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyMatrix<int> graph(vector, false, false);

  graph.delete_vertex(1);
  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "[2]: 3\n[3]: 2\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyMatrixLib, DeleteVertexThrowWhenInvalidVertex) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyMatrix<int> graph(empty_data, true, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.delete_vertex(3), std::logic_error);
}
