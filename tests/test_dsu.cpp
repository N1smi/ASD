// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_dsu/dsu.h"

TEST(TestDSULib, CreateDSUWithSize) {
  DSU dsu(5);

  EXPECT_EQ(dsu.size(), 5);
}

TEST(TestDSULib, InitialAllSeparate) {
  DSU dsu(5);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(dsu.find(i), i);
  }
}

TEST(TestDSULib, FindThrowWhenInvalidElement) {
  DSU dsu(5);

  EXPECT_ANY_THROW(dsu.find(5));
  EXPECT_ANY_THROW(dsu.find(10));
  EXPECT_ANY_THROW(dsu.find(-2));
}

TEST(TestDSULib, UnionThrowWhenInvalidElements) {
  DSU dsu(5);

  EXPECT_ANY_THROW(dsu.union_op(6, 4));
  EXPECT_ANY_THROW(dsu.union_op(-1, 2));
  EXPECT_ANY_THROW(dsu.union_op(1, 10));
  EXPECT_ANY_THROW(dsu.union_op(4, -5));
}

TEST(TestDSULib, UnionSameElement) {
  DSU dsu(5);

  dsu.union_op(2, 2);

  EXPECT_EQ(dsu.find(2), 2);
}

TEST(TestDSULib, UnionTransitivity) {
  DSU dsu(5);

  dsu.union_op(0, 1);
  dsu.union_op(1, 2);

  EXPECT_EQ(dsu.find(0), dsu.find(2));

  dsu.union_op(3, 4);
  dsu.union_op(2, 3);

  EXPECT_EQ(dsu.find(0), dsu.find(4));
}


TEST(TestDSULib, PathCompression) {
  DSU dsu(5);

  for (int i = 1; i < 5; i++) {
    dsu.union_op(i - 1, i);
  }

  int root = dsu.find(4);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(dsu.find(i), root);
  }
}

TEST(TestDSULib, UnionIndependentSets) {
  DSU dsu(6);

  dsu.union_op(0, 1);
  dsu.union_op(2, 3);
  dsu.union_op(4, 5);

  EXPECT_NE(dsu.find(1), dsu.find(3));
  EXPECT_NE(dsu.find(1), dsu.find(5));
  EXPECT_NE(dsu.find(3), dsu.find(5));
}

TEST(TestDSULib, UnionSequenceOfOperations) {
  DSU dsu(10);

  dsu.union_op(0, 1);
  dsu.union_op(2, 3);
  dsu.union_op(0, 2);

  dsu.union_op(4, 5);
  dsu.union_op(6, 7);
  dsu.union_op(4, 6);

  EXPECT_NE(dsu.find(3), dsu.find(7));

  dsu.union_op(0, 4);

  for (int i = 0; i <= 7; i++) {
    EXPECT_EQ(dsu.find(0), dsu.find(i));
  }
}

TEST(TestDSULib, RankIncreasesOnEqualRanks) {
  DSU dsu(4);

  dsu.union_op(0, 1);
  dsu.union_op(2, 3);

  dsu.union_op(2, 0);

  EXPECT_EQ(dsu.find(1), dsu.find(2));
}

TEST(TestDSULib, LargerRankBecomesRoot) {
  DSU dsu(6);

  dsu.union_op(0, 1);
  dsu.union_op(2, 3);
  dsu.union_op(0, 2);

  dsu.union_op(4, 5);

  dsu.union_op(0, 4);

  EXPECT_EQ(dsu.find(4), dsu.find(0));
  EXPECT_EQ(dsu.find(5), dsu.find(0));
}
