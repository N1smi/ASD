// Copyright 2026 Smirnov Nikita

#ifndef LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H_
#define LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H_

#include "../lib_table/table.h"
#include "../lib_tree/tree.h"

template <class TKey, class TValue>
class UnsortedTableOnTree
  : public Table<TKey, TValue, Tree<TKey, TValue>> {
 protected:
  using Base = Table<TKey, TValue, Tree<TKey, TValue>>;

 public:
  UnsortedTableOnTree() = default;
  ~UnsortedTableOnTree() override = default;

  bool insert(const TKey& key, const TValue& value) override;
  bool erase(const TKey& key) override;
  TValue* find(const TKey& key) override;
  const TValue* find(const TKey&) const override;
  bool is_empty() const noexcept override { return Base::_rows.is_empty(); }
};

template <class TKey, class TValue>
bool UnsortedTableOnTree<TKey, TValue>::insert(const TKey& key,
  const TValue& value) {
  if (find(key) != nullptr) {
    return false;
  }

  Base::_rows.insert(key, value);

  return true;
}

template <class TKey, class TValue>
bool UnsortedTableOnTree<TKey, TValue>::erase(const TKey& key) {
  if (find(key) == nullptr) {
    return false;
  }

  Base::_rows.erase(key);

  return true;
}

template <class TKey, class TValue>
TValue* UnsortedTableOnTree<TKey, TValue>::find(const TKey& key) {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TKey, class TValue>
const TValue* UnsortedTableOnTree<TKey, TValue>::find(const TKey& key) const {
  return Base::_rows.find(key);
}

#endif  // LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H_
