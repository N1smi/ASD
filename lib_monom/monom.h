// Copyright 2026 Smirnov Nikita

#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include<iostream>

class Monom {
  static const size_t VARS_COUNT = 3;
  double _coefficient;
  int _powers[VARS_COUNT];

 public:
  explicit Monom(double coef = 0.0);
  Monom(double coef, const int powers[VARS_COUNT]);
  Monom(const Monom& other);
  ~Monom() = default;

  double getCoefficient() const { return _coefficient; }
  int getPower(int index) const {
    if (index >= 0 && index < static_cast<int>(VARS_COUNT)) {
      return _powers[index];
    }
    throw std::out_of_range("Index out of range!");
  }
  size_t getVarsCount() const { return VARS_COUNT; }

  bool operator==(const Monom& monom) const;
  bool operator!=(const Monom& monom) const;

  Monom operator+(const Monom& monom) const;
  Monom operator-(const Monom& monom) const;
  Monom operator*(const Monom& monom) const;
  Monom operator/(const Monom& monom) const;

  Monom operator*(double scalar) const;
  Monom operator/(double scalar) const;

  Monom operator-() const;

  Monom& operator+=(const Monom& monom);
  Monom& operator-=(const Monom& monom);
  Monom& operator*=(const Monom& monom);
  Monom& operator/=(const Monom& monom);

  Monom& operator=(const Monom& monom);

  Monom& operator*=(double scalar);
  Monom& operator/(double scalar);

  double calculate(const double values[VARS_COUNT]) const;

  friend std::ostream& operator<<(std::ostream& os, const Monom& monom);
  friend std::istream& operator>>(std::istream& is, Monom& monom);
};


#endif  // LIB_MONOM_MONOM_H_