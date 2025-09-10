// Copyright 2025 Smirnov Nikita

#include "../lib_point3d/point3d.h"

Point3D::Point3D(int x, int y, int z) : Point(x, y), _z(z) {}

Point3D::Point3D(const Point3D& other) : Point(other.get_x(), other.get_y()), _z(other._z) {}