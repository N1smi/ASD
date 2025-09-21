// Copyright 2025 Smirnov Nikita

#ifndef LIB_POINT3D_POINT3D_H_
#define LIB_POINT3D_POINT3D_H_

#include "../lib_point/point.h"

class Point3D : public Point {
  int _z;

 public:
  explicit Point3D(int x = 0, int y = 0, int z = 0);
  Point3D(const Point3D& other);

  int get_z() const {
    return _z;
  }
};

#endif  // LIB_POINT3D_POINT3D_H_
