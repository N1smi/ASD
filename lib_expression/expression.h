// Copyright 2025 Smirnov Nikita

#ifndef LIB_EXPRESSION_EXPRESSION_H_
#define LIB_EXPRESSION_EXPRESSION_H_

#include<string>
#include <map>
#include "../lib_tlist/tlist.h"
#include "../lib_tlist_stack/tlist_stack.h"
#include "../lib_tvector/tvector.h"
#include "../lib_lexem/lexem.h"
#include "../lib_parser/parser.h"

class Expression {
  TList<Lexem*> _lexems;
  TList<Lexem*> _polish_rec;
  TVector<std::string> _variables_list;
  bool _is_valid;

 public:
  Expression(const std::string& str);
  ~Expression();

  bool isValid() const { return _is_valid; }
  std::string getPolishString() const;
  TVector<std::string> getVariables() const { return _variables_list; }

  double calculate() const;
  double calculate(const std::map<std::string, double>& variables) const;

 private:
  void buildPolishRecord();
  void clearLexems(TList<Lexem*>& list);
  bool isLeftAssociative(const Lexem* lexem) const;
  void extractVariables();

  double calculatePolish(const std::map<std::string, double>& vars) const;
};

#endif  // LIB_EXPRESSION_EXPRESSION_H_
