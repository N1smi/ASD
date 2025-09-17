// Copyright 2025 Smirnov Nikita

#ifndef LIB_MVECTOR_MVECTOR_H_
#define LIB_MVECTOR_MVECTOR_H_

#include "../lib_tvector/tvector.h"

template <class T>
class MVector : public TVector<T> {

public:
  MVector(size_t size = 0);
  MVector(std::initializer_list<T>);
  MVector(const MVector<T>& other);
  ~MVector();
};

template <class T>
MVector<T>::MVector(size_t size) : TVector<T>(size) {}

template <class T>
MVector<T>::MVector(std::initializer_list<T> initList) : TVector<T>(initList) {}

template <class T>
MVector<T>::MVector(const MVector<T>& other) : TVector<T>(other) {}

template <class T>
MVector<T>::~MVector() = default;


#endif // LIB_MVECTOR_MVECTOR_H_
