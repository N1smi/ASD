// Copyright 2025 Smirnov Nikita

#include<stdexcept>
#include "../lib_math_functions/math_functions.h"

double MathFunctions::normalizeAngle(double x) {
  while (x > PI) x -= 2 * PI;
  while (x <= -PI) x += 2 * PI;
  return x;
}

double MathFunctions::mySin(double x) {
  x = normalizeAngle(x);

  double term = x;
  double sum = term;
  double x2 = x * x;
  int n = 1;

  while (std::abs(term) > EPSILON && n < MAX_ITERATIONS) {
    term = -term * x2 / ((2 * n) * (2 * n + 1));
    sum += term;
    n++;
  }

  return sum;
}

double MathFunctions::myCos(double x) {
  x = normalizeAngle(x);

  double term = 1.0;
  double sum = term;
  double x2 = x * x;
  int n = 1;

  while (std::abs(term) > EPSILON && n < MAX_ITERATIONS) {
    term = -term * x2 / ((2 * n - 1) * (2 * n));
    sum += term;
    n++;
  }

  return sum;
}

double MathFunctions::myTan(double x) {
  double cos_val = myCos(x);
  if (std::abs(cos_val) < EPSILON) {
    throw std::runtime_error("tan(x) is undefined at x = PI/2 + PI * k");
  }
  return mySin(x) / cos_val;
}

double MathFunctions::myCtg(double x) {
  double sin_val = mySin(x);
  if (std::abs(sin_val) < EPSILON) {
    throw std::runtime_error("ctg(x) is undefined at x = PI * k");
  }
  return myCos(x) / sin_val;
}

double MathFunctions::myExp(double x) {
  double term = 1.0;
  double sum = term;
  int n = 1;

  while (std::abs(term) > EPSILON && n < MAX_ITERATIONS) {
    term = term * x / n;
    sum += term;
    n++;
  }

  return sum;
}

double MathFunctions::myAbs(double x) {
  return (x < 0) ? -x : x;
}

double MathFunctions::mySqrt(double x) {
  if (x < 0) {
    throw std::runtime_error("sqrt of negative number");
  }

  if (x == 0) return 0.0;

  double guess = x;
  double prev;

  do {
    prev = guess;
    guess = 0.5 * (guess + x / guess);
  } while (std::abs(guess - prev) > EPSILON);

  return guess;
}

bool MathFunctions::isFunction(const std::string& name) {
  return name == "sin" || name == "cos" || name == "tg" ||
    name == "ctg" || name == "exp" || name == "abs" ||
    name == "sqrt";
}
