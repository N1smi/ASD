// Copyright 2026 Smirnov Nikita

#ifndef LIB_TABLE_TABLE_H_
#define LIB_TABLE_TABLE_H_

#include <utility>
#include<iostream>
#include "../lib_itable/itable.h"

template <class TKey, class TValue, class Container>
class Table : public ITable<TKey, TValue> {
 protected:
  Container _rows;
 public:
  Table() : _rows() {}
  ~Table() override = default;

  auto begin() { return _rows.begin(); }
  auto end() { return _rows.end(); }
  auto begin() const { return _rows.begin(); }
  auto end() const { return _rows.end(); }

  std::ostream& print(std::ostream& os) const override;
};

template <class TKey, class TValue, class Container>
std::ostream& Table<TKey, TValue, Container>::print(std::ostream& os) const {
  if (is_empty()) {
    os << "[Empty table]\n";
    return os;
  }

  os << "========== Table ==========\n";

  for (auto it = _rows.begin(); it != _rows.end(); ++it) {
    print_item(os, *it);
  }

  os << "===========================\n";
  return os;
}

template <class TKey, class TValue, class Container>
std::ostream& operator<<(std::ostream& os, const Table<TKey,
  TValue, Container>& table) {
  return table.print(os);
}

template <typename T1, typename T2>
void print_item(std::ostream& os, const std::pair<T1, T2>& item) {
  os << item.first << " " << item.second << "\n";
}

template <typename T>
void print_item(std::ostream& os, const T& item) {
  os << "[Bucket with complex data]\n";
}

#endif  // LIB_TABLE_TABLE_H_
