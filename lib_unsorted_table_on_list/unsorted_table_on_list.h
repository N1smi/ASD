// Copyright 2026 Smirnov Nikita

#ifndef LIB_UNSORTED_TABLE_ON_LIST_UNSORTED_TABLE_ON_LIST_H_
#define LIB_UNSORTED_TABLE_ON_LIST_UNSORTED_TABLE_ON_LIST_H_

#include <utility>

#include "../lib_table/table.h"
#include "../lib_tlist/tlist.h"

template <class TKey, class TValue>
class UnsortedTableOnList
    : public Table<TKey, TValue, TList<std::pair<TKey, TValue>>> {
 protected:
  using Base = Table<TKey, TValue, TList<std::pair<TKey, TValue>>>;

 public:
  UnsortedTableOnList() = default;
  ~UnsortedTableOnList() override = default;

  bool insert(const TKey& key, const TValue& value) override;
  bool erase(const TKey& key) override;
  TValue* find(const TKey& key) override;
  const TValue* find(const TKey&) const override;
  bool is_empty() const noexcept override;
};

template <class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::insert(const TKey& key,
                                               const TValue& value) {
  if (find(key) != nullptr) {
    return false;
  }

  Base::_rows.push_back({key, value});
  return true;
}

template <class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
  size_t pos = 0;
  for (auto& [k, v] : Base::_rows) {
    if (k == key) {
      Base::_rows.erase(pos);
      return true;
    }
    ++pos;
  }

  return false;
}

template <class TKey, class TValue>
TValue* UnsortedTableOnList<TKey, TValue>::find(const TKey& key) {
  for (auto& [k, v] : Base::_rows) {
    if (k == key) {
      return &v;
    }
  }

  return nullptr;
}

template <class TKey, class TValue>
const TValue* UnsortedTableOnList<TKey, TValue>::find(const TKey& key) const {
  for (const auto& [k, v] : Base::_rows) {
    if (k == key) {
      return &v;
    }
  }

  return nullptr;
}

template <class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept {
  return Base::_rows.is_empty();
}

#endif  // LIB_UNSORTED_TABLE_ON_LIST_UNSORTED_TABLE_ON_LIST_H_
