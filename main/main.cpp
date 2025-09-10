// Copyright 2025 Smirnov Nikita

//#define EASY_EXAMPLE
#define CIRCLE_EXAMPLE

#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE

#ifdef CIRCLE_EXAMPLE

#include "../lib_circle/circle.h"

int main() {
  setlocale(LC_ALL, "rus");
  Point center1(0, 0);
  Circle circle1(center1, 2);

  Point center2(8, 0);
  Circle circle2(center2, 3);

  loc result = Circle::location_of_the_circles(circle1, circle2);

  std::cout << "Окружность 1: центр (" << circle1.get_x() << ", " << circle1.get_y()
    << "), радиус = " << circle1.get_rad() << std::endl;
  std::cout << "Окружность 2: центр (" << circle2.get_x() << ", " << circle2.get_y()
    << "), радиус = " << circle2.get_rad() << std::endl;

  switch (result) {
  case coincidence:
    std::cout << "Результат: окружности совпадают" << std::endl;
    break;
  case touch_in:
    std::cout << "Результат: внутреннее касание" << std::endl;
    break;
  case touch_out:
    std::cout << "Результат: внешнее касание" << std::endl;
    break;
  case without_interaction:
    std::cout << "Результат: окружности не взаимодействуют" << std::endl;
    break;
  case entry:
    std::cout << "Результат: одна окружность внутри другой" << std::endl;
    break;
  case interaction:
    std::cout << "Результат: окружности пересекаются в двух точках" << std::endl;
    break;
  }

  return 0;
}
#endif  // CIRCLE_EXAMPLE

