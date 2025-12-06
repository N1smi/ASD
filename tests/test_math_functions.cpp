// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include <cmath>
#include "../lib_math_functions/math_functions.h"

TEST(TestMathFunctionsLib, NormalizeAngleBasic) {
  const double PI = MathFunctions::PI;

  EXPECT_DOUBLE_EQ(MathFunctions::normalizeAngle(0.0), 0.0);
  EXPECT_DOUBLE_EQ(MathFunctions::normalizeAngle(PI / 2), PI / 2);
  EXPECT_DOUBLE_EQ(MathFunctions::normalizeAngle(-PI / 2), -PI / 2);
  EXPECT_DOUBLE_EQ(MathFunctions::normalizeAngle(PI), PI);
  EXPECT_DOUBLE_EQ(MathFunctions::normalizeAngle(-PI), PI);
}

TEST(TestMathFunctionsLib, NormalizeAngleLargePositive) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::normalizeAngle(3 * PI), PI, 1e-10);
  EXPECT_NEAR(MathFunctions::normalizeAngle(2 * PI + PI / 2), PI / 2, 1e-10);
  EXPECT_NEAR(MathFunctions::normalizeAngle(10 * PI + PI / 3), PI / 3, 1e-10);
}

TEST(TestMathFunctionsLib, NormalizeAngleLargeNegative) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::normalizeAngle(-3 * PI), PI, 1e-10);
  EXPECT_NEAR(MathFunctions::normalizeAngle(-2 * PI - PI / 2), -PI / 2, 1e-10);
  EXPECT_NEAR(MathFunctions::normalizeAngle(-10 * PI - PI / 3), -PI / 3, 1e-10);
}

TEST(TestMathFunctionsLib, MySinZero) {
  EXPECT_DOUBLE_EQ(MathFunctions::mySin(0.0), 0.0);
}

TEST(TestMathFunctionsLib, MySinBasicValues) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::mySin(PI / 2), 1.0, 1e-10);
  EXPECT_NEAR(MathFunctions::mySin(PI), 0.0, 1e-10);
  EXPECT_NEAR(MathFunctions::mySin(2 * PI), 0.0, 1e-10);
  EXPECT_NEAR(MathFunctions::mySin(3 * PI / 2), -1.0, 1e-10);
}

TEST(TestMathFunctionsLib, MySinSpecificAngles) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::mySin(PI / 6), 0.5, 1e-10);

  EXPECT_NEAR(MathFunctions::mySin(PI / 4), std::sqrt(2) / 2, 1e-10);

  EXPECT_NEAR(MathFunctions::mySin(PI / 3), std::sqrt(3) / 2, 1e-10);
}

TEST(TestMathFunctionsLib, MySinOddFunction) {
  EXPECT_NEAR(MathFunctions::mySin(-0.5), -MathFunctions::mySin(0.5), 1e-10);
  EXPECT_NEAR(MathFunctions::mySin(-1.0), -MathFunctions::mySin(1.0), 1e-10);
}

TEST(TestMathFunctionsLib, MySinPeriodicity) {
  const double PI = MathFunctions::PI;
  double x = 0.7;

  EXPECT_NEAR(MathFunctions::mySin(x),
    MathFunctions::mySin(x + 2 * PI), 1e-10);
}

TEST(TestMathFunctionsLib, MySinLargeAngle) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::mySin(100 * PI + PI / 2), 1.0, 1e-10);
}

TEST(TestMathFunctionsLib, MySinPrecision) {
  double test_values[] = { 0.1, 0.5, 1.0, 1.57, 3.14 };

  for (double x : test_values) {
    double my_result = MathFunctions::mySin(x);
    double std_result = std::sin(x);
    EXPECT_NEAR(my_result, std_result, 1e-10);
  }
}

TEST(TestMathFunctionsLib, MyCosZero) {
  EXPECT_DOUBLE_EQ(MathFunctions::myCos(0.0), 1.0);
}

TEST(TestMathFunctionsLib, MyCosBasicValues) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCos(PI / 2), 0.0, 1e-10);
  EXPECT_NEAR(MathFunctions::myCos(PI), -1.0, 1e-10);
  EXPECT_NEAR(MathFunctions::myCos(3 * PI / 2), 0.0, 1e-10);
  EXPECT_NEAR(MathFunctions::myCos(2 * PI), 1.0, 1e-10);
}

TEST(TestMathFunctionsLib, MyCosSpecificAngles) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCos(PI / 3), 0.5, 1e-10);

  EXPECT_NEAR(MathFunctions::myCos(PI / 4), std::sqrt(2) / 2, 1e-10);

  EXPECT_NEAR(MathFunctions::myCos(PI / 6), std::sqrt(3) / 2, 1e-10);
}

