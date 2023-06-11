/**
 * @file test.cpp
 * @author mavissig (tg: @senior_stepik | GitHub: https://github.com/mavissig)
 * @brief В этом файле выполнено тестирование функций библиотеки lib_matrix_cpp
 * @version 0.1
 * @date 2023-06-12
 * @copyright Copyright (c) 2023
 */
#include <gtest/gtest.h>

#include <iostream>

#include "../matrix_oop.h"

void completion(S21Matrix& matrix, double val) {
  int cols = matrix.GetCols();
  int rows = matrix.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix(i, j) = val;
    }
  }
}

void manualCompletion(S21Matrix& matrix) {
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;
}

void eqElemMatrix(S21Matrix& matrix1, double val) {
  int cols = matrix1.GetCols();
  int rows = matrix1.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(matrix1(i, j), val);
    }
  }
}

void outMatrix(S21Matrix& matrix) {
  std::cout << "[=====OUTMATRIX=====]:" << std::endl;
  int cols = matrix.GetCols();
  int rows = matrix.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << matrix(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "[=====END=====]" << std::endl;
}

/// Constructor tests

TEST(ParameterizedConstructor, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  EXPECT_EQ(TestMatrix1.GetCols(), 3);
  EXPECT_EQ(TestMatrix1.GetRows(), 3);
}

TEST(CopyConstructor, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  completion(TestMatrix1, 3);
  S21Matrix TestMatrix2(TestMatrix1);
  bool res = TestMatrix1 == TestMatrix2;
  EXPECT_EQ(res, true);
}

TEST(TransferConstructor, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  completion(TestMatrix1, 3);

  S21Matrix TestMatrix2{std::move(TestMatrix1)};

  eqElemMatrix(TestMatrix2, 3);
  EXPECT_EQ(TestMatrix1.GetRows(), 0);
  EXPECT_EQ(TestMatrix1.GetCols(), 0);
}

TEST(TransferConstructor, Test_2) {
  S21Matrix TestMatrix1{};

  S21Matrix TestMatrix2{std::move(TestMatrix1)};

  EXPECT_EQ(TestMatrix2.GetRows(), 0);
  EXPECT_EQ(TestMatrix2.GetCols(), 0);
  EXPECT_EQ(TestMatrix1.GetRows(), 0);
  EXPECT_EQ(TestMatrix1.GetCols(), 0);
}

/// Operator tests

TEST(operatorSum, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  S21Matrix result1{3, 3};
  result1 = TestMatrix1 + TestMatrix2;
  eqElemMatrix(result1, 6);
}

TEST(operatorSum, Test_2) {
  S21Matrix TestMatrix1{2, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  ASSERT_ANY_THROW(TestMatrix1 + TestMatrix2);
}

TEST(operatorSub, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  S21Matrix result1{3, 3};
  result1 = TestMatrix1 - TestMatrix2;
  eqElemMatrix(result1, 0);
}

TEST(operatorSub, Test_2) {
  S21Matrix TestMatrix1{5, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  ASSERT_ANY_THROW(TestMatrix1 - TestMatrix2);
}

TEST(operatorMulMatrix, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  S21Matrix result1{3, 3};
  result1 = TestMatrix1 * TestMatrix2;
  eqElemMatrix(result1, 27);
}

TEST(operatorMulMatrix, Test_2) {
  S21Matrix TestMatrix1{3, 10};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  ASSERT_ANY_THROW(TestMatrix1 * TestMatrix2);
}

TEST(operatorMulNum, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  completion(TestMatrix1, 3);
  S21Matrix result1{3, 3};
  result1 = TestMatrix1 * 3;
  eqElemMatrix(result1, 9);
}

TEST(operatorEqEq, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  bool res = TestMatrix1 == TestMatrix2;
  EXPECT_EQ(res, true);
}

TEST(operatorEqEq, Test_2) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 4);
  completion(TestMatrix2, 3);
  bool res = TestMatrix1 == TestMatrix2;
  EXPECT_EQ(res, false);
}

TEST(operatorEqEq, Test_3) {
  S21Matrix TestMatrix1{10, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  ASSERT_ANY_THROW(TestMatrix1 == TestMatrix2);
}

TEST(operatorEq, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{};
  completion(TestMatrix1, 3);
  TestMatrix2 = TestMatrix1;
  bool res = TestMatrix1 == TestMatrix2;
  EXPECT_EQ(res, true);
}

TEST(operatorEq, Test_2) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{2, 2};
  completion(TestMatrix1, 3);
  TestMatrix2 = TestMatrix1;
  bool res = TestMatrix1 == TestMatrix2;
  EXPECT_EQ(res, true);
}

TEST(operatorTransfer, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{};
  completion(TestMatrix1, 3);

  TestMatrix2 = std::move(TestMatrix1);

  EXPECT_EQ(TestMatrix2.GetCols(), 3);
  EXPECT_EQ(TestMatrix2.GetRows(), 3);
  eqElemMatrix(TestMatrix2, 3);
  EXPECT_EQ(TestMatrix1.GetCols(), 0);
  EXPECT_EQ(TestMatrix1.GetRows(), 0);
}

/// Func tests

TEST(EqMatrix, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  EXPECT_EQ(TestMatrix1.EqMatrix(TestMatrix2), true);
}

TEST(EqMatrix, Test_2) {
  S21Matrix TestMatrix1{100, 50};
  S21Matrix TestMatrix2{100, 50};
  completion(TestMatrix1, 357.678);
  completion(TestMatrix2, 357.678);
  EXPECT_EQ(TestMatrix1.EqMatrix(TestMatrix2), true);
}

TEST(EqMatrix, Test_3) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 2);
  EXPECT_EQ(TestMatrix1.EqMatrix(TestMatrix2), false);
}

