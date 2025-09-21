// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

TEST(TestSphereLib, CreateDefaultSphere) {
  Sphere sphere;
  EXPECT_EQ(sphere.get_x(), 0);
  EXPECT_EQ(sphere.get_y(), 0);
  EXPECT_EQ(sphere.get_z(), 0);
  EXPECT_EQ(sphere.get_rad(), 0);
}

TEST(TestSphereLib, CreateSphereWithParams) {
  Point3D center(5, 10, 15);
  Sphere sphere(center, 7);
  EXPECT_EQ(sphere.get_x(), 5);
  EXPECT_EQ(sphere.get_y(), 10);
  EXPECT_EQ(sphere.get_z(), 15);
  EXPECT_EQ(sphere.get_rad(), 7);
}

TEST(TestSphereLib, CreateSphereWithCopy) {
  Point3D center(3, 6, 9);
  Sphere original(center, 12);
  Sphere copyIt(original);
  EXPECT_EQ(copyIt.get_x(), 3);
  EXPECT_EQ(copyIt.get_y(), 6);
  EXPECT_EQ(copyIt.get_z(), 9);
  EXPECT_EQ(copyIt.get_rad(), 12);
}

TEST(TestSphereLib, SphereNoIntersection) {
  Sphere s1(Point3D(0, 0, 0), 2);
  Sphere s2(Point3D(10, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  EXPECT_EQ(result, without_interaction);
}

TEST(TestSphereLib, SphereExternalTouch) {
  Sphere s1(Point3D(0, 0, 0), 5);
  Sphere s2(Point3D(8, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  EXPECT_EQ(result, touch_out);
}

TEST(TestSphereLib, SphereIntersection) {
  Sphere s1(Point3D(0, 0, 0), 5);
  Sphere s2(Point3D(6, 0, 0), 4);
  loc result = Circle::location_of_the_circles(s1, s2);
  EXPECT_EQ(result, interaction);
}

TEST(TestSphereLib, SphereInternalTouch) {
  Sphere s1(Point3D(0, 0, 0), 5);
  Sphere s2(Point3D(2, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  EXPECT_EQ(result, touch_in);
}

TEST(TestSphereLib, SphereOneInsideAnother) {
  Sphere s1(Point3D(0, 0, 0), 8);
  Sphere s2(Point3D(2, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  EXPECT_EQ(result, entry);
}

TEST(TestSphereLib, SphereIdentical) {
  Sphere s1(Point3D(0, 0, 0), 5);
  Sphere s2(Point3D(0, 0, 0), 5);
  loc result = Circle::location_of_the_circles(s1, s2);
  EXPECT_EQ(result, coincidence);
}