TEST(TestMathFunctionsLib, MyCosEvenFunction) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCos(-0.5), MathFunctions::myCos(0.5), 1e-10);
  EXPECT_NEAR(MathFunctions::myCos(-1.0), MathFunctions::myCos(1.0), 1e-10);
  EXPECT_NEAR(MathFunctions::myCos(-PI / 4),
    MathFunctions::myCos(PI / 4), 1e-10);
}

TEST(TestMathFunctionsLib, MyCosPeriodicity) {
  const double PI = MathFunctions::PI;
  double x = 0.7;

  EXPECT_NEAR(MathFunctions::myCos(x),
    MathFunctions::myCos(x + 2 * PI), 1e-10);
}

TEST(TestMathFunctionsLib, MyCosLargeAngle) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCos(100 * PI + PI), -1.0, 1e-10);
}

TEST(TestMathFunctionsLib, MyCosPrecision) {
  double test_values[] = { 0.1, 0.5, 1.0, 1.57, 3.14 };

  for (double x : test_values) {
    double my_result = MathFunctions::myCos(x);
    double std_result = std::cos(x);
    EXPECT_NEAR(my_result, std_result, 1e-10);
  }
}

TEST(TestMathFunctionsLib, MyTanZero) {
  EXPECT_DOUBLE_EQ(MathFunctions::myTan(0.0), 0.0);
}

TEST(TestMathFunctionsLib, MyTanBasicValues) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myTan(PI / 4), 1.0, 1e-10);
  EXPECT_NEAR(MathFunctions::myTan(-PI / 4), -1.0, 1e-10);
  EXPECT_NEAR(MathFunctions::myTan(PI), 0.0, 1e-10);
  EXPECT_NEAR(MathFunctions::myTan(2 * PI), 0.0, 1e-10);
}

TEST(TestMathFunctionsLib, MyTanSpecificAngles) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myTan(PI / 6), 1.0 / std::sqrt(3), 1e-10);

  EXPECT_NEAR(MathFunctions::myTan(PI / 3), std::sqrt(3), 1e-10);
}

TEST(TestMathFunctionsLib, MyTanOddFunction) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myTan(-0.5), -MathFunctions::myTan(0.5), 1e-10);
  EXPECT_NEAR(MathFunctions::myTan(-1.0), -MathFunctions::myTan(1.0), 1e-10);
  EXPECT_NEAR(MathFunctions::myTan(-PI / 4),
    -MathFunctions::myTan(PI / 4), 1e-10);
  EXPECT_NEAR(MathFunctions::myTan(-PI / 6),
    -MathFunctions::myTan(PI / 6), 1e-10);
}

TEST(TestMathFunctionsLib, MyTanPeriodicity) {
  const double PI = MathFunctions::PI;
  double x = 0.7;

  EXPECT_NEAR(MathFunctions::myTan(x),
    MathFunctions::myTan(x + PI), 1e-10);
}

TEST(TestMathFunctionsLib, MyTanLargeAngle) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myTan(100 * PI + PI / 4), 1.0, 1e-10);
  EXPECT_NEAR(MathFunctions::myTan(50 * PI + 0.5),
    MathFunctions::myTan(0.5), 1e-10);
}

TEST(TestMathFunctionsLib, MyTanPrecision) {
  double test_values[] = { 0.1, 0.2, 0.5, 0.8, 1.0, 1.2, 1.4 };

  for (double x : test_values) {
    double my_result = MathFunctions::myTan(x);
    double std_result = std::tan(x);
    EXPECT_NEAR(my_result, std_result, 1e-10);
  }
}

TEST(TestMathFunctionsLib, MyTanThrowsAtPoles) {
  const double PI = MathFunctions::PI;

  EXPECT_THROW(MathFunctions::myTan(PI / 2), std::runtime_error);
  EXPECT_THROW(MathFunctions::myTan(-PI / 2), std::runtime_error);
  EXPECT_THROW(MathFunctions::myTan(3 * PI / 2), std::runtime_error);

  EXPECT_NO_THROW(MathFunctions::myTan(PI / 2 - 1e-6));
  EXPECT_NO_THROW(MathFunctions::myTan(PI / 2 + 1e-6));

  EXPECT_THROW(MathFunctions::myTan(PI / 2 + PI), std::runtime_error);
  EXPECT_THROW(MathFunctions::myTan(PI / 2 + 2 * PI), std::runtime_error);
  EXPECT_THROW(MathFunctions::myTan(PI / 2 - PI), std::runtime_error);
}

