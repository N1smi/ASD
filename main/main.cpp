// Copyright 2025 Smirnov Nikita

//#define EASY_EXAMPLE
//#define CIRCLE_EXAMPLE
#define MATRIX_CALCULATOR

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

#ifdef MATRIX_CALCULATOR

#include <iostream>
#include <windows.h>
#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/triangle_matrix.h"

template<class T>
void MatrixInput() {
  int matrixType;

  while (true) {
    system("cls");
    std::cout << "=== MATRIX CALCULATOR ===\n";
    std::cout << "Select matrix type:\n";
    std::cout << "1. Regular matrices\n";
    std::cout << "2. Triangular matrices\n";
    std::cout << "Choice: ";
    std::cin >> matrixType;
    if (matrixType == 1 || matrixType == 2) {
      break;
    } else {
      std::cout << "Wrong choice. Try again!\n";
      Sleep(2000);
    }
  }

  system("cls");

  std::cout << "=== MATRIX CALCULATOR ===\n";

  if (matrixType == 1) {
    Matrix<T> A, B;

    std::cout << "Enter the matrix A (first the number of lines and columns, then the elements): \n";
    std::cin >> A;

    std::cout << "Enter the matrix B (first the number of lines and columns, then the elements): \n";
    std::cin >> B;

    system("pause");

    MatrixCalculator<Matrix<T>>(A, B);

  } else {
    TriangleMatrix<T> A, B;

    std::cout << "Enter the triangle matrix A (first the dimension, then the elements): \n";
    std::cin >> A;

    std::cout << "Enter the triangle matrix B (first the dimension, then the elements): \n";
    std::cin >> B;

    system("pause");

    MatrixCalculator<TriangleMatrix<T>>(A, B);
  }
}

template<class Q>
void MatrixCalculator(Q& A, Q& B) {
  std::cout << "=== MATRIX CALCULATOR ===\n";

  int TypeOp;
  Q result;

  do {
    system("cls");
    std::cout << "=== MATRIX CALCULATOR ===\n";
    std::cout << "Select an operation:\n";
    std::cout << "1. Addition (A + B)\n";
    std::cout << "2. Subtraction (A - B)\n";
    std::cout << "3. Multiplication (A * B)\n";
    std::cout << "0. Back\n";
    std::cout << "Selection: ";
    std::cin >> TypeOp;

    try {
      switch (TypeOp) {
      case 1:
        result = A + B;
        std::cout << "\nTHE RESULT OF THE ADDITION:\n";
        std::cout << A;
        std::cout << "\n+\n";
        std::cout << B;
        std::cout << "\n=\n";
        std::cout << result;
        break;

      case 2:
        result = A - B;
        std::cout << "\nTHE RESULT OF THE SUBTRACTION:\n";
        std::cout << A;
        std::cout << "\n-\n";
        std::cout << B;
        std::cout << "\n=\n";
        std::cout << result;
        break;

      case 3:
        result = A * B;
        std::cout << "\nTHE RESULT OF THE MULTIPLICATION:\n";
        std::cout << A;
        std::cout << "\n*\n";
        std::cout << B;
        std::cout << "\n=\n";
        std::cout << result;
        break;

      case 0:
        system("cls");
        break;

      default:
        std::cout << "\nWrong choice! Try again.\n";
        break;
      }

      if (TypeOp != 0) {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
      }

    }
    catch (const std::exception& e) {
      std::cout << "Error: " << e.what() << "\n";
      std::cout << "Press Enter to continue...";
      std::cin.ignore();
      std::cin.get();
    }
  } while (TypeOp != 0);


}

int main() {
  while (true) {
    std::cout << "=== MATRIX CALCULATOR ===\n";
    std::cout << "Select the data type:\n";
    std::cout << "1. int\n";
    std::cout << "2. double\n";
    std::cout << "3. float\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";

    int TypeChoice;
    std::cin >> TypeChoice;

    switch (TypeChoice) {
    case 1:
      MatrixInput<int>();
      break;
    case 2:
      MatrixInput<double>();
      break;
    case 3:
      MatrixInput<float>();
      break;
    case 0:
      return 0;
    default:
      std::cout << "Wrong choice. Try again!\n";
      Sleep(2000);
      system("cls");
      break;
    }
  }

  return 0;

}

#endif  // MATRIX_CALCULATOR

