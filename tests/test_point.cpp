// Copyright 2024 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_point/point.h"

TEST(TestPointLib, CreateDefaultPoint) {
  Point point;

  EXPECT_EQ(0, point.get_x());
  EXPECT_EQ(0, point.get_y());
}

TEST(TestPointLib, CreatePointWithParams) {
  Point point(5, 10);

  EXPECT_EQ(5, point.get_x());
  EXPECT_EQ(10, point.get_y());
}

TEST(TestPointLib, CreatePointWithCopy) {
  Point original(7, 3);
  Point copy(original);

  EXPECT_EQ(7, copy.get_x());
  EXPECT_EQ(3, copy.get_y());
}