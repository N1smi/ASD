// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <utility>
#include <sstream>
#include <cstdint>

#include "../lib_graph_on_adjacency_list/graph_on_adjacency_list.h"
#include "../lib_tvector/tvector.h"

TEST(TestGraphOnAdjacencyListLib, CreateNotOrientedGraph) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 3);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyList<int> graph(vector, false, false);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: 2 3\n[2]: 1 3\n[3]: 2 1\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyListLib, CreateOrientedGraph) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 3);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyList<int> graph(vector, true, false);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: 2 3\n[2]: no edges\n[3]: 2\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyListLib, CreateWeightedGraph) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 2);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyList<int> graph(vector, true, true);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: 2 (w: 3) 3 (w: 4)\n[2]: no edges\n[3]: 2 (w: 2)\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyListLib, AddEdgeThrowsOnDuplicate) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyList<int> graph(empty_data, true, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.add_edge(1, 2), std::logic_error);
}

TEST(TestGraphOnAdjacencyListLib, AddSelfLoop) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyList<int> graph(empty_data, false, true);

  graph.add_edge(1, 1, 0);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  EXPECT_EQ(ss.str(), "[1]: 1 (w: 0)\n");
}

TEST(TestGraphOnAdjacencyListLib, DeleteEdgeNotOriented) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;
  vector.push_back({ {1, 2}, 0 });

  GraphOnAdjacencyList<int> graph(vector, false, false);

  graph.delete_edge(1, 2);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: no edges\n[2]: no edges\n";
  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyListLib, DeleteEdgeOriented) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;
  vector.push_back({ {1, 2}, 0 });
  vector.push_back({ {2, 1}, 0 });

  GraphOnAdjacencyList<int> graph(vector, true, false);

  graph.delete_edge(1, 2);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  std::string expected = "[1]: no edges\n[2]: 1\n";
  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyListLib, DeleteEdgeThrowsIfNotFoundVertex) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyList<int> graph(empty_data, false, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.delete_edge(1, 3), std::logic_error);
}

TEST(TestGraphOnAdjacencyListLib, DeleteEdgeThrowsIfNotFoundEdge) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyList<int> graph(empty_data, true, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.delete_edge(2, 1), std::logic_error);
}

TEST(TestGraphOnAdjacencyListLib, DeleteSelfLoop) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyList<int> graph(empty_data, false, false);

  graph.add_edge(1, 1);
  graph.delete_edge(1, 1);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
  graph.print();
  std::cout.rdbuf(old_cout);

  EXPECT_EQ(ss.str(), "[1]: no edges\n");
}

TEST(TestGraphOnAdjacencyListLib, DeleteVertex) {
  TVector<std::pair<std::pair<int, int>, size_t>> vector;

  auto pair1 = std::make_pair(std::make_pair(1, 2), 3);
  auto pair2 = std::make_pair(std::make_pair(3, 2), 3);
  auto pair3 = std::make_pair(std::make_pair(1, 3), 4);

  vector.push_back(pair1);
  vector.push_back(pair2);
  vector.push_back(pair3);

  GraphOnAdjacencyList<int> graph(vector, false, false);

  graph.delete_vertex(1);
  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  graph.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "[2]: 3\n[3]: 2\n";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestGraphOnAdjacencyListLib, DeleteVertexThrowWhenInvalidVertex) {
  TVector<std::pair<std::pair<int, int>, size_t>> empty_data;
  GraphOnAdjacencyList<int> graph(empty_data, true, false);

  graph.add_edge(1, 2);

  EXPECT_THROW(graph.delete_vertex(3), std::logic_error);
}
