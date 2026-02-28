// Copyright 2026 Smirnov Nikita

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "../lib_polynom/polynom.h"

TEST(TestPolynomLib, CreateDefaultPolynom) {
  Polynom<3> p;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, PlusEqualMonomToEmpty) {
  Polynom<3> p;

  int powers[3] = {1, 2, 3};
  Monom<3> m(2.5, powers);

  p += m;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomZeroIgnored) {
  Polynom<3> p;

  int powers1[3] = {1, 2, 3};
  int powers2[3] = {1, 4, 3};

  Monom<3> m1(2.5, powers1);
  Monom<3> m2(0.0, powers2);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomGreater) {
  Polynom<3> p;

  int p1[3] = {1, 2, 3};
  int p2[3] = {2, 1, 0};

  Monom<3> m1(2.5, p1);
  Monom<3> m2(3.5, p2);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;

  EXPECT_EQ(ss.str(), "3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomLess) {
  Polynom<3> p;
  int p1[3] = {2, 1, 0};
  int p2[3] = {1, 2, 3};

  Monom<3> m1(3.5, p1);
  Monom<3> m2(2.5, p2);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;

  EXPECT_EQ(ss.str(), "3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, PlusEqualMonomMiddle) {
  Polynom<3> p;
  int p1[3] = {2, 1, 0};
  int p2[3] = {1, 2, 3};
  int p3[3] = {0, 0, 0};

  Monom<3> m1(3.0, p1);
  Monom<3> m2(1.0, p2);
  Monom<3> m3(2.0, p3);

  p += m1;
  p += m2;
  p += m3;

  std::stringstream ss;
  ss << p;

  EXPECT_EQ(ss.str(), "3x1^2x2+x1x2^2x3^3+2");
}

TEST(TestPolynomLib, AddSimilar) {
  Polynom<3> p;
  int powers[3] = {1, 2, 3};

  Monom<3> m1(2.5, powers);
  Monom<3> m2(3.5, powers);
  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "6x1x2^2x3^3");
}

TEST(TestPolynomLib, AddOpposite) {
  Polynom<3> p;
  int powers[3] = {1, 2, 3};

  Monom<3> m1(5.0, powers);
  Monom<3> m2(-5.0, powers);

  p += m1;
  p += m2;

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, CreatePolynomWithCopy) {
  Polynom<3> p1;
  int p1_powers[3] = {2, 1, 0};
  int p2_powers[3] = {1, 2, 3};
  int p3_powers[3] = {0, 0, 0};

  Monom<3> m1(3.0, p1_powers);
  Monom<3> m2(2.0, p2_powers);
  Monom<3> m3(1.0, p3_powers);

  p1 += m1;
  p1 += m2;
  p1 += m3;

  Polynom<3> p2(p1);

  std::stringstream ss1, ss2;
  ss1 << p1;
  ss2 << p2;
  EXPECT_EQ(ss1.str(), ss2.str());
  EXPECT_EQ(ss1.str(), "3x1^2x2+2x1x2^2x3^3+1");
}

TEST(TestPolynomLib, ConstructorEmptyString) {
  Polynom<3> p("");

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynomLib, ConstructorNormalString) {
  Polynom<3> p("2.5x1x2^2x3^3-3.5x1^2x2");
  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2+2.5x1x2^2x3^3");
}

TEST(TestPolynomLib, ConstructorWithNegativePowers) {
  Polynom<3> p("2.5x1^(-2)x2^3-3.5x1^2x2^(-1)");
  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "-3.5x1^2x2^(-1)+2.5x1^(-2)x2^3");
}

// TEST(TestPolynomLib, PlusEqual) {
//   Polynom<3> p1, p2;
//
//   int p1_powers1[3] = {1, 2, 3};
//   int p1_powers2[3] = {2, 2, 3};
//   p1.addMonom(Monom<3>(2.5, p1_powers1));
//   p1.addMonom(Monom<3>(2.0, p1_powers2));
//
//   int p2_powers1[3] = {2, 1, 0};
//   int p2_powers2[3] = {2, 2, 3};
//   p2.addMonom(Monom<3>(3.5, p2_powers1));
//   p2.addMonom(Monom<3>(3.0, p2_powers2));
//
//   p1 += p2;
//
//   std::stringstream ss;
//   ss << p1;
//   EXPECT_EQ(ss.str(), "5x1^2x2^2x3^3+3.5x1^2x2+2.5x1x2^2x3^3");
// }