TEST(EqMatrix, Test_4) {
  S21Matrix TestMatrix1{100, 50};
  S21Matrix TestMatrix2{100, 50};
  completion(TestMatrix1, 357.678);
  completion(TestMatrix2, 357.67889);
  EXPECT_EQ(TestMatrix1.EqMatrix(TestMatrix2), false);
}

TEST(EqMatrix, Test_5) {
  S21Matrix TestMatrix1{4, 4};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  ASSERT_ANY_THROW(TestMatrix1.EqMatrix(TestMatrix2));
}

TEST(SumMatrix, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  TestMatrix1.SumMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, 6);
}

TEST(SumMatrix, Test_2) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3.5000);
  completion(TestMatrix2, 3.5000);
  TestMatrix1.SumMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, 7);
}

TEST(SumMatrix, Test_3) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 0);
  completion(TestMatrix2, 3.5000);
  TestMatrix1.SumMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, 3.5);
}

TEST(SumMatrix, Test_4) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{2, 2};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  ASSERT_ANY_THROW(TestMatrix1.SumMatrix(TestMatrix2));
}

TEST(SubMatrix, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  TestMatrix1.SubMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, 0);
}

TEST(SubMatrix, Test_2) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 4);
  TestMatrix1.SubMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, -1);
}

TEST(SubMatrix, Test_3) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3.5);
  completion(TestMatrix2, 4);
  TestMatrix1.SubMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, -0.5);
}

TEST(SubMatrix, Test_4) {
  S21Matrix TestMatrix1{1, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3.5);
  completion(TestMatrix2, 4);
  ASSERT_ANY_THROW(TestMatrix1.SubMatrix(TestMatrix2));
}

TEST(MulNumber, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  completion(TestMatrix1, 3);
  TestMatrix1.MulNumber(2);
  eqElemMatrix(TestMatrix1, 6);
}

TEST(MulNumber, Test_2) {
  S21Matrix TestMatrix1{3, 3};
  completion(TestMatrix1, 3);
  TestMatrix1.MulNumber(-1);
  eqElemMatrix(TestMatrix1, -3);
}

TEST(MulNumber, Test_3) {
  S21Matrix TestMatrix1{3, 3};
  completion(TestMatrix1, 2.5);
  TestMatrix1.MulNumber(-1.5);
  eqElemMatrix(TestMatrix1, -3.75);
}

TEST(MulNumber, Test_4) {
  S21Matrix TestMatrix1{2, 3};
  completion(TestMatrix1, 3);
  TestMatrix1.MulNumber(-1);
  eqElemMatrix(TestMatrix1, -3);
}

TEST(MulMatrix, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  S21Matrix TestMatrix2{3, 3};
  completion(TestMatrix1, 3);
  completion(TestMatrix2, 3);
  TestMatrix1.MulMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, 27);
}

