#include "../headers/s21_matrix_oop.h"

// перегружаем операторы

S21Matrix &S21Matrix::operator=(const S21Matrix &original) {
  if (&original != this) {
    delete[] matrix_;
    Copier(*this, original);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(const std::string file_path) {
  // перегрузка присваивания матрице содержимого файла с матрицей.
  delete[] matrix_;
  Copier(*this, MatrixFromFile(file_path));
  return *this;
}

S21Matrix S21Matrix::operator+(S21Matrix &RightHandSide) {
  S21Matrix R(*this);
  R.SumMatrix(RightHandSide);
  return R;
}

S21Matrix S21Matrix::operator+=(S21Matrix &RightHandSide) {
  SumMatrix(RightHandSide);
  return *this;
}

S21Matrix S21Matrix::operator-(S21Matrix &RightHandSide) {
  S21Matrix Difference(*this);
  Difference.SubMatrix(RightHandSide);
  return Difference;
}

S21Matrix S21Matrix::operator-=(S21Matrix &RightHandSide) {
  SubMatrix(RightHandSide);
  return *this;
}

S21Matrix S21Matrix::operator*(S21Matrix &RightHandSide) {
  S21Matrix Product(*this);
  Product.MulMatrix(RightHandSide);
  return Product;
}

S21Matrix S21Matrix::operator*=(S21Matrix &RightHandSide) {
  MulMatrix(RightHandSide);
  return *this;
}

S21Matrix S21Matrix::operator*(const double y) {
  S21Matrix Product(*this);
  Product.MulNumber(y);
  return Product;
}

bool S21Matrix::operator==(S21Matrix &RightHandSide) {
  return EqMatrix(RightHandSide);
}

double &S21Matrix::operator()(size_t rows, size_t cols) {
  DataChecker(IndexationID, rows, cols);
  return matrix_[rows][cols];
}

double &S21Matrix::operator()(size_t rows, size_t cols) const {
  DataChecker(IndexationID, rows, cols);
  return matrix_[rows][cols];
}