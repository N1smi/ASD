// Copyright 2026 Smirnov Nikita

#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include <algorithm>
#include <string>

#include "../lib_monom/monom.h"
#include "../lib_tlist/tlist.h"

template <size_t N = 3>
class Polynom {
  TList<Monom<N>> _monoms;

 public:
  Polynom();
  explicit Polynom(const std::string& str);
  Polynom(const Polynom& other);
  ~Polynom() = default;

  bool operator==(const Polynom& other) const;
  bool operator!=(const Polynom& other) const;

  Polynom operator+(const Polynom& other) const;
  Polynom operator-(const Polynom& other) const;
  Polynom operator*(const Polynom& other) const;

  Polynom operator+(const Monom<N>& other) const;
  Polynom operator-(const Monom<N>& other) const;
  Polynom operator*(const Monom<N>& other) const;

  Polynom operator*(double scalar) const;

  Polynom& operator+=(const Polynom& other);
  Polynom& operator-=(const Polynom& other);
  Polynom& operator*=(const Polynom& other);

  Polynom& operator+=(const Monom<N>& other);
  Polynom& operator-=(const Monom<N>& other);
  Polynom& operator*=(const Monom<N>& other);

  Polynom& operator*=(double scalar);

  Polynom operator-() const;

  Polynom& operator=(const Polynom& other);

  double calculate(const double values[N]) const;

  friend std::ostream& operator<<(std::ostream& os, const Polynom& polynom) {
    if (polynom._monoms.is_empty()) {
      os << "0";
      return os;
    }

    auto it = polynom._monoms.begin();

    os << *it;
    ++it;

    for (; it != polynom._monoms.end(); ++it) {
      if ((*it).getCoefficient() > 0) {
        os << "+" << *it;
      } else {
        os << *it;
      }
    }

    return os;
  }

  friend std::istream& operator>>(std::istream& is, Polynom& polynom) {
    std::string str;
    std::getline(is, str);

    try {
      polynom = Polynom<N>(str);
    }
    catch (const std::exception& e) {
      is.setstate(std::ios::failbit);
    }

    return is;
  }
};

template <size_t N>
Polynom<N>::Polynom() : _monoms() {}

template <size_t N>
Polynom<N>& Polynom<N>::operator+=(const Monom<N>& other) {
  if (other.getCoefficient() == 0) return *this;

  if (_monoms.is_empty()) {
    _monoms.push_back(other);
    return *this;
  }

  size_t pos = 0;
  auto it = _monoms.begin();

  while (it != _monoms.end()) {
    if (*it == other) {
      *it += other;
      if ((*it).getCoefficient() == 0) {
        _monoms.erase(pos);
      }
      return *this;
    }

    if (other > *it) {
      _monoms.insert(pos, other);
      return *this;
    }

    ++it;
    ++pos;
  }

  _monoms.push_back(other);

  return *this;
}

template <size_t N>
Polynom<N>::Polynom(const Polynom<N>& other) : _monoms(other._monoms) {}

template <size_t N>
Polynom<N>::Polynom(const std::string& str) {
  if (str.empty()) return;

  std::string s = str;
  s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());

  size_t pos = 0;

  if (s[0] != '+' && s[0] != '-') {
    s = '+' + s;
  }

  while (pos < s.length()) {
    size_t signPos = pos;
    pos++;

    int bracketLevel = 0;
    while (pos < s.length()) {
      if (s[pos] == '(') bracketLevel++;
      if (s[pos] == ')') bracketLevel--;

      if (bracketLevel == 0 && (s[pos] == '+' || s[pos] == '-')) {
        break;
      }
      pos++;
    }

    if (bracketLevel != 0) {
      throw std::invalid_argument("Unbalanced parentheses in monom!");
    }

    std::string monomStr = s.substr(signPos, pos - signPos);

    try {
      Monom<N> monom = Monom<N>::parseFromString(monomStr);
      *this += monom;
    } catch (const std::exception& e) {
      throw std::invalid_argument("Invalid monom: " + monomStr);
    }
  }
}

