// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <sstream>
#include <iostream>
#include <string>

#include "../lib_heap/heap.h"

TEST(TestHeapLib, TestInsert) {
  Heap<int> heap;

  heap.insert(3);
  heap.insert(8);
  heap.insert(6);
  heap.insert(2);

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  heap.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "2 3 6 8";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestHeapLib, TestPop) {
  Heap<int> heap;

  heap.insert(3);
  heap.insert(8);
  heap.insert(6);
  heap.insert(2);

  heap.pop();

  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  heap.print();

  std::cout.rdbuf(old_cout);

  std::string expected = "3 8 6";

  EXPECT_EQ(ss.str(), expected);
}

TEST(TestHeapLib, TestPopOneElement) {
  Heap<int> heap;

  heap.insert(3);

  int min = heap.pop();

  EXPECT_EQ(min, 3);
}

TEST(TestHeapLib, TestPopThrowWhenEmptyHeap) {
  Heap<int> heap;

  EXPECT_ANY_THROW(heap.pop());
}

TEST(TestHeapLib, TestSort) {
  Heap<int> heap;

  heap.insert(3);
  heap.insert(8);
  heap.insert(1);
  heap.insert(6);
  heap.insert(2);

  TVector<int> origin;

  origin = heap.sort();

  TVector<int> expected = { 1, 2, 3, 6, 8 };

  EXPECT_EQ(origin, expected);
}

