// Copyright 2025 Smirnov Nikita

#ifndef LIB_TVECTOR_TVECTOR_H_
#define LIB_TVECTOR_TVECTOR_H_

#include <iostream>
#include <random>

enum State { empty, busy, deleted };

#define STEP_OF_CAPACITY 15

template <class T>
class TVector {
  T* _data;
  size_t _size;
  size_t _capacity;
  size_t _deleted;
  State* _states;

  template <typename ValueType>
  class IteratorBase {
   public:
    using value_type = ValueType;
    using pointer = ValueType*;
    using reference = ValueType&;

   private:
    pointer _current;
    pointer _base;
    pointer _end;
    State* _state_ptr;

    void find_next_busy() {
      if (!_current || !_state_ptr || _current >= _end) return;

      while (_current < _end && _state_ptr[_current - _base] != busy) {
        ++_current;
      }

      if (_current >= _end) {
        _current = _end;
      }
    }

    void find_prev_busy() {
      if (!_current || !_state_ptr || _current <= _base) return;

      while (_current > _base && _state_ptr[_current - _base] != busy) {
        --_current;
      }

      if (_state_ptr[_current - _base] != busy) {
        _current = _base;
      }
    }

   public:
     IteratorBase(pointer ptr = nullptr, pointer base = nullptr,
       pointer end = nullptr, State* state_ptr = nullptr)
       : _current(ptr), _base(base), _end(end), _state_ptr(state_ptr) {
       if (_current && _state_ptr && _state_ptr[_current - _base] != busy) {
         find_next_busy();
       }
     }

     reference operator*() const {
       return *_current;
     }

     pointer operator->() const {
       return _current;
     }

     IteratorBase& operator++() {
       if (_current < _end) {
         ++_current;
         find_next_busy();
       }
       return *this;
     }

     IteratorBase operator++(int) {
       IteratorBase tmp = *this;
       ++(*this);
       return tmp;
     }

     IteratorBase& operator--() {
       if (_current > _base) {
         --_current;
         find_prev_busy();
       }
       return *this;
     }

     IteratorBase operator--(int) {
       IteratorBase tmp = *this;
       --(*this);
       return tmp;
     }

     bool operator==(const IteratorBase& other) const {
       return _current == other._current;
     }

     bool operator!=(const IteratorBase& other) const {
       return !(*this == other);
     }
  };

 public:
  using iterator = IteratorBase<T>;
  using const_iterator = IteratorBase<const T>;

  explicit TVector(size_t size = 0);
  TVector(std::initializer_list<T>);
  TVector(const TVector<T>& other);
  ~TVector();

  // inline const State* states() const noexcept
  // { return _states; } // for debugging

  iterator begin_iter() noexcept {
    if (_size == 0) return end_iter();
    return iterator(_data, _data, _data + _capacity, _states);
  }

  iterator end_iter() noexcept {
    if (_size == 0) return iterator(nullptr, nullptr, nullptr, nullptr);
    return iterator(_data + _capacity, _data, _data + _capacity, _states);
  }

  const_iterator begin_iter() const noexcept {
    if (_size == 0) return end_iter();
    return const_iterator(_data, _data, _data + _capacity, _states);
  }

  const_iterator end_iter() const noexcept {
    if (_size == 0) return const_iterator(nullptr, nullptr, nullptr, nullptr);
    return const_iterator(_data + _capacity, _data, _data + _capacity, _states);
  }

  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;

  inline T* data() noexcept;
  inline T& front();
  inline T& back();
  inline T* begin() noexcept;
  inline T* end() noexcept;

  inline const T* data() const noexcept;
  inline size_t size() const noexcept;
  inline size_t capacity() const noexcept;
  inline const T& front() const;
  inline const T& back() const;
  inline const T* begin() const noexcept;
  inline const T* end() const noexcept;

  void push_front(const T& value);
  void push_back(const T& value);
  void insert(size_t pos, const T& value);
  void insert(size_t pos, size_t count, const T& value);

  void pop_front();
  void pop_back();
  void erase(T* frist, T* last);
  void erase(size_t pos);
  void erase(size_t first, size_t last);

  void replace(T* pos, const T& new_value);
  void replace(size_t pos, const T& new_value);

  void assign(size_t count, const T& value);
  inline T& at(size_t pos);
  void clear() noexcept;

