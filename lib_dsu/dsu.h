// Copyright 2025 Smirnov Nikita

#ifndef LIB_DSU_DSU_H_
#define LIB_DSU_DSU_H_

class DSU {
  int* _parent, *_rank;
  size_t _size;

 public:
  DSU(size_t size);
  ~DSU();

  size_t size() const noexcept { return _size; }

  void union_op(int x, int y);
  int find(int x);

 private:
  int find_rec(int x);
};

#endif  // LIB_DSU_DSU_H_
