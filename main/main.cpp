// Copyright 2025 Smirnov Nikita

// #define EASY_EXAMPLE
// #define CIRCLE_EXAMPLE
#define MATRIX_CALCULATOR

#include <iostream>

#ifdef EASY_EXAMPLE

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
  Point center1(0, 0);
  Circle circle1(center1, 2);

  Point center2(8, 0);
  Circle circle2(center2, 3);

  loc result = Circle::location_of_the_circles(circle1, circle2);

  std::cout << "Circle 1: the center (" << circle1.get_x()
    << ", " << circle1.get_y()
    << "), radius =" << circle1.get_rad() << std::endl;
  std::cout << "Circle 2: the center ("
    << circle2.get_x() << ", " << circle2.get_y()
    << "), radius =" << circle2.get_rad() << std::endl;

  switch (result) {
  case coincidence:
    std::cout << "Result: the circles match" << std::endl;
    break;
  case touch_in:
    std::cout << "The result: an inner touch" << std::endl;
    break;
  case touch_out:
    std::cout << "Result: external touch" << std::endl;
    break;
  case without_interaction:
    std::cout << "Result: the circles don't interact." << std::endl;
    break;
  case entry:
    std::cout << "Result: one circle inside the other" << std::endl;
    break;
  case interaction:
    std::cout << "Result: the circles intersect at two points"
      << std::endl;
    break;
  }

  return 0;
}
#endif  // CIRCLE_EXAMPLE

#ifdef MATRIX_CALCULATOR

#include <windows.h>
#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/triangle_matrix.h"

template<class T>
void RegularMatrixInput() {
  size_t lines_A, columns_A;
  size_t lines_B, columns_B;

  while (true) {
    std::cout << "Enter the matrix A "
      "(first the number of lines and columns, then the elements) : \n";

    if (!(std::cin >> lines_A >> columns_A)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input for matrix size!\n\n";
      continue;
    }
    break;
  }

  Matrix<T> A(lines_A, columns_A);

  std::cin >> A;

  while (true) {
    std::cout << "Enter the matrix B "
      "(first the number of lines and columns, then the elements): \n";

    if (!(std::cin >> lines_B >> columns_B)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input for matrix size!\n\n";
      continue;
    }
    break;
  }

  Matrix<T> B(lines_B, columns_B);

  std::cin >> B;

  std::cout << "Press Enter to continue...";
  std::cin.ignore();
  std::cin.get();

  MatrixCalculator<Matrix<T>>(A, B);
}

template<class T>
void TriangleMatrixInput() {
  size_t dimension_A, dimension_B;

  while (true) {
    std::cout << "Enter the triangle matrix A "
      "(first the dimension, then the elements): \n";

    if (!(std::cin >> dimension_A)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input for matrix size!\n\n";
      continue;
    }
    break;
  }
  TriangleMatrix<T> A(dimension_A);

  std::cin >> A;
  while (true) {
    std::cout << "Enter the triangle matrix B "
      "(first the dimension, then the elements): \n";

    if (!(std::cin >> dimension_B)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input for matrix size!\n\n";
      continue;
    }
    break;
  }
  TriangleMatrix<T> B(dimension_B);

  std::cin >> B;

  std::cout << "Press Enter to continue...";
  std::cin.ignore();
  std::cin.get();

  MatrixCalculator<TriangleMatrix<T>>(A, B);
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
    std::cout << "3. Subtraction (B - A)\n";
    std::cout << "4. Multiplication (A * B)\n";
    std::cout << "5. Multiplication (B * A)\n";
    std::cout << "0. Back\n";
    std::cout << "Selection: ";

    if (!(std::cin >> TypeOp)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input! Please enter a number.\n";
      Sleep(2000);
      TypeOp = -1;
      continue;
    }

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
        result = B - A;
        std::cout << "\nTHE RESULT OF THE SUBTRACTION:\n";
        std::cout << B;
        std::cout << "\n-\n";
        std::cout << A;
        std::cout << "\n=\n";
        std::cout << result;
        break;

      case 4:
        result = A * B;
        std::cout << "\nTHE RESULT OF THE MULTIPLICATION:\n";
        std::cout << A;
        std::cout << "\n*\n";
        std::cout << B;
        std::cout << "\n=\n";
        std::cout << result;
        break;

      case 5:
        result = B * A;
        std::cout << "\nTHE RESULT OF THE MULTIPLICATION:\n";
        std::cout << B;
        std::cout << "\n*\n";
        std::cout << A;
        std::cout << "\n=\n";
        std::cout << result;
        break;

      case 0:
        system("cls");
        break;
      default:
        std::cout << "Wrong choice! Try again.\n";
        Sleep(2000);
        break;
      }

      if (TypeOp != 0 && TypeOp <= 5 && TypeOp > 0) {
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

typedef int TYPE;

int main() {
  int matrixType;

  while (true) {
    system("cls");
    std::cout << "=== MATRIX CALCULATOR ===\n";
    std::cout << "Select matrix type:\n";
    std::cout << "1. Regular matrices\n";
    std::cout << "2. Triangular matrices\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";

    int matrixType;
    if (!(std::cin >> matrixType)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input! Please enter a number.\n";
      Sleep(2000);
      continue;
    }

    switch (matrixType) {
    case 1:
      system("cls");
      std::cout << "=== MATRIX CALCULATOR ===\n";
      RegularMatrixInput<TYPE>();
      break;
    case 2:
      system("cls");
      std::cout << "=== MATRIX CALCULATOR ===\n";
      TriangleMatrixInput<TYPE>();
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

