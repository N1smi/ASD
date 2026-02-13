// Copyright 2026 Smirnov Nikita

#include "../lib_monom/monom.h"

Monom::Monom(double coef) : _coefficient(coef) {
  for (size_t i = 0; i < VARS_COUNT; i++) {
    _powers[i] = 0;
  }
}

Monom::Monom(double coef, const int powers[VARS_COUNT]) : _coefficient(coef) {
  for (size_t i = 0; i < VARS_COUNT; i++) {
    _powers[i] = powers[i];
  }
}

Monom::Monom(const Monom& other) : _coefficient(other._coefficient) {
  for (size_t i = 0; i < VARS_COUNT; i++) {
    _powers[i] = other._powers[i];
  }
}
