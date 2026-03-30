// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include "../lib_priority_queue/priority_queue.h"

TEST(TestPriorityQueueLib, TestInsert) {
  PriorityQueue<int> q;

  q.push(0, 5);
  q.push(1, 9);

  EXPECT_EQ(q.top(), 9);
}

TEST(TestPriorityQueueLib, TestPop) {
  PriorityQueue<int> q;

  q.push(0, 5);
  q.push(1, 9);
  q.push(3, 8);
  q.push(3, 10);
  q.push(3, 11);
  q.push(3, 12);

  q.pop();
  q.pop();

  EXPECT_EQ(q.top(), 11);
}
