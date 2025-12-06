// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_lexem/lexem.h"

TEST(TestLexemLib, LexemDefaultConstructor) {
  Lexem lexem;

  EXPECT_EQ(lexem.getName(), "");
  EXPECT_EQ(lexem.getType(), Constant);
}

TEST(TestLexemLib, LexemConstructorWithParams) {
  Lexem lexem("x1", Variable);

  EXPECT_EQ(lexem.getName(), "x1");
  EXPECT_EQ(lexem.getType(), Variable);
}

TEST(TestLexemLib, ConstantLexemConstructorWithParams) {
  ConstantLexem constant(3.14);

  EXPECT_EQ(constant.getName(), "3.140000");
  EXPECT_EQ(constant.getType(), Constant);
  EXPECT_DOUBLE_EQ(constant.getValue(), 3.14);
}

TEST(TestLexemLib, VariableLexemConstructorWithParams) {
  VariableLexem variable("y123");

  EXPECT_EQ(variable.getName(), "y123");
  EXPECT_EQ(variable.getType(), Variable);
}

TEST(TestLexemLib, BracketLexemConstructorWithParams) {
  BracketLexem open_bracket("{", true);

  EXPECT_EQ(open_bracket.getName(), "{");
  EXPECT_EQ(open_bracket.getType(), OpenBracket);
  EXPECT_TRUE(open_bracket.isOpen());

  BracketLexem closed_bracket("}", false);

  EXPECT_EQ(closed_bracket.getName(), "}");
  EXPECT_EQ(closed_bracket.getType(), ClosedBracket);
  EXPECT_FALSE(closed_bracket.isOpen());
}

TEST(TestLexemLib, OperatorLexemConstructorWithParams) {
  OperatorLexem operator_default("+");

  EXPECT_EQ(operator_default.getName(), "+");
  EXPECT_EQ(operator_default.getType(), Operator);
  EXPECT_EQ(operator_default.getPriority(), -1);

  OperatorLexem operator_param("*", 1);

  EXPECT_EQ(operator_param.getName(), "*");
  EXPECT_EQ(operator_param.getType(), Operator);
  EXPECT_EQ(operator_param.getPriority(), 1);
}

TEST(TestLexemLib, FunctionLexemConstructorWithParams) {
  const double PI = MathFunctions::PI;

  FunctionLexem function("sin", &MathFunctions::mySin);

  EXPECT_EQ(function.getName(), "sin");
  EXPECT_EQ(function.getType(), Function);
  EXPECT_NE(function.getFunction(), nullptr);
  EXPECT_NEAR(function.getFunction()(PI / 2), 1.0, 1e-10);
}
