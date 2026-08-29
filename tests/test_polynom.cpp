// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "../lib_polynom/polynom.h"

TEST(TestPolynomLib, CreateDefaultPolynom) {
  Polynom<3> p;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, PlusEqualMonomToEmpty) {
  Polynom<3> p;

  int powers[3] = {1, 2, 3};
  Monom<3> m(2.5, powers);

  p += m;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomZeroIgnored) {
  Polynom<3> p;

  int powers1[3] = {1, 2, 3};
  int powers2[3] = {1, 4, 3};

  Monom<3> m1(2.5, powers1);
  Monom<3> m2(0.0, powers2);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomGreater) {
  Polynom<3> p;

  int p1[3] = {1, 2, 3};
  int p2[3] = {2, 1, 0};

  Monom<3> m1(2.5, p1);
  Monom<3> m2(3.5, p2);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;

  EXPECT_EQ(ss.str(), "3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomLess) {
  Polynom<3> p;
  int p1[3] = {2, 1, 0};
  int p2[3] = {1, 2, 3};

  Monom<3> m1(3.5, p1);
  Monom<3> m2(2.5, p2);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;

  EXPECT_EQ(ss.str(), "3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomMiddle) {
  Polynom<3> p;
  int p1[3] = {2, 1, 0};
  int p2[3] = {1, 2, 3};
  int p3[3] = {0, 0, 0};

  Monom<3> m1(3.0, p1);
  Monom<3> m2(1.0, p2);
  Monom<3> m3(2.0, p3);

  p += m1;
  p += m2;
  p += m3;

  std::stringstream ss;
  ss << p;

  EXPECT_EQ(ss.str(), "3x1^2x2+x1x2^2x3^3+2");
}

TEST(TestPolynomLib, AddSimilar) {
  Polynom<3> p;
  int powers[3] = {1, 2, 3};

  Monom<3> m1(2.5, powers);
  Monom<3> m2(3.5, powers);
  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "6x1x2^2x3^3");
}

TEST(TestPolynomLib, AddOpposite) {
  Polynom<3> p;
  int powers[3] = {1, 2, 3};

  Monom<3> m1(5.0, powers);
  Monom<3> m2(-5.0, powers);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, CreatePolynomWithCopy) {
  Polynom<3> p1;
  int p1_powers[3] = {2, 1, 0};
  int p2_powers[3] = {1, 2, 3};
  int p3_powers[3] = {0, 0, 0};

  Monom<3> m1(3.0, p1_powers);
  Monom<3> m2(2.0, p2_powers);
  Monom<3> m3(1.0, p3_powers);

  p1 += m1;
  p1 += m2;
  p1 += m3;

  Polynom<3> p2(p1);

  std::stringstream ss1, ss2;
  ss1 << p1;
  ss2 << p2;
  EXPECT_EQ(ss1.str(), ss2.str());
  EXPECT_EQ(ss1.str(), "3x1^2x2+2x1x2^2x3^3+1");
}

TEST(TestPolynomLib, ConstructorEmptyString) {
  Polynom<3> p("");

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, ConstructorNormalString) {
  Polynom<3> p("2.5x1x2^2x3^3-3.5x1^2x2");
  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, ConstructorWithNegativePowers) {
  Polynom<3> p("2.5x1^(-2)x2^3-3.5x1^2x2^(-1)");
  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2^(-1)+2.5x1^(-2)x2^3");
}

TEST(TestPolynomLib, MinusEqualMonom) {
  Polynom<3> p("5x1x2^2x3^3 + 3x1^2x2");

  int powers1[3] = {1, 2, 3};
  Monom<3> m1(2.0, powers1);

  int powers2[3] = {3, 0, 0};
  Monom<3> m2(1.0, powers2);

  p -= m1;
  p -= m2;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "-x1^3+3x1^2x2+3x1x2^2x3^3");
}

TEST(TestPolynomLib, MultiplyEqualMonom) {
  Polynom<3> p("2x1x2^2x3^3 + 3x1^2x2");

  int powers[3] = {1, 0, 1};
  Monom<3> m(2.0, powers);

  p *= m;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "6x1^3x2x3+4x1^2x2^2x3^4");
}

TEST(TestPolynomLib, AssignmentOperator) {
  Polynom<3> p1("2.5x1x2^2x3^3 - 3.5x1^2x2");
  Polynom<3> p2;

  p2 = p1;

  std::stringstream ss1, ss2;
  ss1 << p1;
  ss2 << p2;
  EXPECT_EQ(ss1.str(), ss2.str());
  EXPECT_EQ(ss2.str(), "-3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusMonom) {
  Polynom<3> p("2.5x1x2^2x3^3 - 3.5x1^2x2");

  int powers[3] = {1, 0, 1};
  Monom<3> m(2.0, powers);

  Polynom<3> result = p + m;

  std::stringstream ss;
  ss << result;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2+2.5x1x2^2x3^3+2x1x3");

  ss.str("");
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, MinusMonom) {
  Polynom<3> p("2.5x1x2^2x3^3 - 3.5x1^2x2");

  int powers[3] = {2, 1, 0};
  Monom<3> m(1.5, powers);

  Polynom<3> result = p - m;

  std::stringstream ss;
  ss << result;
  EXPECT_EQ(ss.str(), "-5x1^2x2+2.5x1x2^2x3^3");

  ss.str("");
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, MiltiplyMonom) {
  Polynom<3> p("2x1x2^2x3^3 + 3x1^2x2");

  int powers[3] = {1, 0, 1};
  Monom<3> m(2.0, powers);

  Polynom<3> result = p * m;

  std::stringstream ss;
  ss << result;
  EXPECT_EQ(ss.str(), "6x1^3x2x3+4x1^2x2^2x3^4");

  ss.str("");
  ss << p;
  EXPECT_EQ(ss.str(), "3x1^2x2+2x1x2^2x3^3");
}

TEST(TestPolynomLib, MultiplyMonomByZero) {
  Polynom<3> p("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");

  int zero_powers[3] = {0, 0, 0};
  Monom<3> zero_monom(0.0, zero_powers);

  p *= zero_monom;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, MultiplyEqualScalar) {
  Polynom<3> p("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");

  p *= 2.0;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "-7x1^2x2+5x1x2^2x3^3+8");
}