TEST(MulMatrix, Test_2) {
  S21Matrix TestMatrix1{2, 4};
  S21Matrix TestMatrix2{4, 2};
  completion(TestMatrix1, 2);
  completion(TestMatrix2, 2);
  TestMatrix1.MulMatrix(TestMatrix2);
  eqElemMatrix(TestMatrix1, 16);
}

TEST(MulMatrix, Test_3) {
  S21Matrix TestMatrix1{6, 6};
  S21Matrix TestMatrix2{4, 2};
  completion(TestMatrix1, 2);
  completion(TestMatrix2, 2);
  ASSERT_ANY_THROW(TestMatrix1.MulMatrix(TestMatrix2));
}

TEST(Transpose, Test_1) {
  S21Matrix TestMatrix1{0, 5};
  completion(TestMatrix1, 3);
  S21Matrix transposeMatrix = TestMatrix1.Transpose();
  eqElemMatrix(transposeMatrix, 3);
}

TEST(Transpose, Test_2) {
  S21Matrix TestMatrix1{25, 44};
  completion(TestMatrix1, 3);
  S21Matrix transposeMatrix = TestMatrix1.Transpose();
  eqElemMatrix(transposeMatrix, 3);
}

TEST(Transpose, Test_3) {
  S21Matrix TestMatrix1{5, 5};
  completion(TestMatrix1, 3.99999);
  S21Matrix transposeMatrix = TestMatrix1.Transpose();
  eqElemMatrix(transposeMatrix, 3.99999);
}

TEST(Transpose, Test_4) {
  S21Matrix TestMatrix1{5, 5};
  completion(TestMatrix1, -3.99999);
  S21Matrix transposeMatrix = TestMatrix1.Transpose();
  eqElemMatrix(transposeMatrix, -3.99999);
}

TEST(Determinant, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  manualCompletion(TestMatrix1);
  EXPECT_EQ(TestMatrix1.Determinant(), -40);
}

TEST(Determinant, Test_2) {
  S21Matrix TestMatrix1{4, 3};
  ASSERT_ANY_THROW(TestMatrix1.Determinant());
}

TEST(CalcComplements, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  manualCompletion(TestMatrix1);

  S21Matrix TestMatrix2{3, 3};
  TestMatrix2(0, 0) = 0;
  TestMatrix2(0, 1) = 10;
  TestMatrix2(0, 2) = -20;
  TestMatrix2(1, 0) = 4;
  TestMatrix2(1, 1) = -14;
  TestMatrix2(1, 2) = 8;
  TestMatrix2(2, 0) = -8;
  TestMatrix2(2, 1) = -2;
  TestMatrix2(2, 2) = 4;

  S21Matrix complementsMatrix{};
  complementsMatrix = TestMatrix1.CalcComplements();

  EXPECT_EQ(complementsMatrix == TestMatrix2, true);
}

TEST(CalcComplements, Test_2) {
  S21Matrix TestMatrix1{5, 3};
  manualCompletion(TestMatrix1);
  ASSERT_ANY_THROW(TestMatrix1.CalcComplements());
}

TEST(InverseMatrix, Test_1) {
  S21Matrix TestMatrix1{3, 3};
  TestMatrix1(0, 0) = 2;
  TestMatrix1(0, 1) = 5;
  TestMatrix1(0, 2) = 7;
  TestMatrix1(1, 0) = 6;
  TestMatrix1(1, 1) = 3;
  TestMatrix1(1, 2) = 4;
  TestMatrix1(2, 0) = 5;
  TestMatrix1(2, 1) = -2;
  TestMatrix1(2, 2) = -3;

  S21Matrix TestMatrix2{3, 3};
  TestMatrix2(0, 0) = 1;
  TestMatrix2(0, 1) = -1;
  TestMatrix2(0, 2) = 1;
  TestMatrix2(1, 0) = -38;
  TestMatrix2(1, 1) = 41;
  TestMatrix2(1, 2) = -34;
  TestMatrix2(2, 0) = 27;
  TestMatrix2(2, 1) = -29;
  TestMatrix2(2, 2) = 24;

  S21Matrix invMatrix{};
  invMatrix = TestMatrix1.InverseMatrix();

  EXPECT_EQ(invMatrix == TestMatrix2, true);
}

TEST(InverseMatrix, Test_2) {
  S21Matrix TestMatrix1{3, 3};
  completion(TestMatrix1, 1);
  ASSERT_ANY_THROW(TestMatrix1.InverseMatrix());
}