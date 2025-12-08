// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include <string>
#include "../lib_parser/parser.h"

TEST(TestParserLib, ValidNumbers) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("0")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("123")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("999")));
}

TEST(TestParserLib, ValidVariables) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("x")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("var")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("_var")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("var123")));
}

TEST(TestParserLib, ValidOperations) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("a + b")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("x - y")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("a * b / c")));
}

TEST(TestParserLib, ValidBrackets) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("(a + b)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("[(a + b)]")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("{a * (b + c)}")));
}

TEST(TestParserLib, VariableStartsWithDigit) {
  try {
    Parser::isValidExpression(std::string("234 + 123var"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 9);
    EXPECT_STREQ(e.getMsg(), "Variable cannot start with digit");
  }
}

TEST(TestParserLib, MissingFirstOperand) {
  try {
    Parser::isValidExpression(std::string("+ b"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(), "Missing first operand in operation +");
  }
}

TEST(TestParserLib, MissingSecondOperand) {
  try {
    Parser::isValidExpression(std::string("a +"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 3);
    EXPECT_STREQ(e.getMsg(), "Missing second operand in operation +");
  }

  try {
    Parser::isValidExpression(std::string("a  *+ b"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 4);
    EXPECT_STREQ(e.getMsg(), "Missing second operand in operation *");
  }
}

TEST(TestParserLib, MissingOperation) {
  try {
    Parser::isValidExpression(std::string("x y"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 2);
    EXPECT_STREQ(e.getMsg(), "Missing operation");
  }
}

TEST(TestParserLib, EmptyParentheses) {
  try {
    Parser::isValidExpression(std::string("a + ( )"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 6);
    EXPECT_STREQ(e.getMsg(), "Empty parentheses");
  }
}

TEST(TestParserLib, UnmatchedBrackets) {
  try {
    Parser::isValidExpression(std::string("a + b)"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 6);
    EXPECT_STREQ(e.getMsg(), "Missing opened bracket");
  }

  try {
    Parser::isValidExpression(std::string("(a + b"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(), "Missing closed bracket");
  }

  try {
    Parser::isValidExpression(std::string("([x - y)]"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 8);
    EXPECT_STREQ(e.getMsg(), "Unmatched [ and )");
  }
}

TEST(TestParserLib, InvalidCharacters) {
  try {
    Parser::isValidExpression(std::string("a @ b"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 3);
    EXPECT_STREQ(e.getMsg(), "Invalid character '@'");
  }
  try {
    Parser::isValidExpression(std::string("var$name"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 4);
    EXPECT_STREQ(e.getMsg(), "Invalid character '$'");
  }
}

TEST(TestParserLib, EmptyExpression) {
  try {
    Parser::isValidExpression(std::string(""));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 0);
    EXPECT_STREQ(e.getMsg(), "Empty expression");
  }
  try {
    Parser::isValidExpression(std::string("   "));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 0);
    EXPECT_STREQ(e.getMsg(), "Empty expression");
  }
}

TEST(TestParserLib, UnaryOperator) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~x")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~123")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~(a + b)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~_var2")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~x + y")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("a * (~b)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~(~x)")));

  try {
    Parser::isValidExpression(std::string("~"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(), "Missing operand for unary operator ~");
  }
  try {
    Parser::isValidExpression(std::string("a ~"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 3);
    EXPECT_STREQ(e.getMsg(), "Missing operand for unary operator ~");
  }
  try {
    Parser::isValidExpression(std::string("~ + b"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(), "Missing operand for unary operator ~");
  }
}

TEST(TestParserLib, Modulus) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|x|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|123|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|a + b|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|~x|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|(a + b) * c|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("a + |b| * c")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("||x||")));

  try {
    Parser::isValidExpression(std::string("|"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(), "Missing closing '|'");
  }

  try {
    Parser::isValidExpression(std::string("| |"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 2);
    EXPECT_STREQ(e.getMsg(), "Empty modulus");
  }

  try {
    Parser::isValidExpression(std::string("x|"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 2);
    EXPECT_STREQ(e.getMsg(), "Unexpected '|'");
  }

  try {
    Parser::isValidExpression(std::string("|x"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(), "Missing closing '|'");
  }

  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|(|x| + |y|)|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("{ [ |a| ] }")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~|x| + |~y|")));
}

TEST(TestParserLib, ValidDecimalNumbers) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("0.5")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("3.14")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("123.456")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("0.0")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("999.999")));
}

TEST(TestParserLib, InvalidDecimalNumbers) {
  try {
    Parser::isValidExpression(std::string(".5"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(), "Number cannot start with decimal point");
  }

  try {
    Parser::isValidExpression(std::string("5."));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 2);
    EXPECT_STREQ(e.getMsg(), "Number cannot end with decimal point");
  }

  try {
    Parser::isValidExpression(std::string("3..14"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 3);
    EXPECT_STREQ(e.getMsg(), "Multiple decimal points in number");
  }

  try {
    Parser::isValidExpression(std::string("1.2.3"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 4);
    EXPECT_STREQ(e.getMsg(), "Multiple decimal points in number");
  }
}

TEST(TestParserLib, ValidFunctions) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("sin(x)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("ctg(x)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("cos(30)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("tg(a + b)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("exp(2.5)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("sqrt(16)")));

  EXPECT_NO_THROW(Parser::isValidExpression(std::string("sin (x)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("cos ( 30 )")));

  EXPECT_NO_THROW(Parser::isValidExpression(std::string("sin(cos(x))")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("tg(sin(30) + cos(45))")));

  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~sin(x)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|sin(x)|")));
}

TEST(TestParserLib, InvalidFunctions) {
  try {
    Parser::isValidExpression(std::string("unknown(x)"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 0);
    EXPECT_STREQ(e.getMsg(), "Unknown function 'unknown'");
  }
  try {
    Parser::isValidExpression(std::string("sin x"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 1);
    EXPECT_STREQ(e.getMsg(),
      "'sin' is a function name, not a variable. Use parentheses: sin(argument)");
  }
  try {
    Parser::isValidExpression(std::string("sin()"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 4);
    EXPECT_STREQ(e.getMsg(), "Empty parentheses");
  }
}

TEST(TestParserLib, VariableWithDot) {
  try {
    Parser::isValidExpression(std::string("var.name"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 4);
    EXPECT_STREQ(e.getMsg(), "Variable cannot contains a decimal point");
  }

  try {
    Parser::isValidExpression(std::string("x.123"));
  }
  catch (const PositionException& e) {
    EXPECT_EQ(e.getPosition(), 2);
    EXPECT_STREQ(e.getMsg(), "Variable cannot contains a decimal point");
  }
}

TEST(TestParserLib, FunctionAsVariableError) {
  std::string expr1 = "sin";
  std::string expr2 = "sin + x";
  std::string expr3 = "x * cos";

  EXPECT_THROW(Parser::isValidExpression(expr1), PositionException);
  EXPECT_THROW(Parser::isValidExpression(expr2), PositionException);
  EXPECT_THROW(Parser::isValidExpression(expr3), PositionException);

  try {
    Parser::isValidExpression(std::string("sin"));
  }
  catch (const PositionException& e) {
    EXPECT_STREQ(e.getMsg(),
      "'sin' is a function name, not a variable. Use parentheses: sin(argument)");
  }

  try {
    Parser::isValidExpression(std::string("x + sqrt"));
  }
  catch (const PositionException& e) {
    EXPECT_STREQ(e.getMsg(),
      "'sqrt' is a function name, not a variable. Use parentheses: sqrt(argument)");
  }
}

TEST(TestParserLib, ComplexExpressions) {
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("3.14 * x^2 + sin(30) / cos(45)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("(a + b) * (c - d) / (e ^ f)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|x - y| + (~sqrt(z))")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("sin((a + b) * 3.14)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~|~x + (~y)|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("sin(|cos(x)|) + tg(|x + y|)")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("(|x| + |y|) * (|a| - |b|) / |c|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~(~(~x + (~y)) * (~|z|))")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("{[((a + b) * {c - [d / e]})]}^|f|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("sin(cos(tg(exp(sqrt(x)))))")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("|sin(x)| * |cos(y)| / |tg(z)|")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("~(x + |~y - z|) * (|a| / (~b))")));
  EXPECT_NO_THROW(Parser::isValidExpression(std::string("((a + b) * (c - d)) ^ (e / f) + |g|")));
}

TEST(TestParserLib, ModulusTransformation) {
  std::string expr1 = "|x|";
  Parser::isValidExpression(expr1);
  EXPECT_EQ(expr1, "abs(x)");

  std::string expr2 = "|123|";
  Parser::isValidExpression(expr2);
  EXPECT_EQ(expr2, "abs(123)");

  std::string expr3 = "| x |";
  Parser::isValidExpression(expr3);
  EXPECT_EQ(expr3, "abs( x )");

  std::string expr4 = "3*|x|";
  Parser::isValidExpression(expr4);
  EXPECT_EQ(expr4, "3*abs(x)");

  std::string expr5 = "||x||";
  Parser::isValidExpression(expr5);
  EXPECT_EQ(expr5, "abs(abs(x))");

  std::string expr6 = "|x+y|";
  Parser::isValidExpression(expr6);
  EXPECT_EQ(expr6, "abs(x+y)");

  std::string expr7 = "|a|+|b|+|c|";
  Parser::isValidExpression(expr7);
  EXPECT_EQ(expr7, "abs(a)+abs(b)+abs(c)");

  std::string expr8 = "(|x|)";
  Parser::isValidExpression(expr8);
  EXPECT_EQ(expr8, "(abs(x))");

  std::string expr9 = "|3.14|";
  Parser::isValidExpression(expr9);
  EXPECT_EQ(expr9, "abs(3.14)");

  std::string expr10 = "sin(|x|)";
  Parser::isValidExpression(expr10);
  EXPECT_EQ(expr10, "sin(abs(x))");

  std::string expr11 = "||||x||||";
  Parser::isValidExpression(expr11);
  EXPECT_EQ(expr11, "abs(abs(abs(abs(x))))");

  std::string expr12 = "x + 5 * ||y| - |x||";
  Parser::isValidExpression(expr12);
  EXPECT_EQ(expr12, "x + 5 * abs(abs(y) - abs(x))");

  std::string expr13 = "|sin(x) + cos(y)|";
  Parser::isValidExpression(expr13);
  EXPECT_EQ(expr13, "abs(sin(x) + cos(y))");

  std::string expr14 = "sin(|x + 3.14|) * cos(|y - 2.5|)";
  Parser::isValidExpression(expr14);
  EXPECT_EQ(expr14, "sin(abs(x + 3.14)) * cos(abs(y - 2.5))");

  std::string expr15 = "|sin(|x|) + cos(|y|)|";
  Parser::isValidExpression(expr15);
  EXPECT_EQ(expr15, "abs(sin(abs(x)) + cos(abs(y)))");

  std::string expr16 = "sqrt(|x^2 + y^2|) / |tg(z)|";
  Parser::isValidExpression(expr16);
  EXPECT_EQ(expr16, "sqrt(abs(x^2 + y^2)) / abs(tg(z))");

  std::string expr17 = "exp(||x||) + |sin(cos(tg(x)))|";
  Parser::isValidExpression(expr17);
  EXPECT_EQ(expr17, "exp(abs(abs(x))) + abs(sin(cos(tg(x))))");

  std::string expr18 = "~|~sin(x) + cos(|~y|)| * |tg(z)|";
  Parser::isValidExpression(expr18);
  EXPECT_EQ(expr18, "~abs(~sin(x) + cos(abs(~y))) * abs(tg(z))");

  std::string expr19 = "|(sin(x) * |cos(y)|) / (|tg(z)|^2)|";
  Parser::isValidExpression(expr19);
  EXPECT_EQ(expr19, "abs((sin(x) * abs(cos(y))) / (abs(tg(z))^2))");

  std::string expr20 = "{ [ |sin(|cos(|x|)|)| ] }";
  Parser::isValidExpression(expr20);
  EXPECT_EQ(expr20, "{ [ abs(sin(abs(cos(abs(x))))) ] }");

  std::string expr21 = "||sin(x)| - |cos(y)|| + ||tg(z)| * |ctg(w)||";
  Parser::isValidExpression(expr21);
  EXPECT_EQ(expr21, "abs(abs(sin(x)) - abs(cos(y))) + abs(abs(tg(z)) * abs(ctg(w)))");
}

TEST(TestParserLib, ParseNumVarOp) {
  std::string expr = "1.2 + xyz1";

  try {
    TList<Lexem*> lexems = Parser::parse(expr);

    EXPECT_EQ(lexems.size(), 3);

    auto it = lexems.begin();

    const Lexem* lex1 = *it;
    EXPECT_EQ(lex1->getType(), Constant);
    EXPECT_DOUBLE_EQ(lex1->getValue(), 1.2);

    ++it;
    const Lexem* lex2 = *it;
    EXPECT_EQ(lex2->getType(), Operator);
    EXPECT_EQ(lex2->getPriority(), 1);

    ++it;
    const Lexem* lex3 = *it;
    EXPECT_EQ(lex3->getType(), Variable);
    EXPECT_EQ(lex3->getName(), "xyz1");

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
      delete* it;
    }

  } catch (const std::exception& e) {
    FAIL() << "Exception: " << e.what();
  }
}

TEST(TestParserLib, ParseUnaryMinusWithPriority) {
  std::string expr = "~x * y";

  try {
    TList<Lexem*> lexems = Parser::parse(expr);

    EXPECT_EQ(lexems.size(), 5);

    auto it = lexems.begin();

    EXPECT_EQ((*it)->getType(), Constant);
    EXPECT_DOUBLE_EQ((*it)->getValue(), 0.0);
    ++it;

    EXPECT_EQ((*it)->getType(), Operator);
    EXPECT_EQ((*it)->getName(), "-");
    EXPECT_EQ((*it)->getPriority(), 2);
    ++it;

    EXPECT_EQ((*it)->getType(), Variable);
    ++it;

    EXPECT_EQ((*it)->getType(), Operator);
    EXPECT_EQ((*it)->getName(), "*");
    EXPECT_EQ((*it)->getPriority(), 2);
    ++it;

    EXPECT_EQ((*it)->getType(), Variable);
    ++it;

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
      delete* it;
    }

  } catch (const std::exception& e) {
    FAIL() << "Exception: " << e.what();
  }
}

TEST(TestParserLib, ParseUltimateComplexExpression) {
  std::string expr = "~(sin(x + 2) + cos(y)) * (tg(a) - [b * {c + sqrt(d)}])";

  try {
    TList<Lexem*> lexems = Parser::parse(expr);

    EXPECT_EQ(lexems.size(), 35);

    int types[5] = { 0 };
    int functions = 0;

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
      Lexem* lex = *it;
      if (lex->getType() == Constant) types[0]++;
      else if (lex->getType() == Variable) types[1]++;
      else if (lex->getType() == Operator) types[2]++;
      else if (lex->getType() == OpenBracket) types[3]++;
      else if (lex->getType() == ClosedBracket) types[4]++;
      else if (lex->getType() == Function) functions++;
    }

    EXPECT_EQ(types[0], 2);

    EXPECT_EQ(types[1], 6);

    EXPECT_EQ(types[2], 7);

    EXPECT_EQ(types[3], 8);

    EXPECT_EQ(types[4], 8);

    EXPECT_EQ(functions, 4);

    EXPECT_EQ(types[3], types[4]);

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
      delete* it;
    }
  } catch (const std::exception& e) {
    FAIL() << "Exception: " << e.what();
  }
}

TEST(TestParserLib, ParseNestedModulus) {
  std::string expr = "||x|| + |y|";

  try {
    TList<Lexem*> lexems = Parser::parse(expr);

    EXPECT_EQ(lexems.size(), 12);

    int abs_count = 0;
    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
      if ((*it)->getType() == Function && (*it)->getName() == "abs") {
        abs_count++;
      }
    }
    EXPECT_EQ(abs_count, 3);
  }
  catch (const std::exception& e) {
    FAIL() << "Exception: " << e.what();
  }
}

TEST(TestParserLib, ParseModulusInFunction) {
  std::string expr = "sin(|x|) + cos(|y|)";

  try {
    TList<Lexem*> lexems = Parser::parse(expr);

    EXPECT_EQ(lexems.size(), 15);

    int abs_count = 0;
    int sin_count = 0;
    int cos_count = 0;

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
      if ((*it)->getType() == Function) {
        std::string name = (*it)->getName();
        if (name == "abs") abs_count++;
        else if (name == "sin") sin_count++;
        else if (name == "cos") cos_count++;
      }
    }

    EXPECT_EQ(abs_count, 2);
    EXPECT_EQ(sin_count, 1);
    EXPECT_EQ(cos_count, 1);

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
      delete* it;
    }

  }
  catch (const std::exception& e) {
    FAIL() << "Exception: " << e.what();
  }
}
