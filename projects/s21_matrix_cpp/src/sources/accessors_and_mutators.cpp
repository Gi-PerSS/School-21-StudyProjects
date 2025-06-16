#include "../headers/s21_matrix_oop.h"
// Аккцессоры
size_t S21Matrix::GetRowsNumber() { return rows_; }
size_t S21Matrix::GetColumnsNumber() { return cols_; }

// Мутатор
void S21Matrix::SetNewMatrixSize(size_t new_rows_number,
                                 size_t new_columns_number) {
  if (rows_ == new_rows_number && cols_ == new_columns_number) {
    return;
  }

  S21Matrix NewSizeMatrix(new_rows_number, new_columns_number);
  size_t rows_upper_limit = (new_rows_number > rows_) ? rows_ : new_rows_number;
  size_t cols_upper_limit =
      (new_columns_number > cols_) ? cols_ : new_columns_number;

  for (size_t i = 0; i != rows_upper_limit; i++) {
    for (size_t j = 0; j != cols_upper_limit; j++) {
      NewSizeMatrix(i, j) = matrix_[i][j];
    }
  }
  delete[] matrix_;
  Copier(*this, NewSizeMatrix);
}