// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_double_linked_tlist/double_linked_tlist.h"

TEST(TestDoubleLinkedTList, CreateDefaultList) {
  DoubleLinkedTList<int> list;

  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.head(), nullptr);
  EXPECT_EQ(list.tail(), nullptr);
  EXPECT_EQ(list.size(), 0);
}

TEST(TestDoubleLinkedTList, PushFrontInEmptyList) {
  DoubleLinkedTList<int> list;

  list.push_front(10);

  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.head(), list.tail());
  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.size(), 1);
}

TEST(TestDoubleLinkedTList, PushFrontInList) {
  DoubleLinkedTList<int> list;

  list.push_front(10);
  list.push_front(11);
  list.push_front(12);

  EXPECT_FALSE(list.is_empty());
  EXPECT_NE(list.head(), list.tail());

  EXPECT_EQ(list.head()->value, 12);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.head()->next->next->value, 10);

  EXPECT_EQ(list.tail()->value, 10);
  EXPECT_EQ(list.tail()->prev->value, 11);
  EXPECT_EQ(list.tail()->prev->prev->value, 12);

  EXPECT_EQ(list.head()->prev, nullptr);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestDoubleLinkedTList, PushBackInEmptyList) {
  DoubleLinkedTList<int> list;

  list.push_back(10);

  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.head(), list.tail());
  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.size(), 1);
}

TEST(TestDoubleLinkedTList, PushBackInList) {
  DoubleLinkedTList<int> list;

  list.push_back(10);
  list.push_back(11);
  list.push_back(12);

  EXPECT_FALSE(list.is_empty());
  EXPECT_NE(list.head(), list.tail());

  EXPECT_EQ(list.tail()->value, 12);
  EXPECT_EQ(list.tail()->prev->value, 11);
  EXPECT_EQ(list.tail()->prev->prev->value, 10);

  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.head()->next->next->value, 12);

  EXPECT_EQ(list.tail()->next, nullptr);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestDoubleLinkedTList, ThrowWhenInsertWithNodeInEmptyList) {
  DoubleLinkedTList<int> list;

  DoubleLinkedTList<int>::Node* node = new DoubleLinkedTList<int>::Node(5);

  EXPECT_THROW(list.insert(node, 10), std::logic_error);
  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(TestDoubleLinkedTList, ThrowWhenInsertWithNodeAfterNullptr) {
  DoubleLinkedTList<int> list;

  list.push_back(10);

  EXPECT_THROW(list.insert(nullptr, 10), std::invalid_argument);
  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.head(), list.tail());
  EXPECT_EQ(list.size(), 1);
}

TEST(TestDoubleLinkedTList, ThrowWhenInsertWithNodeInvalidNode) {
  DoubleLinkedTList<int> list;

  list.push_back(1);

  DoubleLinkedTList<int>::Node* node = new DoubleLinkedTList<int>::Node(5);

  EXPECT_THROW(list.insert(node, 8), std::invalid_argument);
  EXPECT_FALSE(list.is_empty());
  EXPECT_EQ(list.size(), 1);
}

TEST(TestDoubleLinkedTList, InsertWithNodeInListTailChange) {
  DoubleLinkedTList<int> list;

  list.push_back(10);

  EXPECT_EQ(list.tail()->value, 10);

  list.insert(list.head(), 11);

  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.tail()->value, 11);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.tail()->prev->value, 10);
  EXPECT_EQ(list.head()->next, list.tail());
  EXPECT_EQ(list.size(), 2);
}

TEST(TestDoubleLinkedTList, InsertWithNodeInList) {
  DoubleLinkedTList<int> list;

  list.push_back(10);
  list.push_back(12);

  list.insert(list.head(), 11);

  EXPECT_EQ(list.head()->value, 10);
  EXPECT_EQ(list.head()->next->value, 11);
  EXPECT_EQ(list.head()->next->next->value, 12);

  EXPECT_EQ(list.tail()->value, 12);
  EXPECT_EQ(list.tail()->prev->value, 11);
  EXPECT_EQ(list.tail()->prev->prev->value, 10);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestDoubleLinkedTList, InsertInEmptyListPos) {
  DoubleLinkedTList<int> list;

  size_t pos = 0;

  list.insert(pos, 100);

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.head()->value, 100);
  EXPECT_EQ(list.head(), list.tail());
}

