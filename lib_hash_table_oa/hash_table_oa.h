// Copyright 2026 Smirnov Nikita

#ifndef LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_
#define LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_

#include <tuple>
#include <string>
#include <numeric>
#include <cstdint>
#include <algorithm>

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

#define SIZE 100
#define SHIFT 7

enum status { st_empty, st_busy, st_deleted };

template <class T>
struct HashData {
  status _state = st_empty;
  std::string _key = "";
  T _data = {};

  HashData() = default;

  HashData(std::string key, T data, status state) {
    _key = key;
    _data = data;
    _state = state;
  }
};

namespace std {
template <typename T>
struct tuple_size<HashData<T>> : integral_constant<size_t, 2> {};

template <typename T>
struct tuple_element<0, HashData<T>> { using type = std::string; };

template <typename T>
struct tuple_element<1, HashData<T>> { using type = T; };
}

template <size_t I, typename T>
auto& get(HashData<T>& hd) {
  if constexpr (I == 0) return hd._key;
  else return hd._data;
}

template <size_t I, typename T>
const auto& get(const HashData<T>& hd) {
  if constexpr (I == 0) return hd._key;
  else return hd._data;
}

template <class TValue>
class HashTableOA
  : public Table<std::string, TValue, TVector<HashData<TValue>>> {
  size_t _size;
  size_t _shift;
  size_t _count;

 protected:
  using Base = Table<std::string, TValue, TVector<HashData<TValue>>>;

 public:
  explicit HashTableOA(size_t size = SIZE);
  ~HashTableOA() override = default;

  bool insert(const std::string& key, const TValue& value) override;
  bool erase(const std::string& key) override;
  TValue* find(const std::string& key) override;
  const TValue* find(const std::string& key) const override;
  bool is_empty() const noexcept override { return _count == 0; }
  bool is_full() const noexcept { return _count == _size; }

  std::ostream& print(std::ostream& os) const override;
 private:
  size_t h(const std::string& key) const noexcept;
  size_t hh(size_t index) const noexcept;
  bool is_simple(size_t num, size_t size) const noexcept;
};

template <class TValue>
HashTableOA<TValue>::HashTableOA(size_t size)  : _size(size),
_shift(SHIFT), Base(), _count(0) {
  Base::_rows = TVector<HashData<TValue>>(size);

  for (size_t i = std::max(2, static_cast<int>(size / 15)); i < size; i++) {
    if (is_simple(i, size)) {
      _shift = i;
      break;
    }
  }
}

template <class TValue>
bool HashTableOA<TValue>::insert(const std::string& key, const TValue& value) {
  if (is_full()) {
    return false;
  }

  size_t hash = h(key);
  size_t first_hash = hash;
  size_t first_deleted_idx = SIZE_MAX;

  while (true) {
    auto& current = Base::_rows[hash];

    if (current._state == st_empty) {
      size_t insert_pos = (first_deleted_idx != SIZE_MAX) ?
        first_deleted_idx : hash;
      Base::_rows[insert_pos] = HashData<TValue>(key, value, st_busy);
      _count++;
      return true;
    }

    if (current._state == st_deleted) {
      if (first_deleted_idx == SIZE_MAX) {
        first_deleted_idx = hash;
      }
    }

    if (current._state == st_busy) {
      if (current._key == key) {
        return false;
      }
    }

    hash = hh(hash);

    if (hash == first_hash) {
      if (first_deleted_idx != SIZE_MAX) {
        Base::_rows[first_deleted_idx] = HashData<TValue>(key, value, st_busy);
        _count++;
        return true;
      }
      break;
    }
  }

  return false;
}

template <class TValue>
bool HashTableOA<TValue>::erase(const std::string& key) {
  size_t hash = h(key);

  size_t first_hash = hash;

  while (true) {
    if (Base::_rows[hash]._state == st_empty) {
      break;
    }

    if (_rows[hash]._key == key && _rows[hash]._state == st_busy) {
      Base::_rows[hash]._state = st_deleted;
      _count--;
      return true;
    }

    hash = hh(hash);

    if (first_hash == hash) {
      break;
    }
  }

  return false;
}

template <class TValue>
TValue* HashTableOA<TValue>::find(const std::string& key) {
  return const_cast<TValue*>(std::as_const(*this).find(key));
}

template <class TValue>
const TValue* HashTableOA<TValue>::find(const std::string& key) const {
  size_t hash = h(key);

  size_t first_hash = hash;

  while (true) {
    if (Base::_rows[hash]._state == st_empty) {
      break;
    }

    if (_rows[hash]._key == key && _rows[hash]._state == st_busy) {
      return &Base::_rows[hash]._data;
    }

    hash = hh(hash);

    if (first_hash == hash) {
      break;
    }
  }

  return nullptr;
}

template <class TValue>
std::ostream& HashTableOA<TValue>::print(std::ostream& os) const {
  if (is_empty()) {
    os << "[Empty table]\n";
    return os;
  }

  os << "========== Table ==========\n";

  for (const auto& item : Base::_rows) {
    if (item._state == st_busy) {
      os << item._key << " " << item._data << "\n";
    }
  }

  os << "===========================\n";
  return os;
}

template <class TValue>
size_t HashTableOA<TValue>::h(const std::string& key) const noexcept {
  size_t hash = 0;
  for (size_t i = 0; i < key.length(); i++) {
    hash += key[i];
  }

  hash %= _size;
  return hash;
}

template <class TValue>
size_t HashTableOA<TValue>::hh(size_t index) const noexcept {
  return (index + _shift) % _size;
}

template <class TValue>
bool HashTableOA<TValue>::is_simple(size_t num, size_t size) const noexcept {
  return std::gcd(num, size) == 1;
}

#endif  // LIB_HASH_TABLE_OA_HASH_TABLE_OA_H_
