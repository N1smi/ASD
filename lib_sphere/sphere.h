// Copyright 2025 Smirnov Nikita

#ifndef LIB_SPHERE_SPHERE_H_
#define LIB_SPHERE_SPHERE_H_

#include "../lib_circle/circle.h"
#include "../lib_point3d/point3d.h"

class Sphere : public Circle {
  Point3D _center;

 public:
  Sphere() : Circle(), _center(0, 0, 0) {}
  Sphere(Point3D center, int rad)
    : Circle(Point(center.get_x(), center.get_y()), rad), _center(center) {
  }

  int get_z() const override { return _center.get_z(); };
};

#endif  // LIB_SPHERE_SPHERE_H_
