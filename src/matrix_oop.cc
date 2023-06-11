/**
 * @brief В этом файле описаны функции библиотеки lib_matrix_cpp
 */
#include "matrix_oop.h"

MatrixPlus::MatrixPlus() {
  rows_ = 0;
  cols_ = 0;
  matrix = nullptr;
}

MatrixPlus::MatrixPlus(int rows, int cols) : rows_(rows), cols_(cols) {
  try {
    if (0 == rows && 0 == cols) {
      throw std::bad_array_new_length();
    }
    matrix = new double*[this->rows_]();
    for (auto i = 0; i < rows_; ++i) {
      this->matrix[i] = new double[cols_]();
    }
  } catch (...) {
    Clear();
  }
}

MatrixPlus::MatrixPlus(const MatrixPlus& other)
    : MatrixPlus(other.rows_, other.cols_) {
  if (nullptr != this->matrix && nullptr != other.matrix) {
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix[i][j] = other.matrix[i][j];
      }
    }
  }
}

MatrixPlus::MatrixPlus(MatrixPlus&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix(std::move(other.matrix)) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix = nullptr;
}

void MatrixPlus::Clear() {
  if (nullptr != this->matrix) {
    for (int i = 0; i < this->rows_; i++) {
      if (nullptr == this->matrix[i]) {
        break;
      }
      delete[] this->matrix[i];
      this->matrix[i] = nullptr;
    }
    delete[] this->matrix;
    this->rows_ = 0;
    this->cols_ = 0;
    this->matrix = nullptr;
  }
}

MatrixPlus MatrixPlus::GetMinor(const int rows, const int columns) {
  MatrixPlus result(this->rows_ - 1, this->cols_ - 1);
  int minor_i = 0;
  for (int i = 0; i < this->rows_; i++) {
    int minor_j = 0;
    if (rows != i) {
      for (int j = 0; j < this->cols_; j++) {
        if (columns != j) {
          result.matrix[minor_i][minor_j++] = this->matrix[i][j];
        }
      }
      minor_i++;
    }
  }
  return result;
}

void MatrixPlus::Resize(const int rows, const int cols) {
  MatrixPlus result(rows, cols);
  if (nullptr != result.matrix) {
    int currentRows = (rows < this->rows_) ? rows : this->rows_;
    int currentCols = (cols < this->cols_) ? cols : this->cols_;
    if (nullptr != this->matrix) {
      for (int i = 0; i < currentRows; i++) {
        for (int j = 0; j < currentCols; j++) {
          result.matrix[i][j] = this->matrix[i][j];
        }
      }
    }
    *this = std::move(result);
  }
}

bool MatrixPlus::EqMatrix(const MatrixPlus& other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  bool status = true;
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      if (this->matrix[i][j] != other.matrix[i][j]) {
        status = false;
        break;
      }
    }
  }
  return status;
}

void MatrixPlus::SumMatrix(const MatrixPlus& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      this->matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
    }
  }
}

void MatrixPlus::SubMatrix(const MatrixPlus& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      this->matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
    }
  }
}

void MatrixPlus::MulNumber(const double num) {
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      this->matrix[i][j] = this->matrix[i][j] * num;
    }
  }
}

void MatrixPlus::MulMatrix(const MatrixPlus& other) {
  if (this->cols_ != other.rows_) {
    throw std::out_of_range(
        "Incorrect input, the number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix");
  }
  MatrixPlus tmp(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        tmp.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
      }
    }
  }
  *this = std::move(tmp);
}

MatrixPlus MatrixPlus::Transpose() {
  MatrixPlus tmp(this->cols_, this->rows_);
  for (int i = 0; i < this->cols_; i++) {
    for (int j = 0; j < this->rows_; j++) {
      tmp.matrix[i][j] = this->matrix[j][i];
    }
  }
  return tmp;
}

MatrixPlus MatrixPlus::CalcComplements() {
  if (this->cols_ != this->rows_) {
    throw std::out_of_range("Incorrect input, the matrix is not square");
  }
  MatrixPlus result(this->rows_, this->cols_);
  if (1 != this->rows_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        double determinant = 0;
        MatrixPlus minor = this->GetMinor(i, j);
        determinant = minor.Determinant();
        result.matrix[i][j] = determinant * pow(-1, i + j);
      }
    }
  } else {
    result.matrix[0][0] = 1.0;
  }
  return result;
}

