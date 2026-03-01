// Copyright 2026 Smirnov Nikita

#ifndef LIB_SORTED_TABLE_ON_ARRAY_SORTED_TABLE_ON_ARRAY_H_
#define LIB_SORTED_TABLE_ON_ARRAY_SORTED_TABLE_ON_ARRAY_H_

#include "../lib_unsorted_table_on_array/unsorted_table_on_array.h"

template <class TKey, class TValue>
class SortedTableOnArr : public UnsortedTableOnArr<TKey, TValue> {
 public:
  SortedTableOnArr() = default;
  ~SortedTableOnArr() override = default;

  bool insert(const TKey& key, const TValue& value) override;
  bool erase(const TKey& key) override;
  TValue* find(const TKey& key) override;
  const TValue* find(const TKey&) const override;

 private:
  size_t find_index(const TKey& key) const;
  size_t find_insert_pos(const TKey& key) const;
};

template <class TKey, class TValue>
bool SortedTableOnArr<TKey, TValue>::insert(const TKey& key,
                                            const TValue& value) {
  if (find_index(key) != static_cast<size_t>(-1)) {
    return false;
  }

  size_t pos = find_insert_pos(key);

  Base::_rows.insert(pos, {key, value});
  return true;
}

template <class TKey, class TValue>
bool SortedTableOnArr<TKey, TValue>::erase(const TKey& key) {
  size_t idx = find_index(key);
  if (idx == static_cast<size_t>(-1)) {
    return false;
  }
  Base::_rows.erase(idx);
  return true;
}

template <class TKey, class TValue>
TValue* SortedTableOnArr<TKey, TValue>::find(const TKey& key) {
  size_t idx = find_index(key);
  if (idx == static_cast<size_t>(-1)) {
    return nullptr;
  }
  return &Base::_rows[idx].second;
}

template <class TKey, class TValue>
const TValue* SortedTableOnArr<TKey, TValue>::find(const TKey& key) const {
  size_t idx = find_index(key);
  if (idx == static_cast<size_t>(-1)) {
    return nullptr;
  }
  return &Base::_rows[idx].second;
}

template <class TKey, class TValue>
size_t SortedTableOnArr<TKey, TValue>::find_index(const TKey& key) const {
  if (Base::_rows.is_empty()) {
    return static_cast<size_t>(-1);
  }

  size_t l = 0;
  size_t r = Base::_rows.size() - 1;

  while (l <= r) {
    size_t mid = l + (r - l) / 2;

    if (Base::_rows[mid].first == key) {
      return mid;
    }
    if (Base::_rows[mid].first > key) {
      if (mid == 0) break;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  return static_cast<size_t>(-1);
}

template <class TKey, class TValue>
size_t SortedTableOnArr<TKey, TValue>::find_insert_pos(const TKey& key) const {
  size_t l = 0;
  size_t r = Base::_rows.size();

  while (l < r) {
    size_t mid = l + (r - l) / 2;
    if (Base::_rows[mid].first < key) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return l;
}

#endif  // LIB_SORTED_TABLE_ON_ARRAY_SORTED_TABLE_ON_ARRAY_H_
