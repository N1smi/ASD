// Copyright 2026 Smirnov Nikita

#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include<iostream>

template <class TKey, class TValue>
class ITable {
 public:
  virtual ~ITable() = default;

  virtual void insert(const TKey&, const TValue&) = 0;
  virtual void erase(const TKey&) = 0;
  virtual TValue* find(const TKey&) = 0;
  virtual const TValue* find(const TKey&) const = 0;
  virtual bool is_empty() const noexcept = 0;

  virtual std::ostream& print(std::ostream& os) const = 0;
};

#endif  // LIB_ITABLE_ITABLE_H_
