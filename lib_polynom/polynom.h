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

  bool operator==(const Polynom& monom) const;
  bool operator!=(const Polynom& monom) const;

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

  friend std::istream& operator>>(std::istream& is, Polynom& polynom);
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

    std::string monomStr = s.substr(signPos, pos - signPos);

    try {
      Monom<N> monom = Monom<N>::parseFromString(monomStr);
      *this += monom;
    } catch (const std::exception& e) {
      throw std::invalid_argument("Invalid monom: " + monomStr);
    }
  }
}

// template <size_t N>
// Polynom<N>& Polynom<N>::operator+=(const Polynom<N>& other) {
//   for (const auto& monom : other._monoms) {
//     addMonom(monom);
//   }
//
//   return *this;
// }

#endif  // LIB_POLYNOM_POLYNOM_H_
