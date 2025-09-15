// Copyright 2025 Smirnov Nikita

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

TEST(TestTVectorLib, CreateDefaultVector) {
  TVector<int> vec_1;
  int* pointer = nullptr;

  EXPECT_EQ(static_cast<size_t>(0), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(0), vec_1.capacity());
  EXPECT_EQ(pointer, vec_1.data());
}

TEST(TestTVectorLib, CreateVectorWithInitialization) {
  TVector<char> vec_1(3);

  EXPECT_EQ(static_cast<size_t>(3), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(3), vec_1.capacity());

  for (size_t i = 0; i < vec_1.size(); i++) {
    EXPECT_EQ('\0', vec_1[i]);
  }
}

TEST(TestTVectorLib, CreateVectorWithInitializationList) {
  TVector<float> vec_1({ 1.0f, 0.0f, 2.356f });

  EXPECT_EQ(static_cast<size_t>(3), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(3), vec_1.capacity());
  EXPECT_EQ(1.0f, vec_1[0]);
  EXPECT_EQ(0.0f, vec_1[1]);
  EXPECT_EQ(2.356f, vec_1[2]);
}

TEST(TestTVectorLib, CreateVectorWithCopy) {
  TVector<int> vec_1({ -1, 2, 3 });
  TVector<int> vec_2(vec_1);

  EXPECT_EQ(vec_1.size(), vec_2.size());
  EXPECT_EQ(vec_1.capacity(), vec_2.capacity());

  for (size_t i = 0; i < vec_1.size(); i++) {
    EXPECT_EQ(vec_1[i], vec_2[i]);
  }
}

TEST(TestTVectorLib, ThrowWhenReferToPositionAbroadInAt) {
  TVector<double> vec_1(100);

  EXPECT_ANY_THROW(vec_1.at(100));
}

TEST(TestTVectorLib, IsEmpty) {
  TVector<char> vec_1;

  EXPECT_TRUE(vec_1.is_empty());
}

TEST(TestTVectorLib, FrontBackBeginEnd) {
  TVector<int> vec_1({ 1000, 2, 456, 777 });

  EXPECT_EQ(1000, vec_1.front());
  EXPECT_EQ(777, vec_1.back());
  EXPECT_EQ(1000, *vec_1.begin());
  EXPECT_EQ(777, *(vec_1.end() - 1));
}

TEST(TestTVectorLib, ThrowWhenFrontInEmptyVector) {
  TVector<double> vec_1;

  EXPECT_ANY_THROW(vec_1.front());
}

TEST(TestTVectorLib, ThrowWhenBackInEmptyVector) {
  TVector<double> vec_1;

  EXPECT_ANY_THROW(vec_1.back());
}

TEST(TestTVectorLib, BeginAndEndInEmptyVector) {
  TVector<int> vec_1;

  EXPECT_EQ(nullptr, vec_1.begin());
  EXPECT_EQ(nullptr, vec_1.end());
}

TEST(TestTVectorLib, PushFront) {
  TVector<char> vec_1({ '$', '2', '3' });

  vec_1.push_front('5');

  EXPECT_EQ(static_cast<size_t>(4), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(15), vec_1.capacity());
  EXPECT_EQ('5', vec_1.front());
  EXPECT_EQ('3', vec_1.back());
  EXPECT_EQ('$', vec_1[1]);
  EXPECT_EQ('2', vec_1[2]);
}

TEST(TestTVectorLib, PushFrontInEmptyVector) {
  TVector<int> vec_1;

  vec_1.push_front(2000);

  EXPECT_EQ(static_cast<size_t>(1), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(15), vec_1.capacity());
  EXPECT_EQ(2000, vec_1.front());
  EXPECT_EQ(2000, vec_1.back());
}

TEST(TestTVectorLib, PushBack) {
  TVector<int> vec_1({ 1, 2, 3 });

  vec_1.push_back(4);

  EXPECT_EQ(static_cast<size_t>(4), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(15), vec_1.capacity());
  EXPECT_EQ(1, vec_1.front());
  EXPECT_EQ(4, vec_1.back());
  EXPECT_EQ(2, vec_1[1]);
  EXPECT_EQ(3, vec_1[2]);
}

