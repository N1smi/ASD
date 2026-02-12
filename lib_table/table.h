// Copyright 2026 Smirnov Nikita

#ifndef LIB_TABLE_TABLE_H_
#define LIB_TABLE_TABLE_H_

#include<iostream>
#include "../lib_itable/itable.h"

template <class TKey, class TValue, class Container>
class Table : public ITable<TKey, TValue> {
protected:
  Container _data;
public:
  virtual std::ostream& print(std::ostream& os) const override;
  friend std::ostream& operator<<(std::ostream& os, const Table& table);
};

template <class TKey, class TValue, class Container>
std::ostream& Table<TKey, TValue, Container>::print(std::ostream& os) const {
  if (is_empty()) {
    os << "[Empty table]";
    return os;
  }

  os << "=== Table (" << size() << " items) ===\n";

  size_t index = 0;
  for (const auto& [key, value] : _data) {
    os << key << " " << value << "\n";
  }

  os << "=======================\n";
  return os;
}

template <class TKey, class TValue, class Container>
std::ostream& operator<<(std::ostream& os, const Table<TKey, TValue, Container>& table) {
  return table.print(os);
}

#endif  // LIB_TABLE_TABLE_H_