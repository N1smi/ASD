// Copyright 2025 Smirnov Nikita

#include <cctype>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include "../lib_parser/parser.h"

TList<Lexem*> Parser::parse(const std::string& expr) {
  TList<Lexem*> lexems;

  std::string expression = expr;
  isValidExpression(expression);

  AState current_state = START;
  std::string current_token;

  for (size_t i = 0; i <= expression.length(); i++) {
    char c = (i < expression.length()) ? expression[i] : '\0';

    CharType type = getCharType(c);

    if (type == SPACE || type == END) {
      if (!current_token.empty()) {
        addLexem(lexems, current_token, current_state);
        current_token.clear();
      }
      current_state = START;
      continue;
    }

    if (type == BRACKET_OPEN || type == BRACKET_CLOSE) {
      if (!current_token.empty()) {
        addLexem(lexems, current_token, current_state);
        current_token.clear();
      }

      std::string bracket(1, c);
      bool isOpen = (type == BRACKET_OPEN);
      lexems.push_back(new BracketLexem(bracket, isOpen));

      current_state = START;

      continue;
    }

    AState next_state = getNextState(current_state, type, current_token);

    if (next_state != current_state && !current_token.empty()) {
      addLexem(lexems, current_token, current_state);
      current_token.clear();
    }

    if (type != END) {
      current_token += c;
    }

    current_state = next_state;
  }

  return lexems;
}

void Parser::addLexem(TList<Lexem*>& lexems,
  const std::string& token, AState state) {
  if (token.empty()) return;

  switch (state) {
  case IN_NUMBER: {
    double value = std::stod(token);
    lexems.push_back(new ConstantLexem(value));
    break;
  }

  case IN_IDENTIFIER: {
    if (MathFunctions::isFunction(token)) {
      MathFunctions::MathFunctionPtr ptr = MathFunctions::getFunction(token);
      lexems.push_back(new FunctionLexem(token, ptr));
      break;
    }
    lexems.push_back(new VariableLexem(token));
    break;
  }

  case IN_OPERATOR: {
    int priority = getOperatorPriority(token);
    if (token == "~") {
      lexems.push_back(new ConstantLexem(0.0));
      lexems.push_back(new OperatorLexem("-", priority));
    } else {
      lexems.push_back(new OperatorLexem(token, priority));
    }
    break;
  }

  default:
    break;
  }
}

AState Parser::getNextState(AState current,
  CharType type, const std::string& token) {
  switch (current) {
  case START:
    if (type == DIGIT || type == DOT) return IN_NUMBER;
    if (type == LETTER || type == UNDERSCORE) return IN_IDENTIFIER;
    if (type == OPERATOR || type == UNARY_MINUS) return IN_OPERATOR;
    break;

  case IN_NUMBER:
    if (type == DIGIT || type == DOT) return IN_NUMBER;
    if (type == LETTER || type == UNDERSCORE) return IN_IDENTIFIER;
    if (type == OPERATOR || type == UNARY_MINUS) return IN_OPERATOR;
    break;

  case IN_IDENTIFIER:
    if (type == LETTER || type == DIGIT || type == UNDERSCORE)
      return IN_IDENTIFIER;
    if (type == OPERATOR || type == UNARY_MINUS) return IN_OPERATOR;
    break;

  case IN_OPERATOR:
    if (type == DIGIT || type == DOT) return IN_NUMBER;
    if (type == LETTER || type == UNDERSCORE) return IN_IDENTIFIER;
    if (type == OPERATOR || type == UNARY_MINUS) return IN_OPERATOR;
    break;
  }

  return START;
}

CharType Parser::getCharType(char c) {
  if (c == '\0') return END;
  if (c == ' ') return SPACE;
  if (isdigit(c)) return DIGIT;
  if (c == '.') return DOT;
  if (isalpha(c)) return LETTER;
  if (c == '_') return UNDERSCORE;
  if (c == '~') return UNARY_MINUS;
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
    return OPERATOR;
  }
  if (c == '(' || c == '[' || c == '{') return BRACKET_OPEN;
  if (c == ')' || c == ']' || c == '}') return BRACKET_CLOSE;
  return UNKNOWN;
}

int Parser::getOperatorPriority(const std::string& op) {
  if (op == "^") return 3;
  if (op == "*" || op == "/" || op == "~") return 2;
  return 1;
}

