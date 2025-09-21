// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"

TEST(TestPoint3DLib, CreateDefaultPoint3D) {
  Point3D point;
  EXPECT_EQ(point.get_x(), 0);
  EXPECT_EQ(point.get_y(), 0);
  EXPECT_EQ(point.get_z(), 0);
}

TEST(TestPoint3DLib, CreatePoint3DWithParams) {
  Point3D point(5, 10, 15);
  EXPECT_EQ(point.get_x(), 5);
  EXPECT_EQ(point.get_y(), 10);
  EXPECT_EQ(point.get_z(), 15);
}

TEST(TestPoint3DLib, CreatePoint3DWithCopy) {
  Point3D original(7, 3, 12);
  Point3D copyIt(original);
  EXPECT_EQ(copyIt.get_x(), 7);
  EXPECT_EQ(copyIt.get_y(), 3);
  EXPECT_EQ(copyIt.get_z(), 12);
}
