// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_tlist_stack/tlist_stack.h"

TEST(TestTListStackLib, CreateDefaultStack) {
  TListStack<int> stack;

  EXPECT_TRUE(stack.is_empty());
  EXPECT_EQ(stack.size(), 0);
}

TEST(TestTListStackLib, CreateStackWithSize) {
  TListStack<int> stack(5);

  for (size_t i = 0; i < 5; i++) {
    stack.push(1);
  }

  EXPECT_TRUE(stack.is_full());
  ASSERT_ANY_THROW(stack.push(0));
}

TEST(TestTListStackLib, CreateStackWithCopy) {
  TListStack<int> stack1;

  stack1.push(20);
  stack1.push(30);

  TListStack<int> stack2(stack1);

  EXPECT_EQ(stack2.size(), 2);
  EXPECT_EQ(stack2.top(), 30);
}

TEST(TestTListStackLib, Top) {
  TListStack<int> stack;

  stack.push(5);

  EXPECT_EQ(stack.top(), 5);

  stack.push(10);

  EXPECT_EQ(stack.top(), 10);
}

TEST(TestTListStackLib, ThrowWhenTopInEmptyStack) {
  TListStack<int> stack;

  EXPECT_TRUE(stack.is_empty());
  EXPECT_ANY_THROW(stack.top());
}

TEST(TestTListStackLib, IsEmptyTrue) {
  TListStack<int> stack;

  EXPECT_TRUE(stack.is_empty());
  EXPECT_EQ(stack.size(), 0);
}

TEST(TestTListStackLib, IsEmptyFalse) {
  TListStack<int> stack;

  stack.push(5);

  EXPECT_FALSE(stack.is_empty());
  EXPECT_EQ(stack.size(), 1);
}

TEST(TestTListStackLib, Push) {
  TListStack<int> stack;

  stack.push(5);
  stack.push(10);

  EXPECT_EQ(stack.top(), 10);
  EXPECT_EQ(stack.size(), 2);
}

TEST(TestTListStackLib, Pop) {
  TListStack<int> stack;

  stack.push(2);
  stack.push(10);

  EXPECT_EQ(stack.size(), 2);

  stack.pop();

  EXPECT_EQ(stack.top(), 2);
  EXPECT_EQ(stack.size(), 1);
}

TEST(TestTListStackLib, ThrowWhenPopInEmptyStack) {
  TListStack<int> stack;

  stack.push(2);

  stack.pop();

  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.pop());
}

TEST(TestTListStackLib, Clear) {
  TListStack<int> stack;

  for (size_t i = 0; i < 5; i++) {
    stack.push(5);
  }

  stack.clear();

  EXPECT_TRUE(stack.is_empty());
  EXPECT_EQ(stack.size(), 0);
}

TEST(TestTListStackLib, PopAndPush) {
  TListStack<int> stack;

  for (size_t i = 0; i < 5; i++) {
    stack.push(i+1);
  }

  EXPECT_EQ(stack.top(), 5);
  EXPECT_EQ(stack.size(), 5);

  stack.pop();
  stack.pop();

  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(stack.size(), 3);

  stack.push(4);
  stack.push(79);

  EXPECT_EQ(stack.size(), 5);
  EXPECT_EQ(stack.top(), 79);
}
