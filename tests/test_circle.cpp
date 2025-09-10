// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

TEST(TestCircleLib, CreateDefaultCircle) {
  Circle circle;
  EXPECT_EQ(0, circle.get_x());
  EXPECT_EQ(0, circle.get_y());
  EXPECT_EQ(0, circle.get_rad());
}

TEST(TestCircleLib, CreateCircleWithParams) {
  Point center(3, 4);
  Circle circle(center, 5);
  EXPECT_EQ(3, circle.get_x());
  EXPECT_EQ(4, circle.get_y());
  EXPECT_EQ(5, circle.get_rad());
}

TEST(TestCircleLib, CreateCircleWithCopy) {
  Point center(1, 2);
  Circle original(center, 3);
  Circle copy(original);
  EXPECT_EQ(1, copy.get_x());
  EXPECT_EQ(2, copy.get_y());
  EXPECT_EQ(3, copy.get_rad());
}

TEST(TestCircleLib, CirclesNoIntersection) {
  Circle c1(Point(0, 0), 2);
  Circle c2(Point(8, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  EXPECT_EQ(without_interaction, result);
}

TEST(TestCircleLib, CirclesIntersection) {
  Circle c1(Point(0, 0), 5);
  Circle c2(Point(6, 0), 4);
  loc result = Circle::location_of_the_circles(c1, c2);
  EXPECT_EQ(interaction, result);
}

TEST(TestCircleLib, CirclesInternalTouch) {
  Circle c1(Point(0, 0), 5);
  Circle c2(Point(2, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  EXPECT_EQ(touch_in, result);
}

TEST(TestCircleLib, CirclesExternalTouch) {
  Circle c1(Point(0, 0), 5);
  Circle c2(Point(8, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  EXPECT_EQ(touch_out, result);
}

TEST(TestCircleLib, CirclesOneInsideAnother) {
  Circle c1(Point(0, 0), 8);
  Circle c2(Point(2, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  EXPECT_EQ(entry, result);
}

TEST(TestCircleLib, IdenticalCircles) {
  Circle c1(Point(0, 0), 5);
  Circle c2(Point(0, 0), 5);
  loc result = Circle::location_of_the_circles(c1, c2);
  EXPECT_EQ(coincidence, result);
}

