// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include <sstream>
#include "../lib_monom/monom.h"

TEST(TestMonomLib, CreateDefaultMonom) {
  Monom<3> monom;

  EXPECT_DOUBLE_EQ(monom.getCoefficient(), 0.0);
  for (size_t i = 0; i < monom.getVarsCount(); i++) {
    EXPECT_EQ(monom.getPower(i), 0);
  }
}

TEST(TestMonomLib, CreateScalarMonom) {
  Monom<3> monom(5.0);

  EXPECT_DOUBLE_EQ(monom.getCoefficient(), 5.0);
  for (size_t i = 0; i < monom.getVarsCount(); i++) {
    EXPECT_EQ(monom.getPower(i), 0);
  }
}

TEST(TestMonomLib, CreateMonomWithPowers) {
  int powers[3] = { 1, 2, 3};
  Monom<3> monom(10.0, powers);

  EXPECT_DOUBLE_EQ(monom.getCoefficient(), 10.0);
  for (size_t i = 0; i < monom.getVarsCount(); i++) {
    EXPECT_EQ(monom.getPower(i), i + 1);
  }
}

TEST(TestMonomLib, CopyMonom) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom(10.0, powers);

  Monom<3> monom_copy(monom);

  EXPECT_DOUBLE_EQ(monom_copy.getCoefficient(), 10.0);
  for (size_t i = 0; i < monom_copy.getVarsCount(); i++) {
    EXPECT_EQ(monom_copy.getPower(i), i + 1);
  }
}

TEST(TestMonomLib, StrictEqual) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom1(10.0, powers);

  Monom<3> monom2(20.0, powers);

  EXPECT_TRUE(monom1 == monom2);
  EXPECT_FALSE(monom1 != monom2);
}

TEST(TestMonomLib, StrictNotEqual) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(10.0, powers1);

  int powers2[3] = { -1, 0, 3 };
  Monom<3> monom2(10.0, powers2);

  EXPECT_TRUE(monom1 != monom2);
  EXPECT_FALSE(monom1 == monom2);
}

TEST(TestMonomLib, PlusEqual) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom1(1.0, powers);
  Monom<3> monom2(10.0, powers);

  monom1 += monom2;

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 11.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);
}

TEST(TestMonomLib, PlusEqualThrowWhenNonSimilar) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(1.0, powers1);
  int powers2[3] = { -1, 0, 3 };
  Monom<3> monom2(10.0, powers2);

  EXPECT_THROW(monom1 += monom2, std::invalid_argument);

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 1.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);
}

TEST(TestMonomLib, MinusEqual) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom1(5.0, powers);
  Monom<3> monom2(10.0, powers);

  monom1 -= monom2;

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), -5.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);
}

TEST(TestMonomLib, MinusEqualThrowWhenNonSimilar) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { -1, 0, 3 };
  Monom<3> monom2(10.0, powers2);

  EXPECT_THROW(monom1 -= monom2, std::invalid_argument);

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);
}

TEST(TestMonomLib, MultEqual) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { -1, 0, 3 };
  Monom<3> monom2(10.0, powers2);

  monom1 *= monom2;

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 220.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);

  EXPECT_EQ(monom1.getPower(0), 0);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 6);

  EXPECT_EQ(monom2.getPower(0), -1);
  EXPECT_EQ(monom2.getPower(1), 0);
  EXPECT_EQ(monom2.getPower(2), 3);
}

TEST(TestMonomLib, DivEqual) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { 2, 3, 4 };
  Monom<3> monom2(2.0, powers2);

  monom1 /= monom2;

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 11.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 2.0);

  EXPECT_EQ(monom1.getPower(0), 1);
  EXPECT_EQ(monom1.getPower(1), -1);
  EXPECT_EQ(monom1.getPower(2), -1);

  EXPECT_EQ(monom2.getPower(0), 2);
  EXPECT_EQ(monom2.getPower(1), 3);
  EXPECT_EQ(monom2.getPower(2), 4);
}

