// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_tlist/tlist.h"

TEST(TestTList, CreateDefaultList) {
  TList<int> list;

  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.head(), nullptr);
  EXPECT_EQ(list.tail(), nullptr);
  EXPECT_EQ(list.size(), 0);
}

TEST(TestTList, PushFrontInEmptyList) {
  TList<int> list;

  list.push_front(10);

  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.head(), list.tail());
  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.size(), 1);
}

TEST(TestTList, PushFrontInList) {
  TList<int> list;

  list.push_front(10);
  list.push_front(11);
  list.push_front(12);

  EXPECT_FALSE(list.is_empty());
  EXPECT_NE(list.head(), list.tail());
  EXPECT_EQ(list.head()->value, 12);
  EXPECT_EQ(list.tail()->value, 10);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.head()->next->next->value, 10);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestTList, PushBackInEmptyList) {
  TList<int> list;

  list.push_back(10);

  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.head(), list.tail());
  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.size(), 1);
}

TEST(TestTList, PushBackInList) {
  TList<int> list;

  list.push_back(10);
  list.push_back(11);
  list.push_back(12);

  EXPECT_FALSE(list.is_empty());
  EXPECT_NE(list.head(), list.tail());
  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.head()->next->next->value, 12);
  EXPECT_EQ(list.tail()->value, 12);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestTList, ThrowWhenInsertWithNodeInEmptyList) {
  TList<int> list;

  Node<int>* node = new Node<int>(5);

  EXPECT_THROW(list.insert(node, 10), std::logic_error);
  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(TestTList, ThrowWhenInsertWithNodeAfterNullptr) {
  TList<int> list;

  list.push_back(10);

  EXPECT_THROW(list.insert(nullptr, 10), std::invalid_argument);
  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.head(), list.tail());
  EXPECT_EQ(list.size(), 1);
}

TEST(TestTList, InsertWithNodeInList) {
  TList<int> list;

  list.push_back(10);
  list.push_back(12);

  list.insert(list.head(), 11);

  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.head()->next->next->value, 12);
  EXPECT_EQ(list.tail()->value, 12);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestTList, InsertWithNodeInListTailChange) {
  TList<int> list;

  list.push_back(10);

  list.insert(list.head(), 11);

  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.tail()->value, 11);
  EXPECT_EQ(list.size(), 2);
}

TEST(TestTList, ThrowWhenInsertWithNodeInvalidNode) {
  TList<int> list;

  list.push_back(1);

  Node<int>* node = new Node<int>(5);

  EXPECT_THROW(list.insert(node,8), std::invalid_argument);
  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.size(), 1);
}

TEST(TestTList, InsertInEmptyListPos) {
  TList<int> list;

  size_t pos = 0;

  list.insert(pos, 100);

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.head()->value, 100);
  EXPECT_EQ(list.tail()->value, 100);
  EXPECT_EQ(list.head(), list.tail());
}

TEST(TestTList, InsertInListFrontPos) {
  TList<int> list;

  list.push_back(100);

  size_t pos = 0;

  list.insert(pos, 200);

  EXPECT_EQ(list.head()->value, 200);
  EXPECT_EQ(list.head()->next->value, 100);
  EXPECT_EQ(list.tail()->value, 100);
  EXPECT_EQ(list.size(), 2);
  EXPECT_NE(list.head(), list.tail());
}

TEST(TestTList, InsertInListBackPos) {
  TList<int> list;

  list.push_back(100);
  list.push_front(200);

  list.insert(2, 300);

  EXPECT_EQ(list.head()->value, 200);
  EXPECT_EQ(list.head()->next->value, 100);
  EXPECT_EQ(list.head()->next->next->value, 300);
  EXPECT_EQ(list.tail()->value, 300);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestTList, InsertInListPos) {
  TList<int> list;

  list.push_back(100);
  list.push_front(200);

  list.push_back(300);

  list.insert(1, 400);

  EXPECT_EQ(list.head()->value, 200);
  EXPECT_EQ(list.head()->next->value, 400);
  EXPECT_EQ(list.head()->next->next->value, 100);
  EXPECT_EQ(list.head()->next->next->next->value, 300);
  EXPECT_EQ(list.size(), 4);
}

TEST(TestTList, ThrowWhenInsertAtInvalidPosition) {
  TList<int> list;
  list.push_back(1);

  EXPECT_THROW(list.insert(2, 10), std::out_of_range);
}

TEST(TestTList, CopyConstructorEmptyList) {
  TList<int> original;
  TList<int> copyIt(original);

  EXPECT_TRUE(copyIt.is_empty());
  EXPECT_EQ(copyIt.size(), 0);
  EXPECT_EQ(copyIt.head(), nullptr);
  EXPECT_EQ(copyIt.tail(), nullptr);
}