TEST(TestTVectorLib, PushBackInEmptyVector) {
  TVector<float> vec_1;

  vec_1.push_back(2.7f);

  EXPECT_EQ(static_cast<size_t>(1), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(15), vec_1.capacity());
  EXPECT_EQ(2.7f, vec_1.front());
  EXPECT_EQ(2.7f, vec_1.back());
}

TEST(TestTVectorLib, SeveralPush) {
  TVector<int> vec_1(15);

  vec_1.push_back(3);
  vec_1.push_front(2);
  vec_1.push_back(9);
  vec_1.push_front(5);

  EXPECT_EQ(static_cast<size_t>(19), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(5, vec_1.front());
  EXPECT_EQ(9, vec_1.back());
}

TEST(TestTVectorLib, Insert) {
  TVector<int> vec_1({ 1, 2, 3, 10 });

  vec_1.insert(3, 111);
  vec_1.insert(4, 222);

  EXPECT_EQ(static_cast<size_t>(6), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(15), vec_1.capacity());
  EXPECT_EQ(111, vec_1[3]);
  EXPECT_EQ(222, vec_1[4]);
}

TEST(TestTVectorLib, ThrowWhenInsertInNonExistentPosition) {
  TVector<int> vec_1({ 1, 4, 10 });

  EXPECT_ANY_THROW(vec_1.insert(4, 10));
}

TEST(TestTVectorLib, InsertInEmptyVector) {
  TVector<int> vec_1;
  vec_1.insert(22, 42);

  EXPECT_EQ(static_cast<size_t>(1), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(15), vec_1.capacity());
  EXPECT_EQ(42, vec_1[0]);
}

TEST(TestTVectorLib, PopFront) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
      16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  vec_1.pop_front();

  for (size_t i = 0; i < 4; i++) {
    vec_1.pop_front();
  }

  EXPECT_EQ(static_cast<size_t>(25), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(6, vec_1[0]);
}

TEST(TestTVectorLib, PopFrontWithPushFront) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  for (size_t i = 0; i < 2; i++) {
    vec_1.pop_front();
  }

  for (size_t i = 0; i < 2; i++) {
    vec_1.push_front(999);
  }

  EXPECT_EQ(static_cast<size_t>(30), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(999, vec_1[0]);
}

TEST(TestTVectorLib, PopFrontWithPushBack) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  for (size_t i = 0; i < 2; i++) {
    vec_1.pop_front();
  }

  vec_1.push_back(111);

  for (size_t i = 0; i < 2; i++) {
    vec_1.pop_front();
  }

  vec_1.push_back(112);

  EXPECT_EQ(static_cast<size_t>(28), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(112, vec_1[27]);
}

TEST(TestTVectorLib, PopFrontWithInsert) {
  TVector<int> vec_1(15);

  vec_1.push_front(111);

  for (size_t i = 0; i < 2; i++) {
    vec_1.pop_front();
  }

  vec_1.insert(0, 111);
  vec_1.insert(7, 222);

  EXPECT_EQ(static_cast<size_t>(16), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(111, vec_1[0]);
  EXPECT_EQ(222, vec_1[7]);
}

TEST(TestTVectorLib, ThrowWhenPopFrontInEmptyVector) {
  TVector<int> vec_1;

  EXPECT_ANY_THROW(vec_1.pop_front());
}

TEST(TestTVectorLib, PopBack) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  vec_1.pop_back();

  for (size_t i = 0; i < 4; i++) {
    vec_1.pop_back();
  }

  EXPECT_EQ(static_cast<size_t>(25), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(25, vec_1.back());
}

TEST(TestTVectorLib, ThrowWhenPopBackInEmptyVector) {
  TVector<int> vec_1;

  EXPECT_ANY_THROW(vec_1.pop_back());
}

TEST(TestTVectorLib, PopBackWithPopFront) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  vec_1.pop_front();
  vec_1.pop_back();
  vec_1.pop_front();

  EXPECT_EQ(static_cast<size_t>(27), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(29, vec_1.back());
  EXPECT_EQ(3, vec_1.front());
}

TEST(TestTVectorLib, DeleteAllAndPushOrInsert) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  for (size_t i = 0; i < 30; i++) {
    vec_1.pop_back();
  }

  EXPECT_EQ(static_cast<size_t>(15), vec_1.capacity());

  vec_1.push_back(111);
  EXPECT_EQ(111, vec_1[0]);

  vec_1.pop_back();
  vec_1.push_front(222);
  EXPECT_EQ(222, vec_1[0]);

  vec_1.pop_back();
  vec_1.insert(2, 333);
  EXPECT_EQ(333, vec_1[0]);
}

TEST(TestTVectorLib, PopBackWithPushFront) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  for (size_t i = 0; i < 2; i++) {
    vec_1.pop_back();
  }

  for (size_t i = 0; i < 2; i++) {
    vec_1.push_front(999);
  }

  EXPECT_EQ(static_cast<size_t>(30), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(999, vec_1[0]);
  EXPECT_EQ(28, vec_1.back());
}

TEST(TestTVectorLib, PopBackWithPushBack) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

  for (size_t i = 0; i < 2; i++) {
    vec_1.pop_back();
  }

  for (size_t i = 0; i < 2; i++) {
    vec_1.push_back(111 + i);
  }

  EXPECT_EQ(static_cast<size_t>(30), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(111, vec_1[28]);
  EXPECT_EQ(112, vec_1[29]);
}

TEST(TestTVectorLib, PopBackWithInsert) {
  TVector<int> vec_1(15);

  for (size_t i = 0; i < 1; i++) {
    vec_1.push_front(111);
  }

  for (size_t i = 0; i < 2; i++) {
    vec_1.pop_back();
  }

  vec_1.insert(14, 111);
  vec_1.insert(13, 222);

  EXPECT_EQ(static_cast<size_t>(16), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(111, vec_1[15]);
  EXPECT_EQ(222, vec_1[13]);
}

TEST(TestTVectorLib, Erase) {
  TVector<int> vec_1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
   11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 });

  vec_1.push_front(111);
  vec_1.push_back(222);
  vec_1.pop_front();
  vec_1.pop_back();
  vec_1.erase(18);

  EXPECT_EQ(static_cast<size_t>(25), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(26, vec_1.back());
  EXPECT_EQ(20, vec_1[18]);
}

TEST(TestTVectorLib, ThrowWhenEraseInEmptyVector) {
  TVector<int> vec_1;

  EXPECT_ANY_THROW(vec_1.erase(5));
}

TEST(TestTVectorLib, ThrowWhenEraseForNonExistentPosition) {
  TVector<int> vec_1(10);

  EXPECT_ANY_THROW(vec_1.erase(10));
}

TEST(TestTVectorLib, SeveralPushInsertAndErase) {
  TVector<int> vec_1;

  for (size_t i = 0; i < 50; i++) {
    vec_1.insert(i, i + 1);
  }

  for (size_t i = 0; i < 3; i++) {
    vec_1.erase(0);
  }

  for (size_t i = 0; i < 3; i++) {
    vec_1.push_front(0);
  }

  for (size_t i = 0; i < 3; i++) {
    vec_1.erase(24);
  }

  vec_1.erase(46);
  vec_1.push_back(999);
  vec_1.insert(24, 1111);

  EXPECT_EQ(static_cast<size_t>(48), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(0, vec_1[0]);
  EXPECT_EQ(1111, vec_1[24]);
  EXPECT_EQ(999, vec_1.back());
}

TEST(TestTVectorLib, InsertWithCountInEmptyVector) {
  TVector<int> vec_1;
  vec_1.insert(150, 50, 1);

  EXPECT_EQ(static_cast<size_t>(50), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(1, vec_1[0]);
  EXPECT_EQ(1, vec_1[49]);
}

TEST(TestTVectorLib, InsertWithCountAndDeleted) {
  TVector<int> vec_1;
  vec_1.insert(0, 50, 1);

  for (size_t i = 0; i < 3; i++) {
    vec_1.erase(1);
  }

  vec_1.insert(1, 2, 3);
  vec_1.insert(7, 2, 3);

  EXPECT_EQ(static_cast<size_t>(51), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(3, vec_1[1]);
  EXPECT_EQ(3, vec_1[2]);
  EXPECT_EQ(3, vec_1[7]);
  EXPECT_EQ(3, vec_1[8]);
}

TEST(TestTVectorLib, InsertWithCountWithoutDeleted) {
  TVector<int> vec_1;
  vec_1.insert(0, 50, 2);
  vec_1.insert(25, 3, 5);

  EXPECT_EQ(static_cast<size_t>(53), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(5, vec_1[25]);
  EXPECT_EQ(5, vec_1[26]);
  EXPECT_EQ(5, vec_1[27]);
}

TEST(TestTVectorLib, InsertWithZeroCount) {
  TVector<int> vec_1(90);
  vec_1.insert(2, 0, 45);

  EXPECT_EQ(static_cast<size_t>(90), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(90), vec_1.capacity());
  EXPECT_EQ(0, vec_1[2]);
}

TEST(TestTVectorLib, ThrowWhenInsertWithCountInNonExistentPosition) {
  TVector<int> vec_1({ 1, 4 , 10 });

  EXPECT_ANY_THROW(vec_1.insert(4, 10, 10));
}

TEST(TestTVectorLib, ThrowWhenEraseWithRangeInEmptyVector) {
  TVector<int> vec_1;

  EXPECT_ANY_THROW(vec_1.erase(5, 9));
}

TEST(TestTVectorLib, ThrowWhenEraseWithIncorrectRange) {
  TVector<int> vec_1(90);

  EXPECT_ANY_THROW(vec_1.erase(5, 5));
  EXPECT_ANY_THROW(vec_1.erase(5, 91));
}

TEST(TestTVectorLib, EraseWithRangeWithoutDeleted) {
  TVector<int> vec_1;
  for (size_t i = 0; i < 50; i++) {
    vec_1.insert(i, i + 1);
  }

  vec_1.erase(1, 6);

  EXPECT_EQ(static_cast<size_t>(45), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(7, vec_1[1]);
  EXPECT_EQ(8, vec_1[2]);
}

TEST(TestTVectorLib, EraseWithRangeAndDeleted) {
  TVector<int> vec_1;
  for (size_t i = 0; i < 50; i++) {
    vec_1.insert(i, i + 1);
  }

  vec_1.pop_front();
  vec_1.erase(0, 6);

  EXPECT_EQ(static_cast<size_t>(43), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(8, vec_1[0]);
  EXPECT_EQ(9, vec_1[1]);
  EXPECT_EQ(50, vec_1.back());
}

TEST(TestTVectorLib, EraseWithPointers) {
  TVector<int> vec_1;
  for (size_t i = 0; i < 50; i++) {
    vec_1.insert(i, i + 1);
  }

  vec_1.erase(vec_1.begin() + 1, vec_1.begin() + 8);

  EXPECT_EQ(static_cast<size_t>(43), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(1, vec_1[0]);
  EXPECT_EQ(9, vec_1[1]);
  EXPECT_EQ(50, vec_1.back());
}

TEST(TestTVectorLib, EraseWithPointersAndDeleted) {
  TVector<int> vec_1;
  for (size_t i = 0; i < 50; i++) {
    vec_1.insert(i, i + 1);
  }

  vec_1.erase(1);
  vec_1.erase(vec_1.begin() + 1, vec_1.begin() + 7);

  EXPECT_EQ(static_cast<size_t>(43), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(60), vec_1.capacity());
  EXPECT_EQ(1, vec_1[0]);
  EXPECT_EQ(9, vec_1[1]);
  EXPECT_EQ(50, vec_1.back());
}

TEST(TestTVectorLib, ThrowWhenReplaceForNonExistentPosition) {
  TVector<int> vec_1(10);

  EXPECT_ANY_THROW(vec_1.replace(10, 100));
}

TEST(TestTVectorLib, ThrowWhenReplaceInEmptyVector) {
  TVector<int> vec_1;

  EXPECT_ANY_THROW(vec_1.replace(static_cast<size_t>(0), 100));
}

TEST(TestTVectorLib, Replace) {
  TVector<int> vec_1;
  for (size_t i = 0; i < 30; i++) {
    vec_1.insert(i, i + 1);
  }

  vec_1.replace(5, 999);
  vec_1.pop_front();
  vec_1.replace(10, 1000);

  EXPECT_EQ(static_cast<size_t>(29), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(999, vec_1[4]);
  EXPECT_EQ(1000, vec_1[10]);
}

TEST(TestTVectorLib, ThrowWhenEraseWithPointersOutOfRangeError) {
  TVector<int> vec_1(30);
  for (int i = 0; i < 30; i++) vec_1[i] = i;

  EXPECT_ANY_THROW({
    int* invalid_ptr = vec_1.begin() + 30;
    vec_1.erase(invalid_ptr, invalid_ptr + 1);
    });
}

TEST(TestTVectorLib, ThrowWhenEraseWithPointersInvalidRangeError) {
  TVector<int> vec(30);

  EXPECT_ANY_THROW({
    int* first = vec.begin() + 15;
    int* last = vec.begin() + 10;
    vec.erase(first, last);
    });
}

TEST(TestTVectorLib, ThrowWhenEraseWithPointersEmptyRange) {
  TVector<int> vec(30);

  EXPECT_ANY_THROW({
    int* p = vec.begin() + 10;
    vec.erase(p, p);
    });
}

TEST(TestTVectorLib, ReplaceWithPointers) {
  TVector<int> vec_1;
  for (size_t i = 0; i < 30; i++) {
    vec_1.insert(i, i + 1);
  }

  vec_1.replace(vec_1.begin() + 5, 42);
  vec_1.pop_front();
  vec_1.replace(vec_1.begin() + 10, 142);

  EXPECT_EQ(static_cast<size_t>(29), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(30), vec_1.capacity());
  EXPECT_EQ(42, vec_1[4]);
  EXPECT_EQ(142, vec_1[10]);
}

TEST(TestTVectorLib, ThrowWhenReplaceWithPointersNullptr) {
  TVector<int> vec(5);

  EXPECT_ANY_THROW(vec.replace(nullptr, 123));
}

TEST(TestTVectorLib, ThrowWhenReplaceWithPointersOutOfRangeLeft) {
  TVector<int> vec(5);

  EXPECT_ANY_THROW({
    int* invalid_pos = vec.begin() - 1;
    vec.replace(invalid_pos, 100);
    });
}

TEST(TestTVectorLib, ThrowWhenReplaceWithPointersOutOfRangeRight) {
  TVector<int> vec(10);

  EXPECT_ANY_THROW({
    int* invalid_pos = vec.begin() + 15;
    vec.replace(invalid_pos, 100);
    });
}

TEST(TestTVectorLib, Clear) {
  TVector<int> vec_1(100);
  vec_1.push_back(101);
  vec_1.erase(0, 9);
  vec_1.clear();

  EXPECT_EQ(static_cast<size_t>(0), vec_1.size());
  EXPECT_EQ(static_cast<size_t>(105), vec_1.capacity());
  EXPECT_TRUE(vec_1.is_empty());
}

TEST(TestTVectorLib, Reserve) {
  TVector<int> vec_1(10);

  vec_1.reserve(5);
  EXPECT_EQ(static_cast<size_t>(10), vec_1.capacity());

  vec_1.reserve(100);
  EXPECT_EQ(static_cast<size_t>(100), vec_1.capacity());
  EXPECT_EQ(static_cast<size_t>(10), vec_1.size());

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(0, vec_1[i]);
  }
}

TEST(TestTVectorLib, Resize) {
  TVector<int> vec(10);
  for (size_t i = 0; i < 10; ++i) {
    vec[i] = static_cast<int>(i);
  }

  vec.resize(5);
  EXPECT_EQ(static_cast<size_t>(5), vec.size());
  EXPECT_EQ(4, vec.back());

  vec.resize(8);
  EXPECT_EQ(static_cast<size_t>(8), vec.size());
  EXPECT_EQ(0, vec[6]);
  EXPECT_EQ(4, vec[4]);
}

TEST(TestTVectorLib, ResizeWithDeleted) {
  TVector<int> vec(30);
  for (size_t i = 0; i < 30; ++i) {
    vec[i] = static_cast<int>(i);
  }
  vec.erase(2, 3);

  vec.resize(10);
  EXPECT_EQ(static_cast<size_t>(10), vec.size());
  EXPECT_EQ(1, vec[1]);
  EXPECT_EQ(3, vec[2]);
  EXPECT_EQ(static_cast<size_t>(30), vec.capacity());

  vec.resize(16, 777);
  EXPECT_EQ(static_cast<size_t>(16), vec.size());
  EXPECT_EQ(3, vec[2]);
  EXPECT_EQ(777, vec[15]);
  EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}

TEST(TestTVectorLib, ResizeWithNonTrivialCases) {
  TVector<int> vec;

  vec.resize(0);
  EXPECT_EQ(static_cast<size_t>(0), vec.size());

  vec.resize(30);
  EXPECT_EQ(static_cast<size_t>(30), vec.size());
  EXPECT_EQ(0, vec[3]);

  for (size_t i = 0; i < 5; ++i) {
    vec[i] = static_cast<int>(i);
  }
  vec.erase(1, 4);
  vec.resize(0);
  EXPECT_EQ(static_cast<size_t>(0), vec.size());
  EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}

TEST(TestTVectorLib, ShrinkToFit) {
  TVector<int> vec(50);
  for (int i = 0; i < 50; ++i) {
    vec[i] = i;
  }

  vec.push_front(333);
  vec.erase(0, 5);
  vec.shrink_to_fit();

  EXPECT_EQ(static_cast<size_t>(46), vec.size());
  EXPECT_EQ(static_cast<size_t>(46), vec.capacity());

  TVector<int> empty_vec;
  empty_vec.shrink_to_fit();
  EXPECT_EQ(static_cast<size_t>(0), empty_vec.capacity());
}

TEST(TestTVectorLib, Assign) {
  TVector<int> vec;
  vec.assign(5, 42);

  EXPECT_EQ(static_cast<size_t>(5), vec.size());
  EXPECT_EQ(42, vec[0]);
  EXPECT_EQ(42, vec[4]);

  vec.assign(3, 10);
  EXPECT_EQ(static_cast<size_t>(3), vec.size());
  EXPECT_EQ(10, vec[2]);
}

TEST(TestTVectorLib, AssignWithDeleted) {
  TVector<int> vec(100);
  vec.erase(3, 7);
  vec.assign(8, 100);

  EXPECT_EQ(static_cast<size_t>(8), vec.size());
  EXPECT_EQ(100, vec[7]);
  EXPECT_EQ(static_cast<size_t>(100), vec.capacity());
}

TEST(TestTVectorLib, AssignEmpty) {
  TVector<std::string> vec(5);
  vec.assign(0, "test");

  EXPECT_EQ(static_cast<size_t>(0), vec.size());
  EXPECT_TRUE(vec.is_empty());
  EXPECT_EQ(static_cast<size_t>(5), vec.capacity());
}

TEST(TestTVectorLib, OperatorEquallyBasic) {
  TVector<int> v1(5);
  for (int i = 0; i < 5; i++) v1[i] = i + 1;

  TVector<int> v2;
  v2 = v1;

  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }
}

TEST(TestTVectorLib, OperatorEquallyWithDeleted) {
  TVector<int> v1(30);
  for (int i = 0; i < 30; i++) v1[i] = i;
  v1.erase(3, 7);

  TVector<int> v2;
  v2 = v1;

  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }
}

TEST(TestTVectorLib, OperatorStrictEqualNoEqual) {
  TVector<int> v1(20), v2(20);
  for (int i = 0; i < 20; ++i) {
    v1[i] = v2[i] = i + 1;
  }
  bool basic = (v1 == v2);

  v2.pop_back();
  bool diff_size = v1 != v2;

  TVector<int> v3(20);
  for (int i = 0; i < 20; i++) v3[i] = i + 1;
  v3.insert(2, 111);
  v3.erase(2);
  bool diff_states_and_capacity = v1 == v3;

  EXPECT_TRUE(basic);
  EXPECT_TRUE(diff_size);
  EXPECT_TRUE(diff_states_and_capacity);
}

TEST(TestTVectorLib, SwapBasic) {
  TVector<int> vec(3);
  vec[0] = 10; vec[1] = 20; vec[2] = 30;

  T_swap(vec[0], vec[2]);

  EXPECT_EQ(30, vec[0]);
  EXPECT_EQ(10, vec[2]);
  EXPECT_EQ(20, vec[1]);
}

TEST(TestTVectorLib, SwapSelf) {
  TVector<int> vec(1);
  vec[0] = 42;

  T_swap(vec[0], vec[0]);

  EXPECT_EQ(42, vec[0]);
  EXPECT_EQ(static_cast<size_t>(1), vec.size());
}

TEST(TestTVectorLib, ShuffleBasic) {
  TVector<int> vec_1(100);
  for (int i = 0; i < 100; ++i) {
    vec_1[i] = i;
  }

  TVector<int> vec_2(vec_1);
  shuffle(vec_1);

  EXPECT_EQ(vec_2.size(), vec_1.size());

  for (int val : vec_2) {
    bool found = false;
    for (size_t i = 0; i < vec_1.size(); i++) {
      if (vec_1[i] == val) {
        found = true;
        break;
      }
    }
    EXPECT_TRUE(found);
  }

  bool order_changed = false;
  for (size_t i = 0; i < vec_2.size(); i++) {
    if (vec_2[i] != vec_1[i]) {
      order_changed = true;
      break;
    }
  }
  EXPECT_TRUE(order_changed);
}

TEST(TestTVectorLib, ShuffleEmpty) {
  TVector<int> empty_vec;
  shuffle(empty_vec);
  EXPECT_EQ(static_cast<size_t>(0), empty_vec.size());
}

TEST(TestTVectorLib, ShuffleWithDeleted) {
  TVector<int> vec_1(30);
  for (int i = 0; i < 30; ++i) {
    vec_1[i] = i;
  }
  vec_1.erase(1);
  vec_1.erase(3);

  TVector<int> vec_2(vec_1);
  shuffle(vec_1);

  EXPECT_EQ(vec_2.size(), vec_1.size());

  bool order_changed = false;
  for (size_t i = 0; i < vec_2.size(); i++) {
    if (vec_2[i] != vec_1[i]) {
      order_changed = true;
      break;
    }
  }
  EXPECT_TRUE(order_changed);
}

TEST(TestTVectorLib, FindFirst) {
  int* ptr_null = nullptr;

  TVector<int> empty_vec;
  int* ptr_1 = find_first(empty_vec, 42);
  EXPECT_EQ(ptr_null, ptr_1);

  TVector<int> vec(30);
  for (int i = 0; i < 30; i++) vec[i] = i;
  int* ptr_2 = find_first(vec, 29);
  EXPECT_EQ(29, *ptr_2);

  vec.erase(3);
  int* ptr_3 = find_first(vec, 3);
  EXPECT_EQ(ptr_null, ptr_3);

  int* ptr_4 = find_first(vec, 99);
  EXPECT_EQ(ptr_null, ptr_4);

  vec.push_back(0);
  int* ptr_5 = find_first(vec, 0);
  EXPECT_EQ(&vec[0], ptr_5);
}

TEST(TestTVectorLib, FindLast) {
  int* ptr_null = nullptr;

  TVector<int> empty_vec;
  int* ptr_1 = find_last(empty_vec, 42);
  EXPECT_EQ(ptr_null, ptr_1);

  TVector<int> vec(30);
  for (int i = 0; i < 30; i++) vec[i] = i;
  int* ptr_2 = find_last(vec, 29);
  EXPECT_EQ(29, *ptr_2);

  vec.erase(3);
  int* ptr_3 = find_last(vec, 3);
  EXPECT_EQ(ptr_null, ptr_3);

  int* ptr_4 = find_last(vec, 99);
  EXPECT_EQ(ptr_null, ptr_4);

  vec.push_back(0);
  int* ptr_5 = find_last(vec, 0);
  EXPECT_EQ(&vec[29], ptr_5);
}

TEST(TestTVectorLib, Find) {
  TVector<int> empty_vec;
  TVector<int*> ptr_1 = find(empty_vec, 42);
  EXPECT_TRUE(ptr_1.is_empty());

  TVector<int> vec(30);
  for (int i = 0; i < 30; i++) vec[i] = i;
  for (int i = 20; i < 30; i++) vec[i] = 44;
  TVector<int*> ptr_2 = find(vec, 44);
  EXPECT_EQ(static_cast<size_t>(10), ptr_2.size());

  vec.erase(3);
  TVector<int*> ptr_3 = find(vec, 3);
  EXPECT_EQ(static_cast<size_t>(0), ptr_3.size());

  TVector<int*> ptr_4 = find(vec, 99);
  EXPECT_EQ(static_cast<size_t>(0), ptr_4.size());

  vec.push_back(0);
  TVector<int*> ptr_5 = find(vec, 0);
  EXPECT_EQ(&vec[0], ptr_5[0]);
  EXPECT_EQ(&vec[29], ptr_5[1]);
}

TEST(TestTVectorLib, Sort) {
  TVector<int> vec(1000000);
  for (size_t i = 0; i < 1000000; i++) vec[i] = i;

  shuffle(vec);
  vec.push_front(0);
  vec.erase(0);
  T_sort(vec);

  for (size_t i = 1; i < vec.size(); i++) {
    EXPECT_LE(vec[i - 1], vec[i]);
  }

  TVector<int> empty;
  T_sort(empty);
  EXPECT_TRUE(empty.is_empty());

  TVector<int> single = { 1 };
  T_sort(single);
  EXPECT_EQ(static_cast<size_t>(1), single.size());
  EXPECT_EQ(1, single.back());
}

TEST(TestTVectorLib, Reallocate) {
  TVector<int> vec(44);
  vec.push_back(1);

  size_t initial_capacity = vec.capacity();
  for (size_t i = 0; i < 15; i++) {
    vec.push_back(0 + i);
    EXPECT_EQ(initial_capacity, vec.capacity());
  }

  vec.push_back(3);
  EXPECT_EQ(initial_capacity + 15, vec.capacity());

  vec.erase(0, 4);
  for (size_t i = 0; i < 16; i++) {
    vec.push_back(3);
  }
  EXPECT_EQ(initial_capacity + 15, vec.capacity());
}

TEST(TestTVectorLib, ReallocateForDeleted) {
  TVector<int> vec(99);
  vec.push_back(1);
  size_t initial_capacity = vec.capacity();

  for (size_t i = 0; i < 14; i++) {
    vec.pop_back();
    EXPECT_EQ(initial_capacity, vec.capacity());
  }

  vec.pop_back();
  EXPECT_EQ(initial_capacity - 15, vec.capacity());
}

TEST(TestTVectorLib, HighDimensionalAndReallocateForDeleted) {
  TVector<int> vec(90000);
  vec.erase(0, 13500);
  EXPECT_EQ(static_cast<size_t>(76515), vec.capacity());
}
