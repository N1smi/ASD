// Copyright 2025 Smirnov Nikita

#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_

#include <string>
#include <vector>
#include <stdexcept>
#include "../lib_tlist/tlist.h"
#include "../lib_tlist_stack/tlist_stack.h"
#include "../lib_lexem/lexem.h"

class PositionException : public std::invalid_argument {
 private:
  size_t _position;
  std::string _msg;
 public:
  PositionException(const std::string& msg, size_t pos)
    : std::invalid_argument("Error in function 'Parser::parse()' at "
      + std::to_string(pos) + " symbol: " + msg),
    _position(pos), _msg(msg) {
  }

  size_t getPosition() const { return _position; }
  const char* getMsg() const { return _msg.c_str(); }
};

struct ModInfo {
  size_t position;
  bool isOpening;
};

enum CharType {
  END, DIGIT, DOT, OPERATOR,
  SPACE, UNKNOWN, LETTER, UNDERSCORE, UNARY_MINUS,
  BRACKET_OPEN, BRACKET_CLOSE
};

enum AState { START, IN_NUMBER, IN_OPERATOR, IN_IDENTIFIER };

namespace Parser {
TList<Lexem*> parse(const std::string& expression);

void addLexem(TList<Lexem*>& lexems, const std::string& token, AState state);

int getOperatorPriority(const std::string& op);

CharType getCharType(char c);

AState getNextState(AState current, CharType type, const std::string& token);

void isValidExpression(std::string& expression);

void validateNumber(const std::string& token, size_t start_pos);

void validateVariable(const std::string& token, size_t start_pos);

void validateSecondOperand(const std::string& expression, size_t start_pos);

std::string transformModulusInExpression(const std::string& expression,
   const std::vector<ModInfo>& modulus_info);
}  // namespace Parser

#endif  // LIB_PARSER_PARSER_H_
