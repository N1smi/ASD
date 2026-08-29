// Copyright 2026 Smirnov Nikita

#ifndef LIB_UNSORTED_TABLE_ON_ARRAY_UNSORTED_TABLE_ON_ARRAY_H_
#define LIB_UNSORTED_TABLE_ON_ARRAY_UNSORTED_TABLE_ON_ARRAY_H_

#include <utility>

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class UnsortedTableOnArr
    : public Table<TKey, TValue, TVector<std::pair<TKey, TValue>>> {
 protected:
  using Base = Table<TKey, TValue, TVector<std::pair<TKey, TValue>>>;

 public:
  UnsortedTableOnArr() = default;
  ~UnsortedTableOnArr() override = default;

  bool insert(const TKey& key, const TValue& value) override;
  bool erase(const TKey& key) override;
  TValue* find(const TKey& key) override;
  const TValue* find(const TKey&) const override;
  bool is_empty() const noexcept override;
};

template <class TKey, class TValue>
bool UnsortedTableOnArr<TKey, TValue>::insert(const TKey& key,
                                              const TValue& value) {
  if (find(key) != nullptr) {
    return false;
  }

  Base::_rows.push_back({key, value});
  return true;
}

template <class TKey, class TValue>
bool UnsortedTableOnArr<TKey, TValue>::erase(const TKey& key) {
  for (size_t i = 0; i < Base::_rows.size(); ++i) {
    if (Base::_rows[i].first == key) {
      Base::_rows.erase(i);
      return true;
    }
  }

  return false;
}

template <class TKey, class TValue>
TValue* UnsortedTableOnArr<TKey, TValue>::find(const TKey& key) {
  for (size_t i = 0; i < Base::_rows.size(); ++i) {
    if (Base::_rows[i].first == key) {
      return &Base::_rows[i].second;
    }
  }

  return nullptr;
}

template <class TKey, class TValue>
const TValue* UnsortedTableOnArr<TKey, TValue>::find(const TKey& key) const {
  for (size_t i = 0; i < Base::_rows.size(); ++i) {
    if (Base::_rows[i].first == key) {
      return &Base::_rows[i].second;
    }
  }

  return nullptr;
}

template <class TKey, class TValue>
bool UnsortedTableOnArr<TKey, TValue>::is_empty() const noexcept {
  return Base::_rows.is_empty();
}

#endif  // LIB_UNSORTED_TABLE_ON_ARRAY_UNSORTED_TABLE_ON_ARRAY_H_
