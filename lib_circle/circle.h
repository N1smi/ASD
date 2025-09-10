// Copyright 2025 Smirnov Nikita

#ifndef LIB_CIRCLE_CIRCLE_H_
#define LIB_CIRCLE_CIRCLE_H_

#include "../lib_point/point.h"
#include <iostream>
#include <algorithm>

enum loc {
  coincidence, touch_in, touch_out, without_interaction, entry, interaction
};

class Circle {
  Point _center;
  int _rad;

public:
  Circle();
  Circle(const Circle& other);
  Circle(Point center, int rad);

  int get_x() const {
    return _center.get_x();
  }

  int get_y() const {
    return _center.get_y();
  }

  virtual int get_z() const {
    return 0;
  }

  int get_rad() const {
    return _rad;
  }

  template<typename T>
  static loc location_of_the_circles(const T& first, const T& second) {
    int x1 = first.get_x();
    int x2 = second.get_x();
    int y1 = first.get_y();
    int y2 = second.get_y();
    int z1 = first.get_z();
    int z2 = second.get_z();
    int r1 = first.get_rad();
    int r2 = second.get_rad();

    int dx = x2 - x1;
    int dy = y2 - y1;
    int dz = z2 - z1;
    int distance = dx * dx + dy * dy + dz * dz;

    int R = std::max(r1, r2);
    int r = std::min(r1, r2);

    int sum_rad = (R + r) * (R + r);
    int diff_rad = (R - r) * (R - r);

    if ((x1 == x2) && (y1 == y2) && (z1 == z2) && (r1 == r2)) {
      return coincidence;
    }
    if (distance > sum_rad) {
      return without_interaction;
    }

    if (distance < diff_rad) {
      return entry;
    }

    if (distance == diff_rad) {
      return touch_in;
    }

    if (distance == sum_rad) {
      return touch_out;
    }

    return interaction;
  }
};

#endif  // LIB_CIRCLE_CIRCLE_H_