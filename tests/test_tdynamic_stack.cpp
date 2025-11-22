// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_tdynamic_stack/tdynamic_stack.h"

TEST(TestTDynamicStackLib, CreateStackWithSize) {
  TDynamicStack<int> stack(5);

  EXPECT_EQ(stack.size(), 5);
}

TEST(TestTDynamicStackLib, CreateStackWithCopy) {
  TDynamicStack<int> stack1(10);

  stack1.push(20);
  stack1.push(30);

  TDynamicStack<int> stack2(stack1);

  EXPECT_EQ(stack2.size(), 10);
  EXPECT_EQ(stack2.top(), 30);
}

TEST(TestTDynamicStackLib, Top) {
  TDynamicStack<int> stack(5);

  stack.push(5);

  EXPECT_EQ(stack.top(), 5);

  stack.push(10);

  EXPECT_EQ(stack.top(), 10);
}

TEST(TestTDynamicStackLib, ThrowWhenTopInEmptyStack) {
  TDynamicStack<int> stack(5);

  EXPECT_ANY_THROW(stack.top());
}

TEST(TestTDynamicStackLib, IsEmptyTrue) {
  TDynamicStack<int> stack(5);

  EXPECT_TRUE(stack.is_empty());
}

TEST(TestTDynamicStackLib, IsEmptyFalse) {
  TDynamicStack<int> stack(5);

  stack.push(5);

  EXPECT_FALSE(stack.is_empty());
}

TEST(TestTDynamicStackLib, IsFullTrue) {
  TDynamicStack<int> stack(5);

  for (size_t i = 0; i < stack.size(); i++) {
    stack.push(2);
  }

  EXPECT_TRUE(stack.is_full());
}


TEST(TestTDynamicStackLib, IsFullFalse) {
  TDynamicStack<int> stack(5);

  stack.push(2);

  EXPECT_FALSE(stack.is_full());
}

TEST(TestTDynamicStackLib, Push) {
  TDynamicStack<int> stack(5);

  stack.push(5);
  stack.push(10);

  EXPECT_EQ(stack.top(), 10);
}

TEST(TestTDynamicStackLib, ThrowWhenPushInFullStack) {
  TDynamicStack<int> stack(5);

  for (size_t i = 0; i < stack.size(); i++) {
    stack.push(5);
  }

  EXPECT_ANY_THROW(stack.push(2));
}

TEST(TestTDynamicStackLib, Pop) {
  TDynamicStack<int> stack(5);

  stack.push(2);
  stack.push(10);

  stack.pop();

  EXPECT_EQ(stack.top(), 2);
}

TEST(TestTDynamicStackLib, ThrowWhenPopInEmptyStack) {
  TDynamicStack<int> stack(5);

  stack.push(2);

  stack.pop();

  EXPECT_ANY_THROW(stack.pop());
}

TEST(TestTDynamicStackLib, Clear) {
  TDynamicStack<int> stack(5);

  for (size_t i = 0; i < stack.size(); i++) {
    stack.push(5);
  }

  stack.clear();

  EXPECT_TRUE(stack.is_empty());
  EXPECT_EQ(stack.size(), 5);
}

TEST(TestTDynamicStackLib, PopAndPush) {
  TDynamicStack<int> stack(5);

  for (size_t i = 0; i < stack.size(); i++) {
    stack.push(5);
  }

  stack.pop();
  stack.pop();

  stack.push(4);
  stack.push(79);

  EXPECT_EQ(stack.size(),5);
  EXPECT_EQ(stack.top(), 79);
  EXPECT_TRUE(stack.is_full());
}