template <size_t N>
bool Polynom<N>::operator==(const Polynom<N>& other) const {
  auto it1 = _monoms.begin();
  auto it2 = other._monoms.begin();

  while (it1 != _monoms.end() && it2 != other._monoms.end()) {
    if (*it1 != *it2 || (*it1).getCoefficient() != (*it2).getCoefficient()) {
      return false;
    }

    ++it1;
    ++it2;
  }

  return (it1 == _monoms.end() && it2 == other._monoms.end());
}

template <size_t N>
bool Polynom<N>::operator!=(const Polynom<N>& other) const {
  return !(*this == other);
}

template <size_t N>
Polynom<N> Polynom<N>::operator+(const Polynom<N>& other) const {
  Polynom<N> result = *this;
  result += other;
  return result;
}

template <size_t N>
Polynom<N> Polynom<N>::operator-(const Polynom<N>& other) const {
  Polynom<N> result = *this;
  result -= other;
  return result;
}

template <size_t N>
Polynom<N> Polynom<N>::operator*(const Polynom<N>& other) const {
  Polynom<N> result = *this;
  result *= other;
  return result;
}

template <size_t N>
Polynom<N> Polynom<N>::operator+(const Monom<N>& other) const {
  Polynom<N> result = *this;
  result += other;
  return result;
}

template <size_t N>
Polynom<N> Polynom<N>::operator-(const Monom<N>& other) const {
  Polynom<N> result = *this;
  result -= other;
  return result;
}

template <size_t N>
Polynom<N> Polynom<N>::operator*(const Monom<N>& other) const {
  Polynom<N> result = *this;
  result *= other;
  return result;
}

template <size_t N>
Polynom<N> Polynom<N>::operator*(double scalar) const {
  Polynom<N> result = *this;
  result *= scalar;
  return result;
}

template <size_t N>
Polynom<N>& Polynom<N>::operator+=(const Polynom<N>& other) {
  for (const auto& monom : other._monoms) {
    *this += monom;
  }

  return *this;
}

template <size_t N>
Polynom<N>& Polynom<N>::operator-=(const Polynom<N>& other) {
  for (const auto& monom : other._monoms) {
    *this -= monom;
  }

  return *this;
}

template <size_t N>
Polynom<N>& Polynom<N>::operator*=(const Polynom<N>& other) {
  Polynom<N> result;

  for (const auto& monom : other._monoms) {
    result += (*this * monom);
  }

  *this = result;
  return *this;
}

template <size_t N>
Polynom<N>& Polynom<N>::operator-=(const Monom<N>& other) {
  return *this += (-other);
}

template <size_t N>
Polynom<N>& Polynom<N>::operator*=(const Monom<N>& other) {
  if (other.getCoefficient() == 0) {
    _monoms.clear();
    return *this;
  }

  for (auto& monom : _monoms) {
    monom *= other;
  }

  return *this;
}

template <size_t N>
Polynom<N>& Polynom<N>::operator=(const Polynom<N>& other) {
  if (this != &other) {
    _monoms = other._monoms;
  }
  return *this;
}

template <size_t N>
Polynom<N>& Polynom<N>::operator*=(double scalar) {
  if (scalar == 0.0) {
    _monoms.clear();
    return *this;
  }

  for (auto& monom : _monoms) {
    monom *= scalar;
  }

  return *this;
}

template <size_t N>
Polynom<N> Polynom<N>::operator-() const {
  Polynom<N> result = *this;

  for (auto& monom : result._monoms) {
    monom = -monom;
  }

  return result;
}

template <size_t N>
double Polynom<N>::calculate(const double values[N]) const {
  double result = 0.0;
  for (const auto& monom : _monoms) {
    result += monom.calculate(values);
  }

  return result;
}

#endif  // LIB_POLYNOM_POLYNOM_H_