  void shrink_to_fit() noexcept;
  void reserve(size_t new_capacity);
  void resize(size_t new_size);
  void resize(size_t new_size, const T& value);

  TVector<T>& operator=(const TVector<T>& other);
  bool operator==(const TVector<T>& other) const;
  bool operator!=(const TVector<T>& other) const;

  const T& operator[](size_t pos) const;
  T& operator[](size_t pos);

  template<typename T>
  friend void T_swap(T& first_elem, T& second_elem);

  template<typename T>
  friend void shuffle(TVector<T>& vec);

  template<typename T>
  friend void T_sort(TVector<T>& vec);

  template<typename T>
  friend T* find_first(TVector<T>& vec, const T& value);

  template<typename T>
  friend T* find_last(TVector<T>& vec, const T& value);

  template<typename T>
  friend TVector<T*> find(TVector<T>& vec, const T& value);

 private:
  void defragment();
  size_t real_pos(size_t pos) const;
  T* real_address(size_t pos);
  bool reallocate(size_t new_size);
  void reallocate_for_deleted();
  void create_new_arrays(size_t new_capacity, T*& new_data, State*& new_states);
  void copy_busy_elements(T* new_data, State* new_states, size_t limit);
  void replace_arrays(T* new_data, State* new_states, size_t new_capacity);
};

template <class T>
TVector<T>::TVector(size_t size) {
  _size = size;
  _capacity = _size;
  _deleted = 0;
  _data = (_capacity == 0) ? nullptr : new T[_capacity];
  _states = (_capacity == 0) ? nullptr : new State[_capacity];

  for (size_t i = 0; i < _size; i++) {
    _data[i] = T();
    _states[i] = busy;
  }
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> init_list) {
  _size = init_list.size();
  _capacity = _size;
  _deleted = 0;
  _data = (_capacity == 0) ? nullptr : new T[_capacity];
  _states = (_capacity == 0) ? nullptr : new State[_capacity];

  size_t i;
  auto it = init_list.begin();
  for (i = 0; it != init_list.end(); i++, it++) {
    _data[i] = *it;
    _states[i] = busy;
  }
}

template <class T>
TVector<T>::TVector(const TVector<T>& other) {
  _size = other._size;
  _capacity = other._size;
  _deleted = 0;
  _data = (_capacity == 0) ? nullptr : new T[_capacity];
  _states = (_capacity == 0) ? nullptr : new State[_capacity];

  size_t busy_count = 0;
  for (size_t i = 0; busy_count != other._size; i++) {
    if (other._states[i] == busy) {
      _data[busy_count] = other._data[i];
      _states[busy_count] = other._states[i];
      busy_count++;
    }
  }
}

template <class T>
TVector<T>::~TVector() {
  delete[] _data;
  delete[] _states;
}

template <class T>
inline bool TVector<T>::is_empty() const noexcept {
  return _size == 0;
}

template <class T>
inline T* TVector<T>::data() noexcept {
  return _data;
}

template <class T>
inline T& TVector<T>::front() {
  if (is_empty()) {
    throw std::out_of_range("Use front() in empty vector!");
  }
  size_t it = real_pos(0);
  return _data[it];
}

template <class T>
inline T& TVector<T>::back() {
  if (is_empty()) {
    throw std::out_of_range("Use back() in empty vector!");
  }
  size_t it = real_pos(_size - 1);
  return _data[it];
}

template <class T>
inline T* TVector<T>::begin() noexcept {
  T* main_address = real_address(0);
  return main_address;
}

template <class T>
inline T* TVector<T>::end() noexcept {
  T* main_address = nullptr;
  if (!is_empty()) {
    main_address = (real_address(_size - 1) + 1);
  }
  return main_address;
}

template<class T>
inline const T* TVector<T>::data() const noexcept {
  return _data;
}

template<class T>
inline size_t TVector<T>::size() const noexcept {
  return _size;
}

template<class T>
inline size_t TVector<T>::capacity() const noexcept {
  return _capacity;
}

template <class T>
inline const T& TVector<T>::front() const {
  if (is_empty()) throw std::out_of_range("Use front() in empty vector!");
  size_t it = real_pos(0);
  return _data[it];
}

template <class T>
inline const T& TVector<T>::back() const {
  if (is_empty()) throw std::out_of_range("Use back() in empty vector!");
  size_t it = real_pos(_size - 1);
  return _data[it];
}

