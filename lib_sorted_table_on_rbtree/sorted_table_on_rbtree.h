// Copyright 2026 Smirnov Nikita

#ifndef LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H_
#define LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H_

#include "../lib_table/table.h"
#include "../lib_rbtree/rbtree.h"

template <class TKey, class TValue>
class SortedTableOnRBTree :
  public Table<TKey, TValue, RBTree<TKey, TValue>> {
 protected:
  using Base = Table<TKey, TValue, RBTree<TKey, TValue>>;
 public:
  SortedTableOnRBTree() = default;
  ~SortedTableOnRBTree() override = default;

  bool insert(const TKey& key, const TValue& value) override;
  bool erase(const TKey& key) override;
  TValue* find(const TKey& key) override;
  const TValue* find(const TKey& key) const override;
  bool is_empty() const noexcept override { return Base::_rows.is_empty(); }
};

template <class TKey, class TValue>
bool SortedTableOnRBTree<TKey, TValue>::insert(const TKey& key,
  const TValue& value) {
  if (find(key) != nullptr) {
    return false;
  }

  Base::_rows.insert(key, value);

  return true;
}

template <class TKey, class TValue>
bool SortedTableOnRBTree<TKey, TValue>::erase(const TKey& key) {
  if (find(key) == nullptr) {
    return false;
  }

  Base::_rows.erase(key);

  return true;
}

template <class TKey, class TValue>
TValue* SortedTableOnRBTree<TKey, TValue>::find(const TKey& key) {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TKey, class TValue>
const TValue* SortedTableOnRBTree<TKey, TValue>::find(const TKey& key) const {
  return Base::_rows.find(key);
}

#endif  // LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H_
