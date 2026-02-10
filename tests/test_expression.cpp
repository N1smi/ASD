// Copyright 2025 Smirnov Nikita
#include <gtest/gtest.h>
#include <map>
#include <string>
#include "../lib_expression/expression.h"

TEST(TestExpressionLib, SimpleOps) {
  Expression e1("a + b");
  EXPECT_EQ(e1.getPolishString(), "a b + ");

  Expression e2("a * b + c");
  EXPECT_EQ(e2.getPolishString(), "a b * c + ");

  Expression e3("a + b * c");
  EXPECT_EQ(e3.getPolishString(), "a b c * + ");
}

TEST(TestExpressionLib, Brackets) {
  Expression e1("(a + b) * c");
  EXPECT_EQ(e1.getPolishString(), "a b + c * ");

  Expression e2("a * (b + c)");
  EXPECT_EQ(e2.getPolishString(), "a b c + * ");
}

TEST(TestExpressionLib, LeftAssociative) {
  Expression e1("a - b - c");
  EXPECT_EQ(e1.getPolishString(), "a b - c - ");

  Expression e2("a / b / c");
  EXPECT_EQ(e2.getPolishString(), "a b / c / ");
}

TEST(TestExpressionLib, RightAssociative) {
  Expression e1("a ^ b ^ c");
  EXPECT_EQ(e1.getPolishString(), "a b c ^ ^ ");
}

TEST(TestExpressionLib, Functions) {
  Expression e1("sin(x)");
  EXPECT_EQ(e1.getPolishString(), "x sin ");

  Expression e2("sin(x + y)");
  EXPECT_EQ(e2.getPolishString(), "x y + sin ");

  Expression e3("sin(cos(x))");
  EXPECT_EQ(e3.getPolishString(), "x cos sin ");
}

TEST(TestExpressionLib, UnaryMinus) {
  Expression e1("~x");
  EXPECT_EQ(e1.getPolishString(), "0 x - ");

  Expression e2("x * (~y)");
  EXPECT_EQ(e2.getPolishString(), "x 0 y - * ");
}

TEST(TestExpressionLib, Modulus) {
  Expression e1("|x|");
  EXPECT_EQ(e1.getPolishString(), "x abs ");

  Expression e2("|x + y|");
  EXPECT_EQ(e2.getPolishString(), "x y + abs ");

  Expression e3("||x||");
  EXPECT_EQ(e3.getPolishString(), "x abs abs ");
}

TEST(TestExpressionLib, ComplexExpressions) {
  Expression e1("3 + 4 * 2 / (1 - 5) ^ 2");
  EXPECT_EQ(e1.getPolishString(), "3 4 2 * 1 5 - 2 ^ / + ");

  Expression e2("sin(x) + cos(y) * 2");
  EXPECT_EQ(e2.getPolishString(), "x sin y cos 2 * + ");
}

TEST(TestExpressionLib, AllBracketTypes) {
  Expression e1("(a + [b * {c - d}])");
  EXPECT_EQ(e1.getPolishString(), "a b c d - * + ");
}

TEST(TestExpressionLib, BasicCalculate) {
  Expression e("2 + 3 * 4");
  EXPECT_DOUBLE_EQ(e.calculate(), 14.0);
}

TEST(TestExpressionLib, VariablesCalculate) {
  Expression e("x * y + z");
  std::map<std::string, double> vars = { {"x", 2}, {"y", 3}, {"z", 4} };
  EXPECT_DOUBLE_EQ(e.calculate(vars), 10.0);
}

TEST(TestExpressionLib, FunctionsCalculate) {
  Expression e("sin(4) + cos(5)");
  EXPECT_NEAR(e.calculate(), -0.47314030984, 1e-10);
}

TEST(TestExpressionLib, DivisionByZero) {
  Expression e("5 / 0");
  EXPECT_THROW(e.calculate(), std::runtime_error);
}

TEST(TestExpressionLib, ComplexCalculate) {
  Expression e("3 + 4 * 2 / (1 - 5) ^ 2");
  EXPECT_DOUBLE_EQ(e.calculate(), 3.5);
}

TEST(TestExpressionLib, PowerAssociativityCalculate) {
  Expression e("2 ^ 3 ^ 2");
  EXPECT_DOUBLE_EQ(e.calculate(), 512.0);
}

TEST(TestExpressionLib, ModulusCalculate) {
  Expression e("|~5| + |3 - 7|");
  EXPECT_DOUBLE_EQ(e.calculate(), 9.0);
}

TEST(TestExpressionLib, UnaryMinusCalculation) {
  Expression e("~5 * (~2)");
  EXPECT_DOUBLE_EQ(e.calculate(), 10.0);
}
