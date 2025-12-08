// Copyright 2025 Smirnov Nikita

#ifndef LIB_LEXEM_LEXEM_H_
#define LIB_LEXEM_LEXEM_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "../lib_math_functions/math_functions.h"

enum TypeLexem { Constant, Variable, OpenBracket, ClosedBracket,
  Function, Operator };

class Lexem {
  std::string _name;
  TypeLexem _type;

 public:
  Lexem() : _name(""), _type(Constant) {}
  Lexem(const std::string& name, TypeLexem type) : _name(name), _type(type) {}

  std::string getName() const noexcept { return _name; }
  TypeLexem getType() const noexcept { return _type; }

  virtual double getValue() const { return 0.0; }
  virtual bool isOpen() const noexcept { return false; }
  virtual MathFunctions::MathFunctionPtr getFunction() const noexcept{ return nullptr; }
  virtual int getPriority() const noexcept { return -1; }
};

class ConstantLexem : public Lexem {
  double _value;

 public:
  explicit ConstantLexem(double value)
     : Lexem(doubleToString(value), Constant), _value(value) {}

  double getValue() const noexcept override { return _value; }

 private:
  static std::string doubleToString(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    return oss.str();
  }
};

class VariableLexem : public Lexem {
 public:
  explicit VariableLexem(const std::string& name) : Lexem(name, Variable) {}
};

class BracketLexem : public Lexem {
  bool _isOpen;

 public:
  BracketLexem(const std::string& name, bool isOpen)
    : Lexem(name, isOpen ? OpenBracket : ClosedBracket), _isOpen(isOpen) {}

  bool isOpen() const noexcept override { return _isOpen; }
};

class FunctionLexem : public Lexem {
  MathFunctions::MathFunctionPtr _function;

 public:
  FunctionLexem(const std::string& name,
    MathFunctions::MathFunctionPtr function)
    : Lexem(name, Function), _function(function) {}

  MathFunctions::MathFunctionPtr getFunction() const noexcept override
  { return _function; }
};

class OperatorLexem : public Lexem {
  int _priority;
 public:
  explicit OperatorLexem(const std::string& name, int priority = -1)
    : Lexem(name, Operator), _priority(priority) {}

  int getPriority() const noexcept override { return _priority; }
};

#endif  // LIB_LEXEM_LEXEM_H_