TEST(TestMathFunctionsLib, MyCtgBasicValues) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCtg(PI / 4), 1.0, 1e-10);

  EXPECT_NEAR(MathFunctions::myCtg(PI / 2), 0.0, 1e-10);

  EXPECT_NEAR(MathFunctions::myCtg(3 * PI / 4), -1.0, 1e-10);

  EXPECT_NEAR(MathFunctions::myCtg(3 * PI / 2), 0.0, 1e-10);
}

TEST(TestMathFunctionsLib, MyCtgSpecificAngles) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCtg(PI / 3), 1.0 / std::sqrt(3), 1e-10);

  EXPECT_NEAR(MathFunctions::myCtg(PI / 6), std::sqrt(3), 1e-10);
}

TEST(TestMathFunctionsLib, MyCtgOddFunction) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCtg(-0.5), -MathFunctions::myCtg(0.5), 1e-10);
  EXPECT_NEAR(MathFunctions::myCtg(-1.0), -MathFunctions::myCtg(1.0), 1e-10);
  EXPECT_NEAR(MathFunctions::myCtg(-PI / 4),
    -MathFunctions::myCtg(PI / 4), 1e-10);
}

TEST(TestMathFunctionsLib, MyCtgPeriodicity) {
  const double PI = MathFunctions::PI;
  double x = 0.7;

  EXPECT_NEAR(MathFunctions::myCtg(x),
    MathFunctions::myCtg(x + PI), 1e-10);
}

TEST(TestMathFunctionsLib, MyCtgPrecision) {
  double test_values[] = { 0.1, 0.2, 0.5, 0.8, 1.0, 1.2, 1.4 };

  for (double x : test_values) {
    double my_result = MathFunctions::myCtg(x);
    double std_result = 1.0 / std::tan(x);
    EXPECT_NEAR(my_result, std_result, 1e-10);
  }
}

TEST(TestMathFunctionsLib, MyCtgThrowsAtPoles) {
  const double PI = MathFunctions::PI;

  EXPECT_THROW(MathFunctions::myCtg(0.0), std::runtime_error);
  EXPECT_THROW(MathFunctions::myCtg(PI), std::runtime_error);
  EXPECT_THROW(MathFunctions::myCtg(-PI), std::runtime_error);
  EXPECT_THROW(MathFunctions::myCtg(2 * PI), std::runtime_error);

  EXPECT_NO_THROW(MathFunctions::myCtg(1e-6));
  EXPECT_NO_THROW(MathFunctions::myCtg(PI - 1e-6));
  EXPECT_NO_THROW(MathFunctions::myCtg(PI + 1e-6));
}

TEST(TestMathFunctionsLib, MyCtgSymmetry) {
  const double PI = MathFunctions::PI;

  double x = 0.3;
  EXPECT_NEAR(MathFunctions::myCtg(PI / 2 - x),
    MathFunctions::myTan(x),
    1e-10);

  EXPECT_NEAR(MathFunctions::myCtg(PI / 2 + x),
    -MathFunctions::myTan(x),
    1e-10);
}

TEST(TestMathFunctionsLib, MyCtgLargeAngles) {
  const double PI = MathFunctions::PI;

  EXPECT_NEAR(MathFunctions::myCtg(100 * PI + PI / 4), 1.0, 1e-10);
}

TEST(TestMathFunctionsLib, MyExpZero) {
  EXPECT_DOUBLE_EQ(MathFunctions::myExp(0.0), 1.0);
}

TEST(TestMathFunctionsLib, MyExpOne) {
  EXPECT_NEAR(MathFunctions::myExp(1.0), MathFunctions::E, 1e-10);
}

TEST(TestMathFunctionsLib, MyExpNegative) {
  EXPECT_NEAR(MathFunctions::myExp(-1.0), 1.0 / MathFunctions::E, 1e-10);
  EXPECT_NEAR(MathFunctions::myExp(-2.0), 1.0 / (MathFunctions::E * MathFunctions::E), 1e-10);
}

TEST(TestMathFunctionsLib, MyExpSmallValues) {
  EXPECT_NEAR(MathFunctions::myExp(0.5), std::sqrt(MathFunctions::E), 1e-10);
  EXPECT_NEAR(MathFunctions::myExp(-0.5), 1.0 / std::sqrt(MathFunctions::E), 1e-10);
}

TEST(TestMathFunctionsLib, MyExpProperties) {
  double a = 0.5, b = 1.5;
  EXPECT_NEAR(MathFunctions::myExp(a + b),
    MathFunctions::myExp(a) * MathFunctions::myExp(b),
    1e-10);
}