TEST(TestPolynomLib, MultiplyEqualScalarZero) {
  Polynom<3> p("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");

  p *= 0.0;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, MultiplyScalar) {
  Polynom<3> p("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");

  Polynom<3> result = p * 2.0;

  std::stringstream ss;
  ss << result;
  EXPECT_EQ(ss.str(), "-7x1^2x2+5x1x2^2x3^3+8");

  ss.str("");
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2+2.5x1x2^2x3^3+4");
}

TEST(TestPolynomLib, UnaryMinus) {
  Polynom<3> p("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");

  Polynom<3> neg = -p;

  std::stringstream ss;
  ss << neg;
  EXPECT_EQ(ss.str(), "3.5x1^2x2-2.5x1x2^2x3^3-4");
}

TEST(TestPolynomLib, EqualIdenticalPolynoms) {
  Polynom<3> p1("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");
  Polynom<3> p2("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");

  EXPECT_TRUE(p1 == p2);
  EXPECT_FALSE(p1 != p2);
}

TEST(TestPolynomLib, NotEqualDifferentCoefficients) {
  Polynom<3> p1("2.5x1x2^2x3^3 - 3.5x1^2x2 + 4");
  Polynom<3> p2("2.5x1x2^2x3^3 - 3.5x1^2x2 + 5");

  EXPECT_FALSE(p1 == p2);
  EXPECT_TRUE(p1 != p2);
}

TEST(TestPolynomLib, Calculate) {
  Polynom<3> p("2x1x2 + 3x3^2 - 4");
  double values[3] = {2.0, 3.0, 4.0};

  EXPECT_DOUBLE_EQ(p.calculate(values), 56.0);
}

TEST(TestPolynomLib, PlusEqualPolynom) {
  Polynom<3> p1("2x1x2 + 3x3+3x1^2");
  Polynom<3> p2("4x1x2 - 2x3 + 5");

  p1 += p2;

  std::stringstream ss;
  ss << p1;

  EXPECT_EQ(ss.str(), "3x1^2+6x1x2+x3+5");
}

TEST(TestPolynomLib, MinusEqualPolynom) {
  Polynom<3> p1("6x1x2 + 4x3 + 5");
  Polynom<3> p2("2x1x2 + 4x3 - 2");

  p1 -= p2;

  std::stringstream ss;
  ss << p1;

  EXPECT_EQ(ss.str(), "4x1x2+7");
}

TEST(TestPolynomLib, MultiplyEqualPolynom) {
  Polynom<3> p1("x1 + 2");
  Polynom<3> p2("x1 + 3");

  p1 *= p2;

  std::stringstream ss;
  ss << p1;
  EXPECT_EQ(ss.str(), "x1^2+5x1+6");
}

TEST(TestPolynomLib, PlusPolynom) {
  Polynom<3> p1("2x1x2 + 3x3");
  Polynom<3> p2("4x1x2 - 2x3 + 5");

  Polynom<3> result = p1 + p2;

  std::stringstream ss;
  ss << result;
  EXPECT_EQ(ss.str(), "6x1x2+x3+5");

  ss.str("");
  ss << p1;
  EXPECT_EQ(ss.str(), "2x1x2+3x3");
}

TEST(TestPolynomLib, MinusPolynom) {
  Polynom<3> p1("2x1x2 + 3x3");
  Polynom<3> p2("4x1x2 - 2x3 + 5");

  Polynom<3> result = p1 - p2;

  std::stringstream ss;
  ss << result;
  EXPECT_EQ(ss.str(), "-2x1x2+5x3-5");

  ss.str("");
  ss << p1;
  EXPECT_EQ(ss.str(), "2x1x2+3x3");
}

TEST(TestPolynomLib, MulptiplyPolynom) {
  Polynom<3> p1("x1 + 2");
  Polynom<3> p2("x1 + 3");

  Polynom<3> result = p1 * p2;

  std::stringstream ss;
  ss << result;
  EXPECT_EQ(ss.str(), "x1^2+5x1+6");

  ss.str("");
  ss << p1;
  EXPECT_EQ(ss.str(), "x1+2");
}

TEST(TestPolynomLib, InputOperator) {
  Polynom<3> p;
  std::istringstream iss("2.5x1x2^2x3^3-3.5x1^2x2");

  iss >> p;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, InputOperatorEmpty) {
  Polynom<3> p;
  std::istringstream iss("");

  iss >> p;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, InputOperatorWithError) {
  Polynom<3> p;
  std::istringstream iss("2.5x1x2^2x3^3-3.5x4x2");

  iss >> p;

  EXPECT_TRUE(iss.fail());

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, ConstructorStringUnbalancedParentheses) {
  EXPECT_THROW(Polynom<3>("2.5x1^(-2x2^3"), std::invalid_argument);

  EXPECT_THROW(Polynom<3>("2.5x1^(-2))x2^3"), std::invalid_argument);

  EXPECT_THROW(Polynom<3>("2.5x1^(-2)x2^(3"), std::invalid_argument);

  EXPECT_THROW(Polynom<3>("2.5x1^(-2)x2^3)"), std::invalid_argument);
}
