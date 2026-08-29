// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <string>

#include "../lib_skip_list/skip_list.h"

TEST(TestSkipListLib, CreateDefaulSkipList) {
  SkipList<int, std::string> list;

  EXPECT_TRUE(list.is_empty());
}

TEST(TestSkipListLib, InsertElements) {
  SkipList<int, char> list(8);

  for (size_t i = 0; i <= 14; i++) {
    list.insert(i, '0' + i);
  }

  list.insert(100, '8');
  list.insert(20, '9');

  EXPECT_TRUE(list.contains(10));

  EXPECT_FALSE(list.contains(71));
  EXPECT_FALSE(list.contains(72));

  // list.print();
}

TEST(TestSkipListLib, InsertThrowsThenDuplicateKey) {
  SkipList<int, std::string> list(5);

  list.insert(10, "ten");

  EXPECT_THROW(list.insert(10, "desyat"), std::invalid_argument);

  EXPECT_TRUE(list.contains(10));
}

TEST(TestSkipListLib, IsEmpty) {
  SkipList<int, std::string> list(5);

  EXPECT_TRUE(list.is_empty());

  list.insert(10, "ten");
  EXPECT_FALSE(list.is_empty());
}