template <class T>
inline const T* TVector<T>::begin() const noexcept {
  T* main_address = real_address(0);
  return main_address;
}

template <class T>
inline const T* TVector<T>::end() const noexcept {
  T* main_address = nullptr;
  if (!is_empty()) {
    main_address = (real_address(_size - 1) + 1);
  }
  return main_address;
}

template <class T>
void TVector<T>::push_front(const T& value) {
  for (size_t i = 0; i < _size + _deleted; i++) {
    if (_states[i] != busy && _states[i + 1] == busy) {
      _data[i] = value;
      if (_states[i] == deleted) --_deleted;
      _states[i] = busy;
      _size++;
      return;
    }
    if (_states[i] == busy) {
      break;
    }
  }

  size_t limit = _size + _deleted;

  if (reallocate(_size + 1 + _deleted)) {
    limit = _size;
  }

  for (size_t j = limit; j > 0; j--) {
    _data[j] = _data[j - 1];
    _states[j] = _states[j - 1];
  }

  _data[0] = value;
  _states[0] = busy;
  _size++;
}

template <class T>
void TVector<T>::push_back(const T& value) {
  if (_size != 0) {
    size_t last_busy_pos = real_pos(_size - 1);

    if (last_busy_pos + 1 < _capacity
      && (_states[last_busy_pos + 1] != busy)) {
      size_t insert_pos = last_busy_pos + 1;
      _data[insert_pos] = value;
      _states[insert_pos] = busy;
      _size++;
      if (_states[insert_pos] == deleted) --_deleted;
      return;
    }
  }
  reallocate(_size + 1 + _deleted);
  _data[_size] = value;
  _states[_size] = busy;
  _size++;
}

template<class T>
void TVector<T>::insert(size_t pos, const T& value) {
  if (_size == 0 || pos == _size) {
    push_back(value);
    return;
  }

  if (pos > _size) {
    throw std::out_of_range("Inserting an index outside the range!");
  }

  size_t insert_pos = real_pos(pos);
  if (insert_pos != 0) {
    if (_states[insert_pos - 1] == deleted) {
      _data[insert_pos - 1] = value;
      _states[insert_pos - 1] = busy;
      --_deleted;
      _size += 1;
      return;
    }
  }

  size_t limit = _size + _deleted;

  if (reallocate(_size + 1 + _deleted)) {
    limit = _size;
    insert_pos = pos;
  }

  for (size_t j = limit; j > insert_pos; j--) {
    _data[j] = _data[j - 1];
    _states[j] = _states[j - 1];
  }

  _data[insert_pos] = value;
  _states[insert_pos] = busy;
  _size++;
}

template<class T>
void TVector<T>::insert(size_t pos, size_t count, const T& value) {
  if (count == 0) {
    return;
  }

  if (_size == 0 || pos == _size) {
    for (size_t i = 0; i < count; i++) {
      push_back(value);
    }
    return;
  }

  if (pos > _size) {
    throw std::out_of_range("Inserting an index outside the range!");
  }

  size_t insert_pos = real_pos(pos);
  size_t start_pos = (pos == 0) ? 0 : real_pos(pos - 1) + 1;
  size_t count_deleted = 0;

  for (size_t i = start_pos; i < insert_pos && count_deleted < count; i++) {
    if (_states[i] == deleted) {
      count_deleted++;
    } else {
      count_deleted = 0;
      break;
    }
  }

  if (count_deleted >= count) {
    size_t insert_start = insert_pos - count_deleted;
    for (size_t i = 0; i < count; i++) {
      _data[insert_start + i] = value;
      _states[insert_start + i] = busy;
    }
    _size += count;
    _deleted -= count;
    return;
  }


  size_t limit = _size + count - 1 + _deleted;

  if (reallocate(_size + 1 + _deleted)) {
    limit = _size + count - 1;
    insert_pos = pos;
  }

  for (size_t i = limit;
    i >= insert_pos + count; i--) {
    _data[i] = _data[i - count];
    _states[i] = _states[i - count];
  }

  for (size_t i = 0; i < count; ++i) {
    _data[insert_pos + i] = value;
    _states[insert_pos + i] = busy;
  }

  _size += count;
}

template<class T>
void TVector<T>::pop_front() {
  if (is_empty()) {
    throw std::logic_error("Delete element in empty vector!");
  }

  for (size_t i = 0; i < _capacity; i++) {
    if (_states[i] == busy) {
      _states[i] = deleted;
      _size--;
      _deleted++;
      reallocate_for_deleted();
      return;
    }
  }
}