double MatrixPlus::Determinant() {
  if (this->cols_ != this->rows_) {
    throw std::out_of_range("Incorrect input, the matrix is not square");
  }
  double result = 0;
  double det = 0;
  if (2 < this->rows_) {
    MatrixPlus minor(this->rows_ - 1, this->cols_ - 1);
    for (int i = 0; i < this->cols_; i++) {
      minor = this->GetMinor(0, i);
      det = minor.Determinant();
      result += this->matrix[0][i] * pow(-1, i) * det;
    }
  } else if (2 == this->rows_) {
    result = this->matrix[0][0] * this->matrix[1][1] -
             this->matrix[0][1] * this->matrix[1][0];
  } else if (1 == this->rows_) {
    result = this->matrix[0][0];
  }
  return result;
}

MatrixPlus MatrixPlus::InverseMatrix() {
  double determinant = 0.0;
  MatrixPlus result;
  MatrixPlus adjoint = this->CalcComplements();
  determinant = this->Determinant();
  if (0 != determinant) {
    const double inv_determinant = 1.0 / determinant;
    adjoint.MulNumber(inv_determinant);
    result = adjoint.Transpose();
  } else {
    throw std::out_of_range("Incorrect input, the matrix is not square");
  }
  return result;
}

int MatrixPlus::GetCols() { return this->cols_; }

int MatrixPlus::GetRows() { return this->rows_; }

void MatrixPlus::SetCols(const int& cols) { Resize(this->rows_, cols); }

void MatrixPlus::SetRows(const int& rows) { Resize(rows, this->cols_); }

MatrixPlus MatrixPlus::operator+(const MatrixPlus& other) const {
  MatrixPlus result(*this);
  result.SumMatrix(other);
  return result;
}

MatrixPlus MatrixPlus::operator-(const MatrixPlus& other) const {
  MatrixPlus result(*this);
  result.SubMatrix(other);
  return result;
}

MatrixPlus MatrixPlus::operator*(const MatrixPlus& other) const {
  MatrixPlus result(*this);
  result.MulMatrix(other);
  return result;
}

MatrixPlus MatrixPlus::operator*(const double num) const {
  MatrixPlus result(*this);
  result.MulNumber(num);
  return result;
}

bool MatrixPlus::operator==(const MatrixPlus& other) const {
  return this->EqMatrix(other);
}

MatrixPlus& MatrixPlus::operator=(const MatrixPlus& other) {
  if (this != &other) {
    Resize(other.rows_, other.cols_);
    if (nullptr != other.matrix && this->rows_ == other.rows_ &&
        this->cols_ == other.cols_) {
      for (int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->cols_; j++) {
          this->matrix[i][j] = other.matrix[i][j];
        }
      }
    }
  }
  return *this;
}

MatrixPlus& MatrixPlus::operator=(MatrixPlus&& other) {
  if (this != &other) {
    Clear();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix = other.matrix;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix = nullptr;
  }
  return *this;
}

MatrixPlus& MatrixPlus::operator+=(const MatrixPlus& other) {
  this->SumMatrix(other);
  return *this;
}

MatrixPlus& MatrixPlus::operator-=(const MatrixPlus& other) {
  this->SubMatrix(other);
  return *this;
}

MatrixPlus& MatrixPlus::operator*=(const MatrixPlus& other) {
  this->MulMatrix(other);
  return *this;
}

MatrixPlus& MatrixPlus::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double& MatrixPlus::operator()(int rows, int cols) {
  if (rows < 0 || cols < 0 || cols >= this->cols_ || rows >= this->rows_) {
    throw std::out_of_range("out of range");
  }
  return this->matrix[rows][cols];
}

const double& MatrixPlus::operator()(int rows, int cols) const {
  if (rows < 0 || cols < 0 || cols >= this->cols_ || rows >= this->rows_) {
    throw std::out_of_range("out of range");
  }
  return this->matrix[rows][cols];
}

MatrixPlus::~MatrixPlus() { Clear(); }