// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_tdynamic_queue/tdynamic_queue.h"

TEST(TestTDynamicQueueLib, CreateQueueWithSize) {
  TDynamicQueue<int> queue(5);

  EXPECT_EQ(queue.size(), 5);
}

TEST(TestTDynamicQueueLib, CreateQueueWithCopy) {
  TDynamicQueue<int> queue1(10);

  queue1.push(2);
  queue1.push(6);
  queue1.push(3);

  TDynamicQueue<int> queue2(queue1);

  EXPECT_EQ(queue2.size(), 10);
  EXPECT_EQ(queue2.head(), 2);
  EXPECT_EQ(queue2.tail(), 3);
}

TEST(TestTDynamicQueueLib, Head) {
  TDynamicQueue<int> queue1(10);

  queue1.push(2);
  queue1.push(6);
  queue1.push(3);

  EXPECT_EQ(queue1.head(), 2);
}

TEST(TestTDynamicQueueLib, ThrowWhenHeadInEmptyQueue) {
  TDynamicQueue<int> queue1(10);

  queue1.push(2);
  queue1.pop();

  EXPECT_THROW(queue1.head(), std::underflow_error);
}

TEST(TestTDynamicQueueLib, Tail) {
  TDynamicQueue<int> queue1(5);

  queue1.push(2);
  queue1.push(6);
  queue1.push(3);
  queue1.push(10);
  queue1.push(20);

  EXPECT_EQ(queue1.tail(), 20);

  queue1.pop();
  queue1.push(30);

  EXPECT_EQ(queue1.tail(), 30);
  EXPECT_EQ(queue1.head(), 6);
}

TEST(TestTDynamicQueueLib, ThrowWhenTailInEmptyQueue) {
  TDynamicQueue<int> queue1(10);

  queue1.push(2);
  queue1.pop();

  EXPECT_THROW(queue1.tail(), std::underflow_error);
}

TEST(TestTDynamicQueueLib, IsEmptyTrue) {
  TDynamicQueue<int> queue1(10);

  queue1.push(2);
  queue1.pop();

  EXPECT_TRUE(queue1.is_empty());
}

TEST(TestTDynamicQueueLib, IsEmptyFalse) {
  TDynamicQueue<int> queue1(10);

  queue1.push(2);

  EXPECT_FALSE(queue1.is_empty());
}

TEST(TestTDynamicQueueLib, IsFullTrue) {
  TDynamicQueue<int> queue1(5);

  queue1.push(2);
  queue1.push(2);
  queue1.push(2);
  queue1.push(2);
  queue1.push(2);

  EXPECT_TRUE(queue1.is_full());
}

TEST(TestTDynamicQueueLib, IsFullFalse) {
  TDynamicQueue<int> queue1(10);

  queue1.push(2);
  queue1.push(5);

  EXPECT_FALSE(queue1.is_full());
}

TEST(TestTDynamicQueueLib, Push) {
  TDynamicQueue<int> queue1(5);

  queue1.push(2);
  queue1.push(5);

  EXPECT_EQ(queue1.tail(), 5);

  queue1.push(7);

  EXPECT_EQ(queue1.tail(), 7);

  queue1.push(8);
  queue1.push(9);

  EXPECT_EQ(queue1.tail(), 9);
}

TEST(TestTDynamicQueueLib, ThrowWhenPushInFullQueue) {
  TDynamicQueue<int> queue1(5);

  for (size_t i = 0; i < queue1.size(); i++) {
    queue1.push(1);
  }

  EXPECT_THROW(queue1.push(1), std::overflow_error);
}

TEST(TestTDynamicQueueLib, Pop) {
  TDynamicQueue<int> queue1(5);

  queue1.push(2);
  queue1.push(5);
  queue1.push(7);

  queue1.pop();

  EXPECT_EQ(queue1.head(), 5);

  queue1.pop();

  EXPECT_EQ(queue1.head(), 7);
}

TEST(TestTDynamicQueueLib, ThrowWhenPopInEmptyQueue) {
  TDynamicQueue<int> queue1(5);

  queue1.push(2);
  queue1.pop();

  EXPECT_THROW(queue1.pop(), std::underflow_error);
}

TEST(TestTDynamicQueueLib, Clear) {
  TDynamicQueue<int> queue1(5);

  queue1.push(1);
  queue1.push(2);
  queue1.push(3);

  queue1.clear();

  EXPECT_TRUE(queue1.is_empty());
  EXPECT_THROW(queue1.head(), std::underflow_error);
  EXPECT_THROW(queue1.tail(), std::underflow_error);
  EXPECT_EQ(queue1.size(), 5);
}

TEST(TestTDynamicQueueLib, CircularBehavior) {
  TDynamicQueue<int> queue(3);

  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.pop();
  queue.push(4);

  EXPECT_EQ(queue.head(), 2);
  EXPECT_EQ(queue.tail(), 4);

  queue.pop();
  queue.push(5);

  EXPECT_EQ(queue.head(), 3);
  EXPECT_EQ(queue.tail(), 5);
}

TEST(TestTDynamicQueueLib, BoundaryConditions) {
  TDynamicQueue<int> queue(1);

  EXPECT_TRUE(queue.is_empty());
  EXPECT_FALSE(queue.is_full());

  queue.push(42);
  EXPECT_TRUE(queue.is_full());
  EXPECT_EQ(queue.head(), 42);
  EXPECT_EQ(queue.tail(), 42);

  queue.pop();
  EXPECT_TRUE(queue.is_empty());
}