TEST(TestTList, CopyConstructorNonEmptyList) {
  TList<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  TList<int> copyIt(original);

  EXPECT_EQ(copyIt.size(), 3);
  EXPECT_EQ(copyIt.head()->value, 1);
  EXPECT_EQ(copyIt.head()->next->value, 2);
  EXPECT_EQ(copyIt.tail()->value, 3);

  EXPECT_NE(original.head(), copyIt.head());
  EXPECT_NE(original.tail(), copyIt.tail());

  EXPECT_EQ(original.size(), 3);
  EXPECT_EQ(original.head()->value, 1);
}

TEST(TestTList, ThrowWhenPopBackInEmptyList) {
  TList<int> list;

  EXPECT_THROW(list.pop_back(), std::logic_error);
  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(TestTList, PopBackFromSingleElement) {
  TList<int> list;

  list.push_back(5);
  list.pop_back();

  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.head(), nullptr);
  EXPECT_EQ(list.tail(), nullptr);
  EXPECT_EQ(list.size(), 0);
}

TEST(TestTList, PopBack) {
  TList<int> list;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_back();

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.head()->value, 1);
  EXPECT_EQ(list.tail()->value, 2);
  EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestTList, ThrowWhenPopFrontInEmptyList) {
  TList<int> list;

  EXPECT_THROW(list.pop_front(), std::logic_error);
  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(TestTList, PopFrontFromSingleElement) {
  TList<int> list;

  list.push_back(5);
  list.pop_front();

  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.head(), nullptr);
  EXPECT_EQ(list.tail(), nullptr);
  EXPECT_EQ(list.size(), 0);
}

TEST(TestTList, PopFront) {
  TList<int> list;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_front();

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.head()->value, 2);
  EXPECT_EQ(list.tail()->value, 3);
}

TEST(TestTList, ThrowWhenEraseWithNodeNullNode) {
  TList<int> list;

  list.push_back(1);

  EXPECT_THROW(list.erase(nullptr), std::invalid_argument);
}

TEST(TestTList, ThrowWhenEraseWithNodeInEmptyList) {
  TList<int> list;

  Node<int>* node = new Node<int>(5);

  EXPECT_THROW(list.erase(node), std::logic_error);
  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(TestTList, ThrowWhenEraseWithNodeInvalidNode) {
  TList<int> list;

  list.push_back(1);

  Node<int>* node = new Node<int>(5);

  EXPECT_THROW(list.erase(node), std::invalid_argument);
  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.size(), 1);
}

TEST(TestTList, EraseWithNodeHead) {
  TList<int> list;
  list.push_back(1);
  list.push_back(2);

  list.erase(list.head());

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.head()->value, 2);
  EXPECT_EQ(list.tail()->value, 2);
}

TEST(TestTList, EraseWithNodeTail) {
  TList<int> list;
  list.push_back(1);
  list.push_back(2);

  list.erase(list.tail());

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.head()->value, 1);
  EXPECT_EQ(list.tail()->value, 1);
}

TEST(TestTList, EraseWithNodeMiddle) {
  TList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.erase(list.head()->next);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.head()->value, 1);
  EXPECT_EQ(list.head()->next->value, 3);
  EXPECT_EQ(list.tail()->value, 3);
}

TEST(TestTList, EraseThrowsOnInvalidPosition) {
  TList<int> list;
  list.push_back(1);

  EXPECT_THROW(list.erase(1), std::out_of_range);

  EXPECT_THROW(list.erase(5), std::out_of_range);

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.head()->value, 1);
}

TEST(TestTList, EraseWithPosThrowsOnEmptyList) {
  TList<int> list;
  size_t pos = 0;

  EXPECT_THROW(list.erase(pos), std::out_of_range);
  EXPECT_TRUE(list.is_empty());
}

TEST(TestTList, EraseWithPosFront) {
  TList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  size_t pos = 0;

  list.erase(pos);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.head()->value, 2);
  EXPECT_EQ(list.tail()->value, 3);
  EXPECT_EQ(list.head()->next->value, 3);
}

TEST(TestTList, EraseWithPosBack) {
  TList<int> list;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.erase(2);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.head()->value, 1);
  EXPECT_EQ(list.tail()->value, 2);
  EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestTList, EraseWithPosMiddle) {
  TList<int> list;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  list.erase(2);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.head()->value, 1);
  EXPECT_EQ(list.head()->next->value, 2);
  EXPECT_EQ(list.head()->next->next->value, 4);
  EXPECT_EQ(list.tail()->value, 4);
}
