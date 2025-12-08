// Copyright 2025 Smirnov Nikita

#include<string>
#include <map>
#include "../lib_expression/expression.h"

Expression::Expression(const std::string& str) : _is_valid(false) {
  try {
    _lexems = Parser::parse(str);
    _is_valid = true;

    extractVariables();

    buildPolishRecord();
  }
  catch (const std::exception& e) {
    throw;
  }
}

Expression::~Expression() {}

void Expression::buildPolishRecord() {
  TListStack<Lexem*> stack;

  for (auto it = _lexems.begin(); it != _lexems.end(); ++it) {
    Lexem* current = *it;

    switch (current->getType()) {
    case Constant:
    case Variable:
      _polish_rec.push_back(current->clone());
      break;

    case Function:
    case OpenBracket:
      stack.push(current->clone());
      break;

    case Operator: {
      while (!stack.is_empty()) {
        Lexem* top = stack.top();

        if (top->getType() == OpenBracket) {
          break;
        }

        if (top->getType() == Function) {
          _polish_rec.push_back(top->clone());
          stack.pop();
          delete top;
          continue;
        }

        if (top->getType() == Operator) {
          if (top->getPriority() > current->getPriority() ||
            (top->getPriority() == current->getPriority() &&
              isLeftAssociative(current))) {

            _polish_rec.push_back(top->clone());
            stack.pop();
            delete top;
            continue;
          }
        }
        break;
      }

      stack.push(current->clone());
      break;
      }

    case ClosedBracket: {
      while (!stack.is_empty()) {
        Lexem* top = stack.top();
        stack.pop();

        if (top->getType() == OpenBracket) {
          delete top;
          break;
        } else {
          _polish_rec.push_back(top->clone());
          delete top;
        }
      }
      break;
    }
    default:
      break;
    }
  }

  while (!stack.is_empty()) {
    Lexem* top = stack.top();
    stack.pop();

    _polish_rec.push_back(top->clone());
    delete top;
  }
}

bool Expression::isLeftAssociative(const Lexem* lexem) const {
  if (lexem->getType() != Operator) return false;

  std::string op = lexem->getName();

  if (op == "+" || op == "-" || op == "*" || op == "/") {
    return true;
  }

  if (op == "^") {
    return false;
  }

  return true;
}

std::string Expression::getPolishString() const {
  std::stringstream ss;
  for (auto it = _polish_rec.begin(); it != _polish_rec.end(); ++it) {
    const Lexem* lexem = *it;
    switch (lexem->getType()) {
    case Constant:
      ss << lexem->getValue() << " ";
      break;
    case Variable:
      ss << lexem->getName() << " ";
      break;
    case Operator:
      ss << lexem->getName() << " ";
      break;
    case Function:
      ss << lexem->getName() << " ";
      break;
    default:
      ss << "? ";
      break;
    }
  }
  return ss.str();
}

double Expression::calculate() const {
  std::map<std::string, double> empty_vars;
  return calculate(empty_vars);
}

double Expression::calculate(const std::map<std::string,
  double>& variables) const {
  if (!_is_valid) {
    throw std::runtime_error("Cannot evaluate invalid expression");
  }

  return calculatePolish(variables);
}

double Expression::calculatePolish(const std::map<std::string,
  double>& vars) const {
  TListStack<double> calc_stack;

  for (auto it = _polish_rec.begin(); it != _polish_rec.end(); ++it) {
    const Lexem* lexem = *it;

    switch (lexem->getType()) {
    case Constant: {
      calc_stack.push(lexem->getValue());
      break;
    }
    case Variable: {
      std::string var_name = lexem->getName();
      auto it_var = vars.find(var_name);
      if (it_var != vars.end()) {
        calc_stack.push(it_var->second);
      } else {
        calc_stack.push(0.0);
      }
      break;
    }
    case Operator: {
      double b = calc_stack.top();
      calc_stack.pop();
      double a = calc_stack.top();
      calc_stack.pop();

      double result = 0.0;
      std::string op = lexem->getName();

      if (op == "+") result = a + b;
      else if (op == "-") result = a - b;
      else if (op == "*") result = a * b;
      else if (op == "/") {
        if (b == 0.0) {
          throw std::runtime_error("Division by zero");
        }
        result = a / b;
      } else if (op == "^") result = pow(a, b);

      calc_stack.push(result);
      break;
    }
    case Function: {
      double arg = calc_stack.top();
      calc_stack.pop();

      MathFunctions::MathFunctionPtr func_ptr = lexem->getFunction();

      double result = func_ptr(arg);
      calc_stack.push(result);
      break;
    }
    default:
      break;
    }
  }

  double result = calc_stack.top();
  calc_stack.pop();

  return result;
}

void Expression::extractVariables() {
  for (auto it = _lexems.begin(); it != _lexems.end(); ++it) {
    Lexem* lexem = *it;
    if (lexem && lexem->getType() == TypeLexem::Variable) {
      bool found = false;
      for (const auto& var : _variables_list) {
        if (var == lexem->getName()) {
          found = true;
          break;
        }
      }
      if (!found) {
        _variables_list.push_back(lexem->getName());
      }
    }
  }
}
