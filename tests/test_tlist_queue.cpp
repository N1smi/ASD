// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_tlist_queue/tlist_queue.h"

TEST(TestTListQueueLib, CreateDefaultQueue) {
  TListQueue<int> queue;

  EXPECT_EQ(queue.size(), 0);
  EXPECT_TRUE(queue.is_empty());
}

TEST(TestTListQueueLib, CreateQueueWithCopy) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.push(6);
  queue1.push(3);

  TListQueue<int> queue2(queue1);

  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue2.head(), 2);
  EXPECT_EQ(queue2.tail(), 3);
}

TEST(TestTListQueueLib, Head) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.push(6);
  queue1.push(3);

  EXPECT_EQ(queue1.size(), 3);
  EXPECT_EQ(queue1.head(), 2);

  queue1.pop();

  EXPECT_EQ(queue1.size(), 2);
  EXPECT_EQ(queue1.head(), 6);
}

TEST(TestTListQueueLib, ThrowWhenHeadInEmptyQueue) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.pop();

  EXPECT_TRUE(queue1.is_empty());
  EXPECT_THROW(queue1.head(), std::underflow_error);
}

TEST(TestTListQueueLib, Tail) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.push(6);
  queue1.push(3);

  EXPECT_EQ(queue1.tail(), 3);

  queue1.pop();
  queue1.push(30);

  EXPECT_EQ(queue1.tail(), 30);
  EXPECT_EQ(queue1.head(), 6);
  EXPECT_EQ(queue1.size(), 3);
}

TEST(TestTListQueueLib, ThrowWhenTailInEmptyQueue) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.pop();

  EXPECT_TRUE(queue1.is_empty());
  EXPECT_THROW(queue1.tail(), std::underflow_error);
}

TEST(TestTListQueueLib, IsEmptyTrue) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.pop();

  EXPECT_EQ(queue1.size(), 0);
  EXPECT_TRUE(queue1.is_empty());
}

TEST(TestTListQueueLib, IsEmptyFalse) {
  TListQueue<int> queue1;

  queue1.push(2);

  EXPECT_EQ(queue1.size(), 1);
  EXPECT_FALSE(queue1.is_empty());
}

TEST(TestTListQueueLib, Push) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.push(5);

  EXPECT_EQ(queue1.size(), 2);
  EXPECT_EQ(queue1.tail(), 5);

  queue1.push(7);

  EXPECT_EQ(queue1.size(), 3);
  EXPECT_EQ(queue1.tail(), 7);

  queue1.push(8);
  queue1.push(9);

  EXPECT_EQ(queue1.size(), 5);
  EXPECT_EQ(queue1.tail(), 9);
}

TEST(TestTListQueueLib, Pop) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.push(5);
  queue1.push(7);

  EXPECT_EQ(queue1.head(), 2);
  EXPECT_EQ(queue1.size(), 3);

  queue1.pop();

  EXPECT_EQ(queue1.size(), 2);
  EXPECT_EQ(queue1.head(), 5);

  queue1.pop();

  EXPECT_EQ(queue1.size(), 1);
  EXPECT_EQ(queue1.head(), 7);
}

TEST(TestTListQueueLib, ThrowWhenPopInEmptyQueue) {
  TListQueue<int> queue1;

  queue1.push(2);
  queue1.pop();

  EXPECT_EQ(queue1.size(), 0);
  EXPECT_THROW(queue1.pop(), std::underflow_error);
}

TEST(TestTListQueueLib, Clear) {
  TListQueue<int> queue1;

  queue1.push(1);
  queue1.push(2);
  queue1.push(3);

  queue1.clear();

  EXPECT_TRUE(queue1.is_empty());
  EXPECT_THROW(queue1.head(), std::underflow_error);
  EXPECT_THROW(queue1.tail(), std::underflow_error);
  EXPECT_EQ(queue1.size(), 0);
}