TEST(TestMathFunctionsLib, MyExpPrecision) {
  double test_values[] = { -2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 2.0, 3.0 };

  for (double x : test_values) {
    double my_result = MathFunctions::myExp(x);
    double std_result = std::exp(x);
    EXPECT_NEAR(my_result, std_result, 1e-10);
  }
}

TEST(TestMathFunctionsLib, MyAbsZero) {
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(0.0), 0.0);
}

TEST(TestMathFunctionsLib, MyAbsPositive) {
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(5.0), 5.0);
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(3.14), 3.14);
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(100.0), 100.0);
}

TEST(TestMathFunctionsLib, MyAbsNegative) {
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(-5.0), 5.0);
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(-3.14), 3.14);
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(-100.0), 100.0);
}

TEST(TestMathFunctionsLib, MyAbsProperties) {
  double a = -2.0, b = 3.0;
  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(a * b),
    MathFunctions::myAbs(a) * MathFunctions::myAbs(b));

  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(a / b),
    MathFunctions::myAbs(a) / MathFunctions::myAbs(b));

  EXPECT_DOUBLE_EQ(MathFunctions::myAbs(a),
    MathFunctions::myAbs(-a));
}

TEST(TestMathFunctionsLib, MyAbsPrecision) {
  double test_values[] = { -1000.0, -100.0, -10.0, -1.0, -0.5,
                          0.0, 0.5, 1.0, 10.0, 100.0, 1000.0 };

  for (double x : test_values) {
    double my_result = MathFunctions::myAbs(x);
    double std_result = std::abs(x);
    EXPECT_DOUBLE_EQ(my_result, std_result);
  }
}

TEST(TestMathFunctionsLib, MySqrtZero) {
  EXPECT_DOUBLE_EQ(MathFunctions::mySqrt(0.0), 0.0);
}

TEST(TestMathFunctionsLib, MySqrtNegativeZero) {
  EXPECT_DOUBLE_EQ(MathFunctions::mySqrt(-0.0), 0.0);
}

TEST(TestMathFunctionsLib, MySqrtBasic) {
  EXPECT_DOUBLE_EQ(MathFunctions::mySqrt(1.0), 1.0);
  EXPECT_DOUBLE_EQ(MathFunctions::mySqrt(4.0), 2.0);
}

TEST(TestMathFunctionsLib, MySqrtSpecificValues) {
  EXPECT_NEAR(MathFunctions::mySqrt(2.0), std::sqrt(2.0), 1e-10);
  EXPECT_NEAR(MathFunctions::mySqrt(0.5), std::sqrt(0.5), 1e-10);
  EXPECT_NEAR(MathFunctions::mySqrt(10.0), std::sqrt(10.0), 1e-10);
}

TEST(TestMathFunctionsLib, MySqrtThrowsForNegative) {
  EXPECT_THROW(MathFunctions::mySqrt(-1.0), std::runtime_error);
  EXPECT_THROW(MathFunctions::mySqrt(-0.5), std::runtime_error);
  EXPECT_THROW(MathFunctions::mySqrt(-100.0), std::runtime_error);
}

TEST(TestMathFunctionsLib, MySqrtProperties) {
  double a = 4.0, b = 9.0;

  EXPECT_NEAR(MathFunctions::mySqrt(a * b),
    MathFunctions::mySqrt(a) * MathFunctions::mySqrt(b),
    1e-10);

  EXPECT_NEAR(MathFunctions::mySqrt(a / b),
    MathFunctions::mySqrt(a) / MathFunctions::mySqrt(b),
    1e-10);
}

TEST(TestMathFunctionsLib, MySqrtVerySmallNumbers) {
  EXPECT_NEAR(MathFunctions::mySqrt(1e-12), 1e-6, 1e-10);
  EXPECT_NEAR(MathFunctions::mySqrt(1e-20), 1e-10, 1e-15);
}

TEST(TestMathFunctionsLib, MySqrtVeryLargeNumbers) {
  EXPECT_NEAR(MathFunctions::mySqrt(1e12), 1e6, 1e-5);
  EXPECT_NEAR(MathFunctions::mySqrt(1e20), 1e10, 1e-5);
}

TEST(TestMathFunctionsLib, MySqrtPrecision) {
  double test_values[] = { 0.01, 0.25, 0.5, 1.0, 2.0, 5.0, 10.0, 100.0, 1000.0 };

  for (double x : test_values) {
    double my_result = MathFunctions::mySqrt(x);
    double std_result = std::sqrt(x);
    EXPECT_NEAR(my_result, std_result, 1e-10);
  }
}
