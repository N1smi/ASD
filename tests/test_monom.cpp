// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_monom/monom.h"

TEST(TestMonomLib, CreateDefaultMonom) {
  Monom monom;

  EXPECT_DOUBLE_EQ(monom.getCoefficient(), 0.0);
  for (size_t i = 0; i < monom.getVarsCount(); i++) {
    EXPECT_EQ(monom.getPower(i), 0);
  }
}

TEST(TestMonomLib, CreateScalarMonom) {
  Monom monom(5.0);

  EXPECT_DOUBLE_EQ(monom.getCoefficient(), 5.0);
  for (size_t i = 0; i < monom.getVarsCount(); i++) {
    EXPECT_EQ(monom.getPower(i), 0);
  }
}

TEST(TestMonomLib, CreateMonomWithPowers) {
  int powers[3] = { 1, 2, 3 };
  Monom monom(10.0, powers);

  EXPECT_DOUBLE_EQ(monom.getCoefficient(), 10.0);
  for (size_t i = 0; i < monom.getVarsCount(); i++) {
    EXPECT_EQ(monom.getPower(i), i + 1);
  }
}

TEST(TestMonomLib, CopyMonom) {
  int powers[3] = { 1, 2, 3 };
  Monom monom(10.0, powers);

  Monom monom_copy(monom);

  EXPECT_DOUBLE_EQ(monom_copy.getCoefficient(), 10.0);
  for (size_t i = 0; i < monom_copy.getVarsCount(); i++) {
    EXPECT_EQ(monom_copy.getPower(i), i + 1);
  }
}