void Parser::isValidExpression(std::string& expression) {
  if (expression.empty()) {
    throw PositionException("Empty expression", 0);
  }

  TListStack<std::pair<char, size_t>> brackets(expression.length());

  std::vector<ModInfo> modulus_info;

  bool expect_operand = true;

  for (size_t i = 0; i < expression.length(); i++) {
    char c = expression[i];

    if (c == ' ') {
      continue;
    }

    if (std::isalnum(c) || c == '_' || c == '.') {
      if (!expect_operand) {
        throw PositionException("Missing operation", i);
      }

      size_t start_pos = i;

      while (i < expression.length() && (std::isalnum(expression[i])
        || expression[i] == '_' || expression[i] == '.')) {
        ++i;
      }
      --i;

      std::string token = expression.substr(start_pos, i - start_pos + 1);

      if (std::isdigit(token[0]) || token[0] == '.') {
        validateNumber(token, start_pos);
      } else {
        size_t j = i + 1;
        while (j < expression.length() && expression[j] == ' ') {
          j++;
        }
        if (j < expression.length() && expression[j] == '(') {
          if (!MathFunctions::isFunction(token)) {
            throw PositionException("Unknown function '"
              + token + "'", start_pos);
          }
        } else {
          validateVariable(token, start_pos);
        }
      }
      expect_operand = false;
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
      if (expect_operand) {
        throw PositionException("Missing first operand in operation "
          + std::string(1, c), i + 1);
      }

      validateSecondOperand(expression, i);

      expect_operand = true;
    } else if (c == '~') {
      validateSecondOperand(expression, i);
      expect_operand = true;
    } else if (c == '(' || c == '[' || c == '{') {
      brackets.push({ c, i });
      expect_operand = true;
    } else if (c == ')' || c == ']' || c == '}') {
      if (expect_operand) {
        throw PositionException("Empty parentheses", i);
      }
      if (brackets.is_empty()) {
        throw PositionException("Missing opened bracket", i + 1);
      }

      char top = brackets.top().first;
      if ((c == ')' && top != '(') ||
        (c == ']' && top != '[') ||
        (c == '}' && top != '{')) {
        throw PositionException("Unmatched " +
          std::string(1, top) + " and " + std::string(1, c), i + 1);
      }

      brackets.pop();
      expect_operand = false;
    } else if (c == '|') {
      bool isOpening = expect_operand;

      modulus_info.push_back({ i, isOpening });

      if (expect_operand) {
        brackets.push({ c, i });
        expect_operand = true;
      } else {
        if (brackets.is_empty() || brackets.top().first != '|') {
          throw PositionException("Unexpected '|'", i + 1);
        }
        brackets.pop();
        expect_operand = false;
      }
    } else {
      throw PositionException("Invalid character '"
        + std::string(1, c) + "'", i + 1);
    }
  }

  if (!brackets.is_empty()) {
     if (brackets.size() >= 2) {
       auto top1 = brackets.top();
       brackets.pop();
       auto top2 = brackets.top();
       brackets.push(top1);
       if (top1.first == '|' && top2.first == '|') {
         throw PositionException("Empty modulus", top1.second);
       }
     }

    size_t bracket_pos = brackets.top().second;
    char bracket_char = brackets.top().first;

    if (bracket_char == '|') {
      throw PositionException("Missing closing '|'", bracket_pos + 1);
    } else {
      throw PositionException("Missing closed bracket", bracket_pos + 1);
    }
  }

  if (!modulus_info.empty()) {
    expression = transformModulusInExpression(expression, modulus_info);
  }
}

void Parser::validateNumber(const std::string& token,
  size_t start_pos) {
  if (token.front() == '.') {
    throw PositionException("Number cannot start with decimal point",
      start_pos + 1);
  }
  if (token.back() == '.') {
    throw PositionException("Number cannot end with decimal point",
      start_pos + token.length());
  }

  bool has_dot = false;
  for (size_t i = 0; i < token.length(); i++) {
    if (token[i] == '.') {
      if (has_dot) {
        throw PositionException("Multiple decimal points in number",
          start_pos + i + 1);
      }
      has_dot = true;
    } else if (!std::isdigit(token[i])) {
      throw PositionException("Variable cannot start with digit",
        start_pos + i);
    }
  }
}

void Parser::validateVariable(const std::string& token, size_t start_pos) {
  for (size_t i = 0; i < token.length(); i++) {
    if (token[i] == '.') {
      throw PositionException("Variable cannot contains a decimal point",
        start_pos + i + 1);
    }
  }

  if (MathFunctions::isFunction(token)) {
    throw PositionException("'" + token +
      "' is a function name, not a variable. "
      "Use parentheses: " + token + "(argument)", start_pos + 1);
  }
}

void Parser::validateSecondOperand(const std::string& expression, size_t start_pos) {
  bool has_operand_after = false;
  for (size_t j = start_pos + 1; j < expression.length(); j++) {
    if (expression[j] == ' ') continue;
    if (std::isalnum(expression[j]) || expression[j] == '(' ||
      expression[j] == '[' || expression[j] == '{' ||
      expression[j] == '|') {
      has_operand_after = true;
      break;
    }

    if (expression[j] == '+' || expression[j] == '-' ||
      expression[j] == '*' || expression[j] == '/' ||
      expression[j] == '^' || expression[j] == ')' ||
      expression[j] == ']' || expression[j] == '}' ||
      expression[j] == '~' || expression[j] == '|'){
      break;
    }
  }

  if (!has_operand_after) {
    if (expression[start_pos] == '~') {
      throw PositionException("Missing operand for unary operator "
        + std::string(1, expression[start_pos]), start_pos + 1);
    } else {
      throw PositionException("Missing second operand in operation "
        + std::string(1, expression[start_pos]), start_pos + 1);
    }
  }
}

std::string Parser::transformModulusInExpression(const std::string& expression,
   const std::vector<ModInfo>& modulus_info) {
  if (modulus_info.empty()) {
    return expression;
  }

  std::vector<ModInfo> sorted_info = modulus_info;

  std::sort(sorted_info.begin(), sorted_info.end(),
    [](const ModInfo& a, const ModInfo& b) {
      return a.position < b.position;
    });

  std::string result;
  size_t last_pos = 0;

  for (const auto& info : sorted_info) {
    result += expression.substr(last_pos, info.position - last_pos);

    if (info.isOpening) {
      result += "abs(";
    } else {
      result += ")";
    }

    last_pos = info.position + 1;
  }

  if (last_pos < expression.length()) {
    result += expression.substr(last_pos);
  }

  return result;
}
