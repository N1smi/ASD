// Copyright 2025 Smirnov Nikita

#include<random>
#include <string>
#include <cstdio>
#include "../lib_algorithm/algorithm.h"

int find_local_min(const Matrix<int>& matrix) {
  if (matrix.get_lines() != matrix.get_columns()) {
    throw std::logic_error("Matrix lines and columns don't match!");
  }

  size_t dimension = matrix.get_lines();

  if (dimension == 0) {
    throw std::logic_error("Matrix is empty!");
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> dis(0, dimension - 1);

  size_t i = dis(gen);
  size_t j = dis(gen);

  while (true) {
    size_t new_i = i, new_j = j;

    find_best_neighbor(matrix, i, j, new_i, new_j);

    if (new_i == i && new_j == j) return matrix[i][j];

    i = new_i;
    j = new_j;
  }
}

void find_best_neighbor(const Matrix<int>& matrix, size_t i, size_t j,
  size_t& new_i, size_t& new_j) {
  size_t dimension = matrix.get_lines();

  if (i > 0 && matrix[i - 1][j] < matrix[new_i][new_j]) {
    new_i = i - 1;
    new_j = j;
  }

  if (i < dimension - 1 && matrix[i + 1][j] < matrix[new_i][new_j]) {
    new_i = i + 1;
    new_j = j;
  }

  if (j > 0 && matrix[i][j - 1] < matrix[new_i][new_j]) {
    new_i = i;
    new_j = j - 1;
  }

  if (j < dimension - 1 && matrix[i][j + 1] < matrix[new_i][new_j]) {
    new_i = i;
    new_j = j + 1;
  }
}

bool check_breckets(const std::string& str) {
  TDynamicStack<char> checker(str.length());

  for (char c : str) {
    if ((c != '(') && (c != ')')
      && (c != '{') && (c != '}')
      && (c != '[') && (c != ']')) {
      continue;
    }
    if (c == '(' || c == '[' || c == '{') {
      checker.push(c);
    } else {
      if (checker.is_empty()) {
        return false;
      }

      char top = checker.top();

      if ((c == ')' && top != '(') ||
        (c == ']' && top != '[') ||
        (c == '}' && top != '{')) {
        return false;
      }

      checker.pop();
    }
  }

  return checker.is_empty();
}

void read_expression(const std::string& expression) {
  TDynamicStack<char> brackets(expression.length());

  bool expect_operand = true;

  for (size_t i = 0; i < expression.length(); i++) {
    char c = expression[i];

    if (c == ' ') {
      continue;
    }

    if (c == '(' || c == '[' || c == '{') {
      brackets.push(c);
      expect_operand = true;
      continue;
    }

    if (c == ')' || c == ']' || c == '}') {
      if (brackets.is_empty()) {
        throw std::invalid_argument("Missing opened bracket");
      }

      char top = brackets.top();
      if ((c == ')' && top != '(') ||
        (c == ']' && top != '[') ||
        (c == '}' && top != '{')) {
        throw std::invalid_argument("Missing opened bracket");
      }

      brackets.pop();
      expect_operand = false;
      continue;
    }

    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
      if (expect_operand) {
        throw std::invalid_argument("Missing first operand in operation "
          + std::string(1, c));
      }

      bool has_operand_after = false;
      for (size_t j = i + 1; j < expression.length(); j++) {
        if (expression[j] == ' ') continue;
        if (std::isalnum(expression[j]) || expression[j] == '(' ||
          expression[j] == '[' || expression[j] == '{') {
          has_operand_after = true;
          break;
        }

        if (expression[j] == '+' || expression[j] == '-' ||
          expression[j] == '*' || expression[j] == '/' ||
          expression[j] == '^' || expression[j] == ')' ||
          expression[j] == ']' || expression[j] == '}') {
          break;
        }
      }
      if (!has_operand_after) {
        throw std::invalid_argument("Missing second operand in operation "
          + std::string(1, c));
      }

      expect_operand = true;
      continue;
    }

    if (std::isalnum(c)) {
      if (!expect_operand) {
        throw std::invalid_argument("Missing operation");
      }

      while (i < expression.length() && std::isalnum(expression[i])) {
        ++i;
      }
      --i;
      expect_operand = false;
      continue;
    }

    throw std::invalid_argument("Invalid character in expression");
  }

  if (!brackets.is_empty()) {
    throw std::invalid_argument("Missing closed bracket");
  }
}

int countIslands(const Matrix<int>& matrix) {
  size_t lines = matrix.get_lines();
  size_t columns = matrix.get_columns();

  if (lines == 0 || columns == 0) return 0;

  DSU dsu(lines * columns);

  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < columns; j++) {
      if (matrix[i][j] == 0) continue;

      int current = i * columns + j;

      if (i > 0 && matrix[i - 1][j] == 1) {
        int up = (i - 1) * columns + j;
        dsu.union_op(current, up);
      }

      if (j > 0 && matrix[i][j - 1] == 1) {
        int left = i * columns + (j - 1);
        dsu.union_op(current, left);
      }
    }
  }

  int IslandCount = 0;
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < columns; j++) {
      if (matrix[i][j] == 0) continue;

      int current = i * columns + j;
      int root = dsu.find(current);

      if (root == current) {
        IslandCount++;
      }
    }
  }

  return IslandCount;
}

