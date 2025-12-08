//  Copyright 2025 Smirnov Nikita

// #define EASY_EXAMPLE
// #define CIRCLE_EXAMPLE
// #define MATRIX_CALCULATOR
#define ARITHMETIC_CALCULATOR
#include <iostream>
#include <iomanip>

#ifdef EASY_EXAMPLE

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

#ifdef ARITHMETIC_CALCULATOR

#include <string>
#include <map>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "../lib_expression/expression.h"
#include "../lib_tvector/tvector.h"


struct ExpressionEntry {
  int id;
  std::string expr_str;
  Expression* expr;
  std::map<std::string, double> variables;

  ExpressionEntry() : id(0), expr_str(""), expr(nullptr) {}

  ExpressionEntry(int _id, const std::string& str)
    : id(_id), expr_str(str), expr(nullptr) {
    expr = new Expression(str);
  }

  ExpressionEntry(const ExpressionEntry& other)
    : id(other.id),
    expr_str(other.expr_str),
    expr(other.expr ? new Expression(*(other.expr)) : nullptr),
    variables(other.variables) {
  }

  ExpressionEntry& operator=(const ExpressionEntry& other) {
    if (this != &other) {
      delete expr;

      id = other.id;
      expr_str = other.expr_str;
      expr = other.expr ? new Expression(*(other.expr)) : nullptr;
      variables = other.variables;
    }
    return *this;
  }

  TVector<std::string> getVariableNames() const {
    if (expr && expr->isValid()) {
      return expr->getVariables();
    }
    return TVector<std::string>();
  }

  ~ExpressionEntry() {
    delete expr;
  }
};

void print_table(const TVector<ExpressionEntry>& expressions) {
  std::cout <<std::string(50, '=');
  std::cout << "ARITHMETIC CALCULATOR";
  std::cout << std::string(49, '=') << "\n";

  std::cout << "+" << std::string(118, '-') << "+\n";

  std::cout << "| " << std::left << std::setw(6) << "ID"
    << "| " << std::left << std::setw(50) << "EXPRESSION"
    << "| " << std::left << std::setw(57) << "VARIABLES VALUES"
    << "|\n";

  std::cout << "+" << std::string(118, '-') << "+\n";

  if (expressions.size() == 0) {
    std::cout << "| " << std::left << std::setw(116)
      << "Without Expression" << " |\n";
  } else {
    for (int i = 0; i < expressions.size(); i++) {
      const auto& entry = expressions[i];

      std::string expr_display = entry.expr_str;
      if (expr_display.length() > 48) {
        expr_display = expr_display.substr(0, 45) + "...";
      }

      std::string vars_str;

      if (entry.variables.size() == 0) {
        TVector<std::string> var_names = entry.getVariableNames();

        for (int j = 0; j < var_names.size(); j++) {
          if (!vars_str.empty()) vars_str += ", ";
          vars_str += var_names[j] + " = ?";
        }

        if (vars_str.empty()) vars_str = "No variables";
      } else {
        for (const auto& var_pair : entry.variables) {
          if (!vars_str.empty()) vars_str += ", ";
          vars_str += var_pair.first + " = " +
            (std::ostringstream{} << std::fixed << std::setprecision(2)
              << var_pair.second).str();
          if (vars_str.length() > 50) {
            vars_str = vars_str.substr(0, 47) + "...";
            break;
          }
        }
      }

      std::cout << "| " << std::left << std::setw(6) << entry.id
        << "| " << std::left << std::setw(50) << expr_display
        << "| " << std::left << std::setw(57) << vars_str
        << "|\n";
    }
  }

  std::cout << "+" << std::string(118, '-') << "+\n\n";
}

void create_expression(TVector<ExpressionEntry>& expressions, int& next_id) {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "\nInput expression: ";
  std::string expr;
  std::getline(std::cin, expr);

  try {
    ExpressionEntry new_entry(next_id++, expr);
    expressions.push_back(new_entry);
  } catch (const PositionException& e) {
    next_id--;
    std::cout << std::string(18, ' ');

    size_t error_pos = e.getPosition() - 1;
    for (size_t i = 0; i < expr.length(); i++) {
      if (i == error_pos) {
        std::cout << "^";
      } else {
        std::cout << " ";
      }
    }
    std::cout << "\n" << e.what() << "\n";
  }
}

void delete_expression(TVector<ExpressionEntry>& expressions) {
  std::cout << "\nInput ID expression: ";
  int id;
  std::cin >> id;

  for (int i = 0; i < expressions.size(); i++) {
    if (expressions[i].id == id) {
      expressions.erase(i);
      return;
    }
  }

  std::cout << "\nExpression with ID " << id << " not exist.\n";
}

void set_variables(TVector<ExpressionEntry>& expressions) {
  std::cout << "\nInput ID expression: ";
  int id;
  std::cin >> id;

  for (int i = 0; i < expressions.size(); i++) {
    if (expressions[i].id == id) {
      auto& entry = expressions[i];

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << "\nExpression: " << entry.expr_str << "\n";

      auto var_names = entry.getVariableNames();
      if (var_names.size() == 0) {
        std::cout << "\nNo variables in expression.\n";
        return;
      }

      for (int j = 0; j < var_names.size(); j++) {
        const std::string& var_name = var_names[j];

        while (true) {
          std::cout << var_name << ": ";

          std::string value_str;
          std::getline(std::cin, value_str);


          try {
            double value = std::stod(value_str);
            entry.variables[var_name] = value;
            break;
          }
          catch (...) {
            std::cout << "Error: invalid value! \n";
          }
        }
      }

      return;
    }
  }

  std::cout << "\nExpression with ID " << id << " not exist.\n";
}

void calculate_expression(TVector<ExpressionEntry>& expressions) {
  std::cout << "\nInput ID expression: ";
  int id;
  std::cin >> id;

  for (int i = 0; i < expressions.size(); i++) {
    if (expressions[i].id == id) {
      const auto& entry = expressions[i];

      try {
        double result = entry.expr->calculate(entry.variables);
        std::cout << "\nResult: " << result << "\n";
      }
      catch (const std::exception& e) {
        std::cout << "\nCalculation error: " << e.what() << "\n";
      }
      return;
    }
  }

  std::cout << "\nExpression with ID " << id << " not exist.\n";
}

int main() {
  TVector<ExpressionEntry> expressions;
  int next_id = 1;
  int choice = 0;

  ExpressionEntry entry1(next_id++, "x + y * (x^2 - 16)");
  entry1.variables["x"] = 5;
  entry1.variables["y"] = 10;
  expressions.push_back(entry1);

  ExpressionEntry entry2(next_id++, "x_1 * sin(y + 7) + y * (~|x_2 - 17| + 23)"
    "+ 123456");
  expressions.push_back(entry2);

  while (true) {
    system("cls");

    print_table(expressions);

    std::cout << "Menu:\n";
    std::cout << "1. Create a new expression\n";
    std::cout << "2. Delete an expression\n";
    std::cout << "3. Set variables\n";
    std::cout << "4. Calculate the value of the expression\n";
    std::cout << "5. Exit\n";
    std::cout << "\nYour choice: ";

    std::cin >> choice;

    switch (choice) {
    case 1:
      create_expression(expressions, next_id);
      break;
    case 2:
      delete_expression(expressions);
      break;
    case 3:
      set_variables(expressions);
      break;
    case 4:
      calculate_expression(expressions);
      break;
    case 5:
      return 0;
    default:
      std::cout << "\nWrong choice\n";
    }

    if (choice != 5) {
      system("pause");
    }

  }
  return 0;
}

#endif  // ARITHMETIC_CALCULATOR
