#include "../headers/s21_matrix_oop.h"

// библиотека функций

// сравнение даблов
bool S21Matrix::AreDoublesTheSame(double a, double b) const {
  bool r = 0;

  // Число ли это?
  if (std::isfinite(a) && std::isfinite(b)) {
    r = fabs(a - b) < 1e-7;
    return r;
  } else {
    // Если нет, то что?
    if (std::isinf(a) && std::isinf(b)) {
      if (a > DBL_MAX && b > DBL_MAX) {
        r = 1;
      } else {
        if (a < -DBL_MAX && b < -DBL_MAX) {
          r = 1;
        }
      }
    }
    if (std::isnan(a) && std::isnan(b)) {
      r = 1;
    }
  }
  return r;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool are_equal = (cols_ == other.cols_) && (rows_ == other.rows_);
  for (size_t row = 0; row != rows_ && are_equal; row++) {
    for (size_t column = 0; column != cols_ && are_equal; column++) {
      double x = matrix_[row][column];
      double y = other.matrix_[row][column];
      are_equal = are_equal && AreDoublesTheSame(x, y);
    }
  }
  return are_equal;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  DataChecker(SumMatrixID, other);
  for (size_t row = 0; row != rows_; row++) {
    for (size_t column = 0; column != cols_; column++) {
      double summ = (matrix_[row][column] + other.matrix_[row][column]);
      matrix_[row][column] = summ;
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  DataChecker(SubMatrixID, other);
  for (size_t row = 0; row != rows_; row++) {
    for (size_t column = 0; column != cols_; column++) {
      double difference = (matrix_[row][column] - other.matrix_[row][column]);
      matrix_[row][column] = difference;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  DataChecker(MulMatrixID, other);
  S21Matrix Result(rows_, other.cols_);
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < other.cols_; j++) {
      Result.matrix_[i][j] = 0;
      for (size_t k = 0; k < other.rows_; k++) {
        Result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  delete[] matrix_;
  Copier(*this, Result);
}

void S21Matrix::MulNumber(const double num) {
  DataChecker(MulNumberID);
  for (size_t row = 0; row != rows_; row++) {
    for (size_t column = 0; column != cols_; column++) {
      matrix_[row][column] = matrix_[row][column] * num;
    }
  }
}

void S21Matrix::MinorCreator(S21Matrix &X, S21Matrix &MinorOfTheX,
                             size_t exclude_row, size_t exclude_column) {
  for (size_t i = 0, minor_i = 0; i < X.rows_; i++, minor_i++) {
    for (size_t j = 0, minor_j = 0; j < X.cols_; j++, minor_j++) {
      if (i == exclude_row) {
        i++;
      }
      if (j == exclude_column) {
        j++;
      }
      // Проверка на выход за пределы размерности матрицы и копирование в
      // результат.
      if (j < X.cols_ && i < X.rows_) {
        MinorOfTheX(minor_i, minor_j) = X(i, j);
      }
    }
  }
}

double S21Matrix::Determinant() {
  DataChecker(DeterminantID);
  // рекурсивно определяем детерминант, редуцируя исходную матрицу через
  // миноризацию до матрицы 2х2, параллельно накапливая результат-детерминант.
  double determinant = 0;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    // Формула: A[1,1]*(-1)^(1+1)*D|minor|+ ...
    for (size_t i = 0; i != cols_; i++) {
      // раскладываем детерминант по первой строке
      double t = 0;
      t = matrix_[0][i];
      t *= pow((-1), (1 + (i + 1)));
      // создаем минор по первой строке
      S21Matrix Minor(rows_ - 1, cols_ - 1);
      MinorCreator(*this, Minor, 0, i);
      double Dt = 0;
      Dt = Minor.Determinant();
      t *= Dt;
      determinant += t;
    }
  }
  return determinant;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix Transposed(cols_, rows_);
  for (size_t i = 0; i != rows_; i++) {
    for (size_t j = 0; j != cols_; j++) {
      Transposed(j, i) = matrix_[i][j];
    }
  }
  return Transposed;
}

void S21Matrix::MinorMatrixCreator(S21Matrix &A, S21Matrix &Result) {
  // Создаем миноры, вычисляем из них детерминанты и кладем значение в новую
  // матрицу.
  for (size_t i = 0; i != A.rows_; i++) {
    for (size_t j = 0; j != A.cols_; j++) {
      S21Matrix T(A.rows_ - 1, A.cols_ - 1);
      MinorCreator(A, T, i, j);
      double d;
      d = T.Determinant();
      Result(i, j) = d;
    }
  }
}

S21Matrix S21Matrix::CalcComplements() {
  DataChecker(CalcComplementsID);
  // Создаем матрицу миноров, после умножаем каждый элемент на -1 в нужной
  // степени.
  S21Matrix Result(rows_, cols_);
  MinorMatrixCreator(*this, Result);
  for (size_t i = 0; i != rows_; i++) {
    for (size_t j = 0; j != cols_; j++) {
      Result(i, j) = pow(-1, i + 1 + j + 1) * Result(i, j);
    }
  }
  return Result;
}

S21Matrix S21Matrix::InverseMatrix() {
  DataChecker(InverseMatrixID);
  // Формула: A^(-1) =  1/|A| * M^T.
  S21Matrix R(*this);
  double determinant = Determinant();
  if (cols_ == 1 && rows_ == 1) {
    // Если матрица единичная
    R(0, 0) = 1 / matrix_[0][0];
  } else {
    S21Matrix ComplementMatrix = CalcComplements();
    S21Matrix TransposeComplement = ComplementMatrix.Transpose();
    double one_divide_det = (1.0 / determinant);
    TransposeComplement.MulNumber(one_divide_det);
    R = TransposeComplement;
  }
  return R;
}