template<class T>
void TVector<T>::pop_back() {
  if (is_empty()) {
    throw std::logic_error("Delete element in empty vector!");
  }

  for (size_t i = _size + _deleted - 1; i != static_cast<size_t>(-1); i--) {
    if (_states[i] == busy) {
      _states[i] = deleted;
      _size--;
      _deleted++;
      reallocate_for_deleted();
      return;
    }
  }
}

template<class T>
void TVector<T>::erase(T* first, T* last) {
  if (is_empty()) {
    throw std::logic_error("Delete element in empty vector!");
  }

  if (first < begin() || last > end()) {
    throw std::out_of_range("Pointer is out of Vector bounds!");
  }

  if (last <= first) {
    throw std::invalid_argument("last must be > first");
  }

  size_t first_pos = first - begin();

  size_t last_pos = last - begin();

  erase(first_pos, last_pos);
}

template<class T>
void TVector<T>::erase(size_t pos) {
  if (is_empty()) {
    throw std::logic_error("Delete element in empty vector!");
  }

  if (pos >= _size) {
    throw std::out_of_range("Erasing an index outside the range!");
  }

  size_t erase_pos = real_pos(pos);
  _states[erase_pos] = deleted;

  _size--;
  _deleted++;
  reallocate_for_deleted();
}

template<class T>
void TVector<T>::erase(size_t first, size_t last) {
  if (is_empty()) {
    throw std::logic_error("Delete element in empty vector!");
  }

  if (first >= last || last > _size) {
    throw std::out_of_range("Invalid erase range!");
  }

  size_t real_first = real_pos(first);
  size_t real_last = real_pos(last - 1);

  size_t busy_erased = 0;
  for (size_t i = real_first; i <= real_last; i++) {
    if (_states[i] == busy) {
      _states[i] = deleted;
      busy_erased++;
    }
  }

  _size -= busy_erased;
  _deleted += busy_erased;
  reallocate_for_deleted();
}

template<class T>
void TVector<T>::replace(T* pos, const T& new_value) {
  if (pos < begin() || pos >= end()) {
    throw std::out_of_range("Pointer is out of Vector bounds!");
  }

  size_t replace_pos = real_pos(pos - begin());
  _data[replace_pos] = new_value;
}

template<class T>
void TVector<T>::replace(size_t pos, const T& new_value) {
  if (pos >= _size) {
    throw std::out_of_range("Replacing an index outside the range!");
  }

  size_t replace_pos = real_pos(pos);
  _data[replace_pos] = new_value;
}

template<class T>
void TVector<T>::assign(size_t count, const T& value) {
  clear();

  if (count == 0) return;

  if (count > _capacity) {
    reserve(count);
  }

  for (size_t i = 0; i < count; i++) {
    _data[i] = value;
    _states[i] = busy;
  }

  _size = count;
  _deleted = 0;
}

template<class T>
inline T& TVector<T>::at(size_t pos) {
  if (pos >= _size) {
    throw std::out_of_range("Index out of range in at()");
  }
  size_t it = real_pos(pos);
  return _data[it];
}

template<class T>
void TVector<T>::clear() noexcept {
  for (size_t i = 0; i < _size + _deleted; i++) {
    _states[i] = empty;
  }

  _size = 0;
  _deleted = 0;
}

template<class T>
void TVector<T>::shrink_to_fit() noexcept {
  if (_capacity == _size || _size == 0) return;

  T* new_data;
  State* new_states;

  create_new_arrays(_size, new_data, new_states);

  copy_busy_elements(new_data, new_states, _size + _deleted);

  replace_arrays(new_data, new_states, _size);
}

template<class T>
void TVector<T>::reserve(size_t new_capacity) {
  if (new_capacity <= _capacity) {
    return;
  }

  T* new_data;
  State* new_states;

  create_new_arrays(new_capacity, new_data, new_states);
  if (_size != 0) {
    copy_busy_elements(new_data, new_states, _size + _deleted);
  }

  replace_arrays(new_data, new_states, new_capacity);
}

template<class T>
void TVector<T>::resize(size_t new_size) {
  resize(new_size, T());
}