TEST(TestMonomLib, DivEqualThrowWhenDivByZero) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { 2, 3, 4 };
  Monom<3> monom2(0.0, powers2);

  EXPECT_THROW(monom1 /= monom2, std::invalid_argument);

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 0.0);

  EXPECT_EQ(monom1.getPower(0), 3);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);

  EXPECT_EQ(monom2.getPower(0), 2);
  EXPECT_EQ(monom2.getPower(1), 3);
  EXPECT_EQ(monom2.getPower(2), 4);
}

TEST(TestMonomLib, Plus) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom1(1.0, powers);
  Monom<3> monom2(10.0, powers);

  Monom<3> result = monom1 + monom2;

  EXPECT_DOUBLE_EQ(result.getCoefficient(), 11.0);
  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 1.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);
}

TEST(TestMonomLib, PlusThrowsWhenNonSimilar) {
  int powers1[3] = { 1, 2, 3 };
  int powers2[3] = { 3, 2, 1 };

  Monom<3> monom1(1.0, powers1);
  Monom<3> monom2(10.0, powers2);

  EXPECT_THROW(monom1 + monom2, std::invalid_argument);
}

TEST(TestMonomLib, Minus) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom1(5.0, powers);
  Monom<3> monom2(10.0, powers);

  Monom<3> result = monom1 - monom2;

  EXPECT_DOUBLE_EQ(result .getCoefficient(), -5.0);
  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 5.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);
}

TEST(TestMonomLib, MinusThrowWhenNonSimilar) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { -1, 0, 3 };
  Monom<3> monom2(10.0, powers2);

  EXPECT_THROW(monom1 - monom2, std::invalid_argument);
}

TEST(TestMonomLib, Mult) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { -1, 0, 3 };
  Monom<3> monom2(10.0, powers2);

  Monom<3> result = monom1 * monom2;

  EXPECT_DOUBLE_EQ(result.getCoefficient(), 220.0);
  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 10.0);

  EXPECT_EQ(result.getPower(0), 0);
  EXPECT_EQ(result.getPower(1), 2);
  EXPECT_EQ(result.getPower(2), 6);

  EXPECT_EQ(monom1.getPower(0), 1);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);

  EXPECT_EQ(monom2.getPower(0), -1);
  EXPECT_EQ(monom2.getPower(1), 0);
  EXPECT_EQ(monom2.getPower(2), 3);
}

TEST(TestMonomLib, Div) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { 2, 3, 4 };
  Monom<3> monom2(2.0, powers2);

  Monom<3> result = monom1 / monom2;

  EXPECT_DOUBLE_EQ(result.getCoefficient(), 11.0);
  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);
  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 2.0);

  EXPECT_EQ(result.getPower(0), 1);
  EXPECT_EQ(result.getPower(1), -1);
  EXPECT_EQ(result.getPower(2), -1);

  EXPECT_EQ(monom1.getPower(0), 3);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);

  EXPECT_EQ(monom2.getPower(0), 2);
  EXPECT_EQ(monom2.getPower(1), 3);
  EXPECT_EQ(monom2.getPower(2), 4);
}

TEST(TestMonomLib, DivThrowWhenDivByZero) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);
  int powers2[3] = { 2, 3, 4 };
  Monom<3> monom2(0.0, powers2);

  EXPECT_THROW(monom1 / monom2, std::invalid_argument);
}

TEST(TestMonomLib, MultEqualScalar) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(22.0, powers1);

  monom1 *= 2.0;

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 44.0);

  EXPECT_EQ(monom1.getPower(0), 1);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);
}

TEST(TestMonomLib, DivEqualScalar) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);

  monom1 /= 2.0;

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 11.0);

  EXPECT_EQ(monom1.getPower(0), 3);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);
}

TEST(TestMonomLib, DivEqualScalarThrowWhenDivByZero) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);

  EXPECT_THROW(monom1 /= 0.0, std::invalid_argument);

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);

  EXPECT_EQ(monom1.getPower(0), 3);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);
}

