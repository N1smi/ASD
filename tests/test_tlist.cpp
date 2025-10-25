// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_tlist/tlist.h"

TEST(TestTList, CreateDefaultList) {
  TList<int> list;

  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.head(), nullptr);
  EXPECT_EQ(list.tail(), nullptr);
}