template<class T>
void TVector<T>::resize(size_t new_size, const T& value) {
  if (_size == new_size) return;

  if (new_size == 0) {
    clear();
    return;
  }

  if (_size > new_size) {
    for (size_t i = real_pos(new_size); i < _size + _deleted; i++) {
      if (_states[i] != empty) {
        if (_states[i] == deleted) --_deleted;
        _states[i] = empty;
      }
    }
    _size = new_size;
    reallocate_for_deleted();
    return;
  }
  if (_size < new_size) {
    reserve(new_size);

    for (size_t i = _size + _deleted; i < new_size + _deleted; i++) {
      _data[i] = value;
      _states[i] = busy;
    }
    _size = new_size;
  }
}

template<class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
  if (this == &other) {
    return *this;
  }
  T* new_data;
  State* new_states;

  create_new_arrays(other._size, new_data, new_states);

  size_t busy_count = 0;
  for (size_t i = 0; i < other._capacity; ++i) {
    if (other._states[i] == busy) {
      new_data[busy_count] = other._data[i];
      new_states[busy_count] = other._states[i];
      busy_count++;
    }
  }
  delete[] _data;
  delete[] _states;

  _data = new_data;
  _states = new_states;
  _size = other._size;
  _capacity = other._size;
  _deleted = 0;

  return *this;
}

template<class T>
bool TVector<T>::operator==(const TVector<T>& other) const {
  if (this == &other) return true;
  if (_size != other._size) return false;
  if (_size == 0) return true;

  size_t phys_pos1 = 0;
  size_t phys_pos2 = 0;
  size_t busy_count = 0;

  while (busy_count < _size) {
    while (phys_pos1 < _capacity && _states[phys_pos1] != busy) {
      ++phys_pos1;
    }

    while (phys_pos2 < other._capacity && other._states[phys_pos2] != busy) {
      ++phys_pos2;
    }

    if (phys_pos1 >= _capacity || phys_pos2 >= other._capacity) {
      return false;
    }

    if (_data[phys_pos1] != other._data[phys_pos2]) {
      return false;
    }

    ++phys_pos1;
    ++phys_pos2;
    ++busy_count;
  }

  return true;
}

template<class T>
bool TVector<T>::operator!=(const TVector<T>& other) const {
  return !(*this == other);
}

template<class T>
const T& TVector<T>::operator[](size_t pos) const {
  size_t it = real_pos(pos);
  return _data[it];
}

template<class T>
T& TVector<T>::operator[](size_t pos) {
  size_t it = real_pos(pos);
  return _data[it];
}

template<class T>
void TVector<T>::defragment() {
  if (_deleted == 0) return;

  T* new_data;
  State* new_states;

  size_t new_capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

  create_new_arrays(new_capacity, new_data, new_states);

  copy_busy_elements(new_data, new_states, _size + _deleted);

  replace_arrays(new_data, new_states, new_capacity);
}

template<class T>
void T_swap(T& first_elem, T& second_elem) {
  if (first_elem == second_elem) {
    return;
  }

  T temp = first_elem;
  first_elem = second_elem;
  second_elem = temp;
}

template<class T>
void shuffle(TVector<T>& vec) {
  if (vec.size() < 2) return;

  vec.defragment();

  static std::random_device rd;
  static std::mt19937 gen(rd());

  for (size_t i = 0; i < vec.size(); i++) {
    std::uniform_int_distribution<size_t> dist(0, i);
    size_t rand_i = dist(gen);
    T_swap(vec[i], vec[rand_i]);
  }
}

template<class T>
T median_of_three(T a, T b, T c) {
  if (a < b) {
    if (b < c) return b;
    else if (a < c) return c;
    else return a;
  } else {
    if (a < c) return a;
    else if (b < c) return c;
    else return b;
  }
}

template<class T>
void insertion_sort(TVector<T>& vec, size_t l, size_t r) {
  for (size_t i = l + 1; i <= r; i++) {
    T key = vec[i];
    size_t j = i - 1;
    while (j >= l && vec[j] > key) {
      vec[j + 1] = vec[j];
      j--;
    }
    vec[j + 1] = key;
  }
}

