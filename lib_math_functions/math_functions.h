// Copyright 2025 Smirnov Nikita

#ifndef LIB_MATH_FUNCTIONS_MATH_FUNCTIONS_H_
#define LIB_MATH_FUNCTIONS_MATH_FUNCTIONS_H_

#include <cmath>
#include <string>

namespace MathFunctions {
const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;
const double EPSILON = 1e-12;
const int MAX_ITERATIONS = 100;

double normalizeAngle(double x);

double mySin(double x);

double myCos(double x);

double myTan(double x);

double myCtg(double x);

double myExp(double x);

double myAbs(double x);

double mySqrt(double x);

using MathFunctionPtr = double(*)(double);

bool isFunction(const std::string& name);

inline MathFunctionPtr getFunction(const std::string& name) {
    if (name == "sin") return mySin;
    if (name == "cos") return myCos;
    if (name == "tg") return myTan;
    if (name == "ctg") return myCtg;
    if (name == "exp") return myExp;
    if (name == "abs") return myAbs;
    if (name == "sqrt") return mySqrt;
    return nullptr;
  }

}  // namespace MathFunctions

#endif  // LIB_MATH_FUNCTIONS_MATH_FUNCTIONS_H_