Matrix<bool> generate_maze(size_t entry, size_t exit,
  size_t lines, size_t columns) {
  if (entry == exit) {
    throw std::invalid_argument("The entry cannot match the exit!");
  }

  if (lines < 5 || columns < 5) {
    throw std::invalid_argument("The maze is too small!");
  }

  if (entry < 1 || entry > lines * columns ||
    exit < 1 || exit > lines * columns) {
    throw std::invalid_argument("Invalid entry or exit!");
  }

  size_t entry_row = (entry - 1) / columns;
  size_t entry_col = (entry - 1) % columns;
  size_t exit_row = (exit - 1) / columns;
  size_t exit_col = (exit - 1) % columns;

  if (entry_row != 0 && entry_row != lines - 1 &&
    entry_col != 0 && entry_col != columns - 1) {
    throw std::invalid_argument("The entry cannot be inside the maze!");
  }

  if (exit_row != 0 && exit_row != lines - 1 &&
    exit_col != 0 && exit_col != columns - 1) {
    throw std::invalid_argument("The exit cannot be inside the maze!");
  }

  DSU dsu(lines * columns);
  Matrix<bool> result(2 * lines + 1, 2 * columns + 1);

  for (size_t i = 0; i < 2 * lines + 1; i++) {
    for (size_t j = 0; j < 2 * columns + 1; j++) {
      result[i][j] = true;
    }
  }

  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < columns; j++) {
      result[2 * i + 1][2 * j + 1] = false;
    }
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  struct Wall {
    size_t cell1;
    size_t cell2;
    size_t wall_row;
    size_t wall_col;
  };

  TVector<Wall> walls;

  for (size_t i = 0; i < lines - 1; i++) {
    for (size_t j = 0; j < columns; j++) {
      size_t cell1 = i * columns + j;
      size_t cell2 = (i + 1) * columns + j;
      walls.push_back({ cell1, cell2, 2 * i + 2, 2 * j + 1 });
    }
  }

  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < columns - 1; j++) {
      size_t cell1 = i * columns + j;
      size_t cell2 = i * columns + j + 1;
      walls.push_back({ cell1, cell2, 2 * i + 1, 2 * j + 2 });
    }
  }

  std::shuffle(walls.begin(), walls.end(), gen);

  for (const auto& wall : walls) {
    if (dsu.find(wall.cell1) != dsu.find(wall.cell2)) {
      dsu.union_op(wall.cell1, wall.cell2);
      result[wall.wall_row][wall.wall_col] = false;
    }
  }

  if (entry_row == 0) {
    result[0][2 * entry_col + 1] = false;
  } else if (entry_row == lines - 1) {
    result[2 * lines][2 * entry_col + 1] = false;
  } else if (entry_col == 0) {
    result[2 * entry_row + 1][0] = false;
  } else if (entry_col == columns - 1) {
    result[2 * entry_row + 1][2 * columns] = false;
  }

  if (exit_row == 0) {
    result[0][2 * exit_col + 1] = false;
  } else if (exit_row == lines - 1) {
    result[2 * lines][2 * exit_col + 1] = false;
  } else if (exit_col == 0) {
    result[2 * exit_row + 1][0] = false;
  } else if (exit_col == columns - 1) {
    result[2 * exit_row + 1][2 * columns] = false;
  }

  return result;
}

void print_maze(const Matrix<bool>& maze) {
  for (size_t i = 0; i < maze.get_lines(); i++) {
    for (size_t j = 0; j < maze.get_columns(); j++) {
      if (maze[i][j] == false) {
        printf(" ");
      } else {
        if (i % 2 == 0) {
          printf("-");
        } else {
          printf("|");
        }
      }
    }
    printf("\n");
  }
}

void print_maze_with_color(const Matrix<bool>& maze,
  size_t entry, size_t exit,
  size_t lines, size_t columns) {
  size_t entry_row = (entry - 1) / columns;
  size_t entry_col = (entry - 1) % columns;
  size_t exit_row = (exit - 1) / columns;
  size_t exit_col = (exit - 1) % columns;

  size_t entry_i, entry_j, exit_i, exit_j;

  if (entry_row == 0) {
    entry_i = 0;
    entry_j = 2 * entry_col + 1;
  } else if (entry_row == lines - 1) {
    entry_i = 2 * lines;
    entry_j = 2 * entry_col + 1;
  } else if (entry_col == 0) {
    entry_i = 2 * entry_row + 1;
    entry_j = 0;
  } else if (entry_col == columns - 1) {
    entry_i = 2 * entry_row + 1;
    entry_j = 2 * columns;
  } else {
    entry_i = 2 * entry_row + 1;
    entry_j = 2 * entry_col + 1;
  }

  if (exit_row == 0) {
    exit_i = 0;
    exit_j = 2 * exit_col + 1;
  } else if (exit_row == lines - 1) {
    exit_i = 2 * lines;
    exit_j = 2 * exit_col + 1;
  } else if (exit_col == 0) {
    exit_i = 2 * exit_row + 1;
    exit_j = 0;
  } else if (exit_col == columns - 1) {
    exit_i = 2 * exit_row + 1;
    exit_j = 2 * columns;
  } else {
    exit_i = 2 * exit_row + 1;
    exit_j = 2 * exit_col + 1;
  }

  const char* WALL = "\033[44m  \033[0m";
  const char* PATH = "\033[47m  \033[0m";
  const char* ENTRY = "\033[42mE \033[0m";
  const char* EXIT = "\033[41mX \033[0m";

  for (size_t i = 0; i < maze.get_lines(); i++) {
    for (size_t j = 0; j < maze.get_columns(); j++) {
      if (i == entry_i && j == entry_j) {
        printf("%s", ENTRY);
      } else if (i == exit_i && j == exit_j) {
        printf("%s", EXIT);
      } else if (maze[i][j]) {
        printf("%s", WALL);
      } else {
        printf("%s", PATH);
      }
    }
    printf("\n");
  }

  printf("\n\033[42mE\033[0m - Entry (cell %zu)"
    "  \033[41mX\033[0m - Exit (cell %zu)\n",
    entry, exit);
}
