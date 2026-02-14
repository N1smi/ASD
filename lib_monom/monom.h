// Copyright 2026 Smirnov Nikita

#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include<iostream>
#include <cmath>

template<size_t N = 3>
class Monom {
  double _coefficient;
  int _powers[N];

 public:
  explicit Monom(double coef = 0.0);
  Monom(double coef, const int powers[N]);
  Monom(const Monom& other);
  ~Monom() = default;

  double getCoefficient() const { return _coefficient; }
  int getPower(int index) const {
    if (index >= 0 && index < static_cast<int>(N)) {
      return _powers[index];
    }
    throw std::out_of_range("Index out of range!");
  }
  size_t getVarsCount() const { return N; }
  bool isConstant() const;

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
  Monom& operator/=(double scalar);

  double calculate(const double values[N]) const;

  friend std::ostream& operator<<(std::ostream& os, const Monom& monom) {
    if (monom._coefficient == 0) {
      os << "0";
      return os;
    }

    if (monom.isConstant()) {
      os << monom._coefficient;
      return os;
    }

    if (monom._coefficient != 1.0 && monom._coefficient != -1.0) {
      os << monom._coefficient;
    }
    else if (monom._coefficient == -1.0) {
      os << "-";
    }

    for (size_t i = 0; i < monom.getVarsCount(); i++) {
      int power = monom.getPower(i);
      if (power > 0) {
        os << "x" << i + 1;
        if (power > 1) {
          os << "^" << power;
        }
      }
      else if (power < 0) {
        os << "x" << i + 1 << "^(" << power << ")";
      }
    }

    return os;
  }

  friend std::istream& operator>>(std::istream& is, Monom& monom) {
    is >> monom._coefficient;
    for (size_t i = 0; i < N; i++) {
      is >> monom._powers[i];
    }
    return is;
  }
};

template<size_t N>
Monom<N>::Monom(double coef) : _coefficient(coef) {
  for (size_t i = 0; i < N; i++) {
    _powers[i] = 0;
  }
}

template<size_t N>
Monom<N>::Monom(double coef, const int powers[N]) : _coefficient(coef) {
  for (size_t i = 0; i < N; i++) {
    _powers[i] = powers[i];
  }
}

template<size_t N>
Monom<N>::Monom(const Monom<N>& other) : _coefficient(other._coefficient) {
  for (size_t i = 0; i < N; i++) {
    _powers[i] = other._powers[i];
  }
}

template<size_t N>
bool Monom<N>::isConstant() const {
  for (size_t i = 0; i < N; i++) {
    if (_powers[i] != 0) {
      return false;
    }
  }
  return true;
}

template<size_t N>
bool Monom<N>::operator==(const Monom& monom) const {
  for (size_t i = 0; i < N; i++) {
    if (_powers[i] != monom._powers[i]) {
      return false;
    }
  }

  return true;
}

template<size_t N>
bool Monom<N>::operator!=(const Monom& monom) const {
  return !(*this == monom);
}

template<size_t N>
Monom<N> Monom<N>::operator+(const Monom<N>& monom) const {
  Monom result = *this;
  result += monom;
  return result;
}

template<size_t N>
Monom<N> Monom<N>::operator-(const Monom<N>& monom) const {
  Monom result = *this;
  result -= monom;
  return result;
}

template<size_t N>
Monom<N> Monom<N>::operator*(const Monom<N>& monom) const {
  Monom result = *this;
  result *= monom;
  return result;
}

template<size_t N>
Monom<N> Monom<N>::operator/(const Monom<N>& monom) const {
  Monom result = *this;
  result /= monom;
  return result;
}

template<size_t N>
Monom<N> Monom<N>::operator*(double scalar) const {
  Monom result = *this;
  result *= scalar;
  return result;
}

template<size_t N>
Monom<N> Monom<N>::operator-() const {
  Monom result = *this;
  result._coefficient = -result._coefficient;
  return result;
}

template<size_t N>
Monom<N> Monom<N>::operator/(double scalar) const {
  Monom result = *this;
  result /= scalar;
  return result;
}

template<size_t N>
Monom<N>& Monom<N>::operator+=(const Monom<N>& monom) {
  if (*this != monom) {
    throw std::invalid_argument("Cannot add non-similar monoms!");
  }

  _coefficient += monom._coefficient;
  return *this;
}

template<size_t N>
Monom<N>& Monom<N>::operator-=(const Monom<N>& monom) {
  if (*this != monom) {
    throw std::invalid_argument("Cannot sub non-similar monoms!");
  }

  _coefficient -= monom._coefficient;
  return *this;
}

template<size_t N>
Monom<N>& Monom<N>::operator*=(const Monom<N>& monom) {
  _coefficient *= monom._coefficient;

  for (size_t i = 0; i < N; i++) {
    _powers[i] += monom._powers[i];
  }

  return *this;
}

template<size_t N>
Monom<N>& Monom<N>::operator/=(const Monom<N>& monom) {
  if (monom._coefficient == 0) {
    throw std::invalid_argument("Division by zero!");
  }

  _coefficient /= monom._coefficient;

  for (size_t i = 0; i < N; i++) {
    _powers[i] -= monom._powers[i];
  }

  return *this;
}

template<size_t N>
Monom<N>& Monom<N>::operator=(const Monom<N>& monom) {
  if (this != &monom) {
    _coefficient = monom._coefficient;
    for (size_t i = 0; i < N; i++) {
      _powers[i] = monom._powers[i];
    }
  }

  return *this;
}

template<size_t N>
Monom<N>& Monom<N>::operator*=(double scalar) {
  _coefficient *= scalar;

  return *this;
}

template<size_t N>
Monom<N>& Monom<N>::operator/=(double scalar) {
  if (scalar == 0) {
    throw std::invalid_argument("Division by zero!");
  }

  _coefficient /= scalar;

  return *this;
}

template<size_t N>
double Monom<N>::calculate(const double values[N]) const {
  double result = _coefficient;
  for (size_t i = 0; i < N; i++) {
    result *= std::pow(values[i], _powers[i]);
  }

  return result;
}

#endif  // LIB_MONOM_MONOM_H_
