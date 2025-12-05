// Copyright 2025 Smirnov Nikita

#include<stdexcept>
#include "../lib_dsu/dsu.h"

DSU::DSU(size_t size) : _size(size) {
  if (_size == 0) {
    _parent = nullptr;
    _rank = nullptr;
    return;
  }

  _parent = new int[_size];
  _rank = new int[_size];

  for (size_t i = 0; i < _size; i++) {
    _parent[i] = static_cast<int>(i);
    _rank[i] = 0;
  }
}

DSU::~DSU() {
  delete[] _parent;
  delete[] _rank;
}

int DSU::find_rec(int x) {
  if (_parent[x] != x) {
    _parent[x] = find_rec(_parent[x]);
  }

  return _parent[x];
}

int DSU::find(int x) {
  if (x >= _size || x < 0) throw std::invalid_argument("This element does not "
    "exist in the DSU!");

  return find_rec(x);
}

void DSU::union_op(int x, int y) {
  if (x >= _size || y >= _size || x < 0 || y < 0) throw std::invalid_argument
  ("One of the elements does not exist in the DSU!");

  if (x == y) return;

  int parent_x = find(x);
  int parent_y = find(y);

  if (_rank[parent_x] > _rank[parent_y]) {
    _parent[parent_y] = parent_x;
  } else if (_rank[parent_x] < _rank[parent_y]) {
    _parent[parent_x] = parent_y;
  } else {
    _parent[parent_y] = parent_x;
    _rank[parent_x]++;
  }
}