TEST(TestDoubleLinkedTList, InsertInListFrontPos) {
  DoubleLinkedTList<int> list;

  list.push_back(100);

  size_t pos = 0;

  list.insert(pos, 200);

  EXPECT_EQ(list.head()->value, 200);
  EXPECT_EQ(list.head()->next->value, 100);
  EXPECT_EQ(list.tail()->value, 100);
  EXPECT_EQ(list.tail()->prev, list.head());
  EXPECT_EQ(list.size(), 2);
}

TEST(TestDoubleLinkedTList, InsertInListBackPos) {
  DoubleLinkedTList<int> list;

  list.push_back(100);
  list.push_front(200);

  list.insert(2, 300);

  EXPECT_EQ(list.head()->value, 200);
  EXPECT_EQ(list.head()->next->value, 100);
  EXPECT_EQ(list.head()->next->next->value, 300);
  EXPECT_EQ(list.tail()->value, 300);
  EXPECT_EQ(list.tail()->prev->value, 100);
  EXPECT_EQ(list.tail()->prev->prev->value, 200);
  EXPECT_EQ(list.size(), 3);
}

TEST(TestDoubleLinkedTList, InsertInListPos) {
  DoubleLinkedTList<int> list;

  list.push_back(100);
  list.push_front(200);

  list.push_back(300);

  list.insert(1, 400);

  EXPECT_EQ(list.head()->value, 200);
  EXPECT_EQ(list.head()->next->value, 400);
  EXPECT_EQ(list.head()->next->next->value, 100);
  EXPECT_EQ(list.head()->next->next->next->value, 300);
  EXPECT_EQ(list.tail()->value, 300);
  EXPECT_EQ(list.tail()->prev->value, 100);
  EXPECT_EQ(list.tail()->prev->prev->value, 400);
  EXPECT_EQ(list.tail()->prev->prev->prev->value, 200);
  EXPECT_EQ(list.size(), 4);
}

TEST(TestDoubleLinkedTList, ThrowWhenInsertAtInvalidPosition) {
  DoubleLinkedTList<int> list;
  list.push_back(1);

  EXPECT_THROW(list.insert(2, 10), std::out_of_range);
}

TEST(TestDoubleLinkedTList, CopyConstructorEmptyList) {
  DoubleLinkedTList<int> original;
  DoubleLinkedTList<int> copyIt(original);

  EXPECT_TRUE(copyIt.is_empty());
  EXPECT_EQ(copyIt.size(), 0);
  EXPECT_EQ(copyIt.head(), nullptr);
  EXPECT_EQ(copyIt.tail(), nullptr);
}

TEST(TestDoubleLinkedTList, CopyConstructorNonEmptyList) {
  DoubleLinkedTList<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  DoubleLinkedTList<int> copyIt(original);

  EXPECT_EQ(copyIt.size(), 3);

  EXPECT_EQ(copyIt.head()->value, 1);
  EXPECT_EQ(copyIt.head()->next->value, 2);
  EXPECT_EQ(copyIt.head()->next->next->value, 3);

  EXPECT_EQ(copyIt.tail()->value, 3);
  EXPECT_EQ(copyIt.tail()->prev->value, 2);
  EXPECT_EQ(copyIt.tail()->prev->prev->value, 1);

  EXPECT_NE(original.head(), copyIt.head());
  EXPECT_NE(original.tail(), copyIt.tail());

  EXPECT_EQ(original.size(), 3);
  EXPECT_EQ(original.head()->value, 1);
}

TEST(TestDoubleLinkedTList, Clear) {
  DoubleLinkedTList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.clear();

  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list.head(), nullptr);
  EXPECT_EQ(list.tail(), nullptr);
}
