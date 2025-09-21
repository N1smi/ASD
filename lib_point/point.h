// Copyright 2025 Smirnov Nikita

#ifndef LIB_POINT_POINT_H_
#define LIB_POINT_POINT_H_

class Point {
  int _x;
  int _y;

 public:
  Point(int x = 0, int y = 0);

  Point(const Point& other);

  void set_x(int x) {
    _x = x;
  }

  void set_y(int y) {
    _y = y;
  }

  int get_x() const {
    return _x;
  }

  int get_y() const {
    return _y;
  }
};

#endif  // LIB_POINT_POINT_H_
