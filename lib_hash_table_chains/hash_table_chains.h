// Copyright 2026 Smirnov Nikita

#ifndef LIB_HASH_TABLE_CHAINS_HASH_TABLE_CHAINS_H_
#define LIB_HASH_TABLE_CHAINS_HASH_TABLE_CHAINS_H_

#include <utility>

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"
#include "../lib_tlist/tlist.h"

#define SIZE 100

template <class TValue>
class HashTableChains
  : public Table<std::string,
  TValue, TVector<TList<std::pair<std::string, TValue>>>> {
  size_t _size;
  size_t _count;

protected:
  using Base = Table<std::string,
    TValue, TVector<TList<std::pair<std::string, TValue>>>>;

public:
  explicit HashTableChains(size_t size = SIZE);
  ~HashTableChains() override = default;

  bool insert(const std::string& key, const TValue& value) override;
  bool erase(const std::string& key) override;
  TValue* find(const std::string& key) override;
  const TValue* find(const std::string& key) const override;
  bool is_empty() const noexcept override { return _count == 0; }

  std::ostream& print(std::ostream& os) const override;
private:
  size_t h(const std::string& key) const noexcept;
};

template <class TValue>
HashTableChains<TValue>::HashTableChains(size_t size)
  : _size(size), Base(), _count(0) {
  Base::_rows = TVector<TList<std::pair<std::string, TValue>>>(size);
}

template <class TValue>
bool HashTableChains<TValue>::insert(const std::string& key, const TValue& value) {
  if (find(key)) {
    return false;
  }

  size_t hash = h(key);

  Base::_rows[hash].push_back({ key, value });
  _count++;

  return true;
}

template <class TValue>
bool HashTableChains<TValue>::erase(const std::string& key) {
  if (is_empty()) {
    return false;
  }

  size_t hash = h(key);

  size_t index = 0;

  for (auto it = Base::_rows[hash].begin(); it != Base::_rows[hash].end(); ++it) {
    if ((*it).first == key) {
      Base::_rows[hash].erase(index);
      _count--;
      return true;
    }
    index++;
  }

  return false;
}

template <class TValue>
TValue* HashTableChains<TValue>::find(const std::string& key) {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TValue>
const TValue* HashTableChains<TValue>::find(const std::string& key) const {
  if (is_empty()) {
    return nullptr;
  }

  size_t hash = h(key);

  for (auto it = Base::_rows[hash].begin(); it != Base::_rows[hash].end(); ++it) {
    if ((*it).first == key) {
      return &((*it).second);
    }
  }

  return nullptr;
}

template <class TValue>
std::ostream& HashTableChains<TValue>::print(std::ostream& os) const {
  if (is_empty()) {
    os << "[Empty table]\n";
    return os;
  }

  os << "========== Table ==========\n";

  for (const auto& bucket : Base::_rows) {
    for (const auto& item : bucket) {
      const auto& [key, value] = item;
      os << key << " " << value << "\n";
    }
  }

  os << "===========================\n";
  return os;
}

template <class TValue>
size_t HashTableChains<TValue>::h(const std::string& key) const noexcept {
  size_t hash = 0;
  for (size_t i = 0; i < key.length(); i++) {
    hash += key[i];
  }

  hash %= _size;
  return hash;
}

#endif  // LIB_HASH_TABLE_CHAINS_HASH_TABLE_CHAINS_H_