template<class T>
void hoar_sort_rec(TVector<T>& vec, size_t  l, size_t  r) {
  if (r - l < 16) {
    insertion_sort(vec, l, r);
    return;
  }

  size_t i = l, j = r;
  T x = median_of_three(vec[l], vec[(l + r) / 2], vec[r]);

  do {
    while (vec[i] < x) i++;
    while (vec[j] > x) j--;

    if (i <= j) {
      if (i < j) {
        T_swap(vec[i], vec[j]);
      }
      i++;
      j--;
    }
  } while (i <= j);

  if (l < j) hoar_sort_rec(vec, l, j);
  if (i < r) hoar_sort_rec(vec, i, r);
}

template<class T>
void T_sort(TVector<T>& vec) {
  if (vec.size() <= 1) {
    return;
  }

  vec.defragment();

  hoar_sort_rec(vec, 0, (vec.size() - 1));
}

template<class T>
T* find_first(TVector<T>& vec, const T& value) {
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] == value) {
      return &vec[i];
    }
  }
  return nullptr;
}

template<class T>
T* find_last(TVector<T>& vec, const T& value) {
  for (size_t i = vec.size() - 1; i != static_cast<size_t>(-1); i--) {
    if (vec[i] == value) {
      return &vec[i];
    }
  }
  return nullptr;
}

template<class T>
TVector<T*> find(TVector<T>& vec, const T& value) {
  TVector<T*> found;
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] == value) {
      found.push_back(&vec[i]);
    }
  }
  return found;
}

template<class T>
size_t TVector<T>::real_pos(size_t pos) const {
  if (_deleted == 0) return pos;
  size_t busy_count = 0;
  for (size_t i = 0; i < _size + _deleted; i++) {
    if (_states[i] == busy) {
      if (busy_count == pos) {
        return i;
      }
      busy_count++;
    }
  }
  return -1;
}

template<class T>
T* TVector<T>::real_address(size_t pos) {
  if (_deleted == 0) return &_data[pos];
  size_t busy_count = 0;
  for (size_t i = 0; i < _size + _deleted; i++) {
    if (_states[i] == busy) {
      if (busy_count == pos) {
        return &_data[i];
      }
      busy_count++;
    }
  }
  return nullptr;
}

template<class T>
inline bool TVector<T>::is_full() const noexcept {
  return _size == _capacity;
}

template<class T>
bool TVector<T>::reallocate(size_t new_size) {
  if (new_size <= _capacity) return false;
  size_t new_capacity = ((new_size - _deleted)
    / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
  T* new_data;
  State* new_states;

  create_new_arrays(new_capacity, new_data, new_states);
  if (_size != 0) {
    copy_busy_elements(new_data, new_states, _size + _deleted);
  }

  replace_arrays(new_data, new_states, new_capacity);
  return true;
}

template<class T>
void TVector<T>::reallocate_for_deleted() {
  constexpr double DELETED_THRESHOLD = 0.15;
  constexpr size_t MAX_DELETED_COUNT = 100000;

  if (_size + _deleted == 0) {
    return;
  }

  if (_size == 0) {
    size_t new_capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    T* new_data;
    State* new_states;
    create_new_arrays(new_capacity, new_data, new_states);
    replace_arrays(new_data, new_states, new_capacity);
    return;
  }

  if (_deleted >= DELETED_THRESHOLD * (_size + _deleted)
    || _deleted >= MAX_DELETED_COUNT) {
    size_t new_capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    T* new_data;
    State* new_states;
    create_new_arrays(new_capacity, new_data, new_states);
    copy_busy_elements(new_data, new_states, _size + _deleted);
    replace_arrays(new_data, new_states, new_capacity);
  }
}

template<class T>
void TVector<T>::create_new_arrays
(size_t new_capacity, T*& new_data, State*& new_states) {
  new_data = new T[new_capacity];
  new_states = new State[new_capacity];

  for (size_t i = 0; i < new_capacity; i++) {
    new_states[i] = empty;
  }
}

template<class T>
void TVector<T>::copy_busy_elements
(T* new_data, State* new_states, size_t limit) {
  size_t busy_count = 0;
  for (size_t i = 0; i < limit; i++) {
    if (_states[i] == busy) {
      new_data[busy_count] = _data[i];
      new_states[busy_count] = busy;
      busy_count++;
    }
  }
}

template<class T>
void TVector<T>::replace_arrays
(T* new_data, State* new_states, size_t new_capacity) {
  delete[] _data;
  delete[] _states;

  _data = new_data;
  _states = new_states;
  _capacity = new_capacity;
  _deleted = 0;
}

#endif  // LIB_TVECTOR_TVECTOR_H_
