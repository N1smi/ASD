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
};

template <class TKey, class TValue>
bool SortedTableOnArr<TKey, TValue>::insert(const TKey& key,
                                            const TValue& value) {
  size_t idx = find_index(key);

  if (idx < Base::_rows.size() && Base::_rows[idx].first == key) {
    return false;
  }

  Base::_rows.insert(idx, {key, value});
  return true;
}

template <class TKey, class TValue>
bool SortedTableOnArr<TKey, TValue>::erase(const TKey& key) {
  size_t idx = find_index(key);

  if (idx >= Base::_rows.size() || Base::_rows[idx].first != key) {
    return false;
  }

  Base::_rows.erase(idx);
  return true;
}

template <class TKey, class TValue>
TValue* SortedTableOnArr<TKey, TValue>::find(const TKey& key) {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TKey, class TValue>
const TValue* SortedTableOnArr<TKey, TValue>::find(const TKey& key) const {
  size_t idx = find_index(key);

  if (idx >= Base::_rows.size() || Base::_rows[idx].first != key) {
    return nullptr;
  }

  return &Base::_rows[idx].second;
}

template <class TKey, class TValue>
size_t SortedTableOnArr<TKey, TValue>::find_index(const TKey& key) const {
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