TEST(TestMonomLib, MultScalar) {
  int powers1[3] = { 1, 2, 3 };
  Monom<3> monom1(22.0, powers1);

  Monom<3> result = monom1 * 2.0;

  EXPECT_DOUBLE_EQ(result.getCoefficient(), 44.0);
  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);

  EXPECT_EQ(monom1.getPower(0), 1);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);
}

TEST(TestMonomLib, DivScalar) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);

  Monom<3> result = monom1 / 2.0;

  EXPECT_DOUBLE_EQ(result.getCoefficient(), 11.0);
  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);

  EXPECT_EQ(monom1.getPower(0), 3);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);
}

TEST(TestMonomLib, DivScalarThrowWhenDivByZero) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);

  EXPECT_THROW(monom1 / 0.0, std::invalid_argument);

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);

  EXPECT_EQ(monom1.getPower(0), 3);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);
}

TEST(TestMonomLib, UnaryMinus) {
  int powers1[3] = { 3, 2, 3 };
  Monom<3> monom1(22.0, powers1);

  Monom<3> result = -monom1;

  EXPECT_DOUBLE_EQ(result.getCoefficient(), -22.0);

  EXPECT_EQ(result.getPower(0), 3);
  EXPECT_EQ(result.getPower(1), 2);
  EXPECT_EQ(result.getPower(2), 3);

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);
  EXPECT_EQ(monom1.getPower(0), 3);
  EXPECT_EQ(monom1.getPower(1), 2);
  EXPECT_EQ(monom1.getPower(2), 3);
}

TEST(TestMonomLib, AssignmentOperator) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom1(22.0, powers);
  Monom<3> monom2;

  monom2 = monom1;

  EXPECT_DOUBLE_EQ(monom2.getCoefficient(), 22.0);
  EXPECT_EQ(monom2.getPower(0), 1);
  EXPECT_EQ(monom2.getPower(1), 2);
  EXPECT_EQ(monom2.getPower(2), 3);

  EXPECT_DOUBLE_EQ(monom1.getCoefficient(), 22.0);
}

TEST(TestMonomLib, AssignmentSelfAssignment) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom(22.0, powers);

  monom = monom;

  EXPECT_DOUBLE_EQ(monom.getCoefficient(), 22.0);
  EXPECT_EQ(monom.getPower(0), 1);
  EXPECT_EQ(monom.getPower(1), 2);
  EXPECT_EQ(monom.getPower(2), 3);
}

TEST(TestMonomLib, CalculateMonom) {
  int powers[3] = { 1, 2, 3 };
  Monom<3> monom(22.0, powers);

  double values[3] = { 2.0, 10.1, 3.0 };
  double result = monom.calculate(values);

  EXPECT_NEAR(result, 121187.88, 1e-6);
}

TEST(TestMonomLib, ZeroMonomOutput) {
  Monom<3> m;
  std::stringstream ss;
  ss << m;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestMonomLib, ConstantMonomOutput) {
  Monom<3> m(5.0);
  std::stringstream ss;
  ss << m;
  EXPECT_EQ(ss.str(), "5");
}


TEST(TestMonomLib, CoeffOneOutput) {
  int p[3] = { 1, 0, 0 };
  Monom<3> m(1.0, p);
  std::stringstream ss;
  ss << m;
  EXPECT_EQ(ss.str(), "x1");
}

TEST(TestMonomLib, CoeffMinusOneOuput) {
  int p[3] = { 1, 0, 0 };
  Monom<3> m(-1.0, p);
  std::stringstream ss;
  ss << m;
  EXPECT_EQ(ss.str(), "-x1");
}

TEST(TestMonomLib, VariablesOutput) {
  int p[3] = { 1, -2, 3 };
  Monom<3> m(2.5, p);
  std::stringstream ss;
  ss << m;
  EXPECT_EQ(ss.str(), "2.5x1x2^(-2)x3^3");
}
