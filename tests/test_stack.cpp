// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestStackLib, CreateStackWithSize) {
  Stack<int> stack(5);

  EXPECT_EQ(stack.size(), 5);
}

TEST(TestStackLib, CreateStackWithCopy) {
  Stack<int> stack1(10);

  stack1.push(20);
  stack1.push(30);

  Stack<int> stack2(stack1);

  EXPECT_EQ(stack2.size(), 10);
  EXPECT_EQ(stack2.top(), 30);
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

TEST(TestStackLib, IsEmptyTrue) {
  Stack<int> stack(5);

  EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackLib, IsEmptyFalse) {
  Stack<int> stack(5);

  stack.push(5);

  EXPECT_FALSE(stack.is_empty());
}

TEST(TestStackLib, IsFullTrue) {
  Stack<int> stack(5);

  for (size_t i = 0; i < stack.size(); i++) {
    stack.push(2);
  }

  EXPECT_TRUE(stack.is_full());
}


TEST(TestStackLib, IsFullFalse) {
  Stack<int> stack(5);

  stack.push(2);

  EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, Push) {
  Stack<int> stack(5);

  stack.push(5);
  stack.push(10);

  EXPECT_EQ(stack.top(), 10);
}

TEST(TestStackLib, ThrowWhenPushInFullStack) {
  Stack<int> stack(5);

  for (size_t i = 0; i < stack.size(); i++) {
    stack.push(5);
  }

  EXPECT_ANY_THROW(stack.push(2));
}

TEST(TestStackLib, Pop) {
  Stack<int> stack(5);

  stack.push(2);
  stack.push(10);

  stack.pop();

  EXPECT_EQ(stack.top(), 2);
}

TEST(TestStackLib, ThrowWhenPopInEmptyStack) {
  Stack<int> stack(5);

  stack.push(2);

  stack.pop();

  EXPECT_ANY_THROW(stack.pop());
}

TEST(TestStackLib, Clear) {
  Stack<int> stack(5);

  for (size_t i = 0; i < stack.size(); i++) {
    stack.push(5);
  }

  stack.clear();

  EXPECT_TRUE(stack.is_empty());
  EXPECT_EQ(stack.size(), 5);
}

TEST(TestStackLib, OperatorEqual) {
  Stack<int> stack1(10);

  stack1.push(20);
  stack1.push(30);

  Stack<int> stack2 = stack1;

  EXPECT_EQ(stack2.size(), 10);
  EXPECT_EQ(stack2.top(), 30);

  stack1.push(40);
  EXPECT_EQ(stack2.top(), 30);
}

TEST(TestStackLib, OperatorEqualSelf) {
  Stack<int> stack(5);
  stack.push(10);

  stack = stack;

  EXPECT_EQ(stack.top(), 10);
  EXPECT_FALSE(stack.is_empty());
}
