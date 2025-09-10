// Copyright 2025 Smirnov Nikita

#include "../lib_point/point.h"

Point::Point(int x, int y) {
  _x = x;
  _y = y;
}

Point::Point(const Point& other) {
  _x = other._x;
  _y = other._y;
}