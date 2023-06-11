/**
 * @brief Содержит объявление класса MatrixPlus
 * @details
 * @author mavissig
 */
#ifndef LIB_MATRIX_CPP_MATRIX_OOP_H
#define LIB_MATRIX_CPP_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class MatrixPlus {
 public:
  /**
   * @brief Базовый конструктор, инициализирующий матрицу некоторой заранее
   * заданной размерностью
   */
  MatrixPlus();

  /**
   * @brief Параметризированный конструктор с количеством строк и столбцов
   * @param rows
   * @param cols
   */
  MatrixPlus(int rows, int cols);

  /**
   * @brief Конструктор копирования
   * @param other
   */
  MatrixPlus(const MatrixPlus& other);

  /**
   * @brief Конструктор переноса
   * @param other
   */
  MatrixPlus(MatrixPlus&& other) noexcept;

  /**
   * @brief Деструктор класса MatrixPlus
   */
  ~MatrixPlus();

  /// Operator overloading

  /**
   * @brief Сложение двух матриц
   * @param other
   * @return MatrixPlus
   * @throw @ различная размерность матриц
   */
  MatrixPlus operator+(const MatrixPlus& other) const;

  /**
   * @brief Вычитание одной матрицы из другой
   * @param other
   * @return MatrixPlus
   * @throw @ различная размерность матриц
   */
  MatrixPlus operator-(const MatrixPlus& other) const;

  /**
   * @brief Умножение матриц
   * @param other
   * @return MatrixPlus
   * @throw @ число столбцов первой матрицы не равно числу строк второй матрицы
   */
  MatrixPlus operator*(const MatrixPlus& other) const;

  /**
   * @brief умножение матрицы на число
   * @param num
   * @return MatrixPlus
   */
  MatrixPlus operator*(const double num) const;

  /**
   * @brief Проверка на равенство матриц (EqMatrix)
   * @param other
   * @return bool
   */
  bool operator==(const MatrixPlus& other) const;

  /**
   * @brief Присвоение матрице значений другой матрицы
   * @param other
   * @return MatrixPlus&
   */
  MatrixPlus& operator=(const MatrixPlus& other);

  /**
   * @brief Оператор перемещения
   * @param other
   * @return MatrixPlus&
   */
  MatrixPlus& operator=(MatrixPlus&& other);

  /**
   * @brief Присвоение сложения (SumMatrix)
   * @param other
   * @return MatrixPlus&
   * @throw @ различная размерность матриц
   */
  MatrixPlus& operator+=(const MatrixPlus& other);

  /**
   * @brief Присвоение разности (SubMatrix)
   * @param other
   * @return MatrixPlus&
   * @throw @ различная размерность матриц
   */
  MatrixPlus& operator-=(const MatrixPlus& other);

  /**
   * @brief Присвоение умножения (MulMatrix)
   * @param other
   * @return
   * @throw число столбцов первой матрицы не равно числу строк второй матрицы
   */
  MatrixPlus& operator*=(const MatrixPlus& other);

  /**
   * @brief Присвоение умножения (MulNumber)
   * @param other
   * @return MatrixPlus&
   * @throw число столбцов первой матрицы не равно числу строк второй матрицы
   */
  MatrixPlus& operator*=(const double num);

  /**
   * @brief Индексация по элементам матрицы (строка, колонка)
   * @throw индекс за пределами матрицы
   */
  double& operator()(int rows, int cols);

  /**
   * @brief Индексация по элементам матрицы (строка, колонка)
   * @throw индекс за пределами матрицы
   */
  const double& operator()(int rows, int cols) const;

  /// Library functions

  /**
   * @brief Проверяет матрицы на равенство между собой
   * @param other
   * @return bool
   */
  bool EqMatrix(const MatrixPlus& other) const;

  /**
   * @brief Прибавляет вторую матрицу к текущей
   * @param other
   * @throw @ различная размерность матриц
   */
  void SumMatrix(const MatrixPlus& other);

  /**
   * @brief Вычитает из текущей матрицы другую
   * @param other
   * @throw @ различная размерность матриц
   */
  void SubMatrix(const MatrixPlus& other);

  /**
   * @brief Умножает текущую матрицу на число
   * @param num
   */
  void MulNumber(const double num);

  /**
   * @brief Умножает текущую матрицу на вторую
   * @param other
   * @throw @ число столбцов первой матрицы не равно числу строк второй матрицы
   */
  void MulMatrix(const MatrixPlus& other);

  /**
   * @brief Создает новую транспонированную матрицу из текущей и возвращает ее
   * @return MatrixPlus
   */
  MatrixPlus Transpose();

  /**
   * @brief Вычисляет матрицу алгебраических дополнений текущей матрицы и
   * возвращает ее
   * @return MatrixPlus
   * @throw @ матрица не является квадратной
   */
  MatrixPlus CalcComplements();

  /**
   * @brief Вычисляет и возвращает определитель текущей матрицы
   * @return double
   * @throw @ матрица не является квадратной
   */
  double Determinant();

  /**
   * @brief Вычисляет и возвращает обратную матрицу
   * @return MatrixPlus
   * @throw @ определитель матрицы равен 0
   */
  MatrixPlus InverseMatrix();

  /**
   * @brief Получение cols текущего объекта
   * @return int
   */
  int GetCols();

  /**
   * @brief Получение rows текущего объекта
   * @return int
   */
  int GetRows();

  /**
   * @brief Изменение cols текущего объекта
   */
  void SetCols(const int& cols);

  /**
   * @brief Изменение rows текущего объекта
   */
  void SetRows(const int& rows);

 private:
  int rows_;
  int cols_;
  double** matrix;

  void Clear();
  void Resize(const int rows, const int cols);
  MatrixPlus GetMinor(const int rows, const int columns);
};

#endif  // LIB_MATRIX_CPP_MATRIX_OOP_H
