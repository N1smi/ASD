// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestStackLib, CreateDefaultStack) {
  Stack<int> stack;

  EXPECT_EQ(stack.capacity(), 0);
  EXPECT_EQ(stack.size(), 0);
}

TEST(TestStackLib, CreateStackWithSize) {
  Stack<int> stack(5);

  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stack.capacity(), 5);
}

TEST(TestStackLib, CreateStackWithCopy) {
  Stack<int> stack1(10);
  Stack<int> stack2(stack1);

  EXPECT_EQ(stack2.capacity(), 10);
  EXPECT_EQ(stack2.size(), 0);
}

TEST(TestStackLib, IsEmptyTrue) {
  Stack<int> stack(5);

  EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackLib, IsEmptyFalse) {
  Stack<int> stack(5);
  stack.push(5);

  EXPECT_FALSE(stack.is_empty());
  EXPECT_EQ(stack.size(), 1);
}

TEST(TestStackLib, IsFullTrue) {
  Stack<int> stack(5);
  for (size_t i = 0; i < stack.capacity(); i++) {
    stack.push(2);
  }

  EXPECT_TRUE(stack.is_full());
  EXPECT_EQ(stack.size(), 5);
}

TEST(TestStackLib, IsFullFalse) {
  Stack<int> stack(5);
  stack.push(5);
  stack.push(7);

  EXPECT_FALSE(stack.is_full());
  EXPECT_EQ(stack.size(), 2);
}

TEST(TestStackLib, Push) {
  Stack<int> stack(5);
  stack.push(5);
  stack.push(10);

  EXPECT_EQ(stack.top(), 10);
}

TEST(TestStackLib, ThrowWhenPushInFullStack) {
  Stack<int> stack(5);
  for (size_t i = 0; i < stack.capacity(); i++) {
    stack.push(5);
  }

  EXPECT_ANY_THROW(stack.push(2));
}

TEST(TestStackLib, Top) {
  Stack<int> stack(5);
  stack.push(5);
  EXPECT_EQ(stack.top(), 5);
  stack.push(10);
  EXPECT_EQ(stack.top(), 10);
}

TEST(TestStackLib, ThrowWhenTopInEmptyStack) {
  Stack<int> stack(5);

  EXPECT_ANY_THROW(stack.top());
}

TEST(TestStackLib, Pop) {
  Stack<int> stack(5);
  stack.push(2);
  stack.push(10);
  stack.pop();

  EXPECT_EQ(stack.top(), 2);
  EXPECT_EQ(stack.size(), 1);
}

TEST(TestStackLib, ThrowWhenPopInEmptyStack) {
  Stack<int> stack(5);
  stack.push(2);
  stack.pop();
  EXPECT_ANY_THROW(stack.pop());
}

TEST(TestStackLib, Clear) {
  Stack<int> stack(5);
  for (size_t i = 0; i < stack.capacity(); i++) {
    stack.push(5);
  }
  stack.clear();

  EXPECT_TRUE(stack.is_empty());
  EXPECT_EQ(stack.capacity(), 5);
  EXPECT_EQ(stack.size(), 0);
}
