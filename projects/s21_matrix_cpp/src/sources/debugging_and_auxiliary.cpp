#include "../headers/s21_matrix_oop.h"

// отладочно-вспомогательное

// чтение матрицы из файла
S21Matrix S21Matrix::MatrixFromFile(const std::string file_path) {
  /*
  Формат файла матриц следующий:
  - первая строка содержит количество рядов и колонок разделенных любым
  символом, например: "9x9"
  - следующие строки содержат значения данных в виде рядов, разделенных
  переводом строки
  */
  DataChecker(file_path);
  std::ifstream TxtMatrix;
  TxtMatrix.open(file_path);
  size_t rows = -1;
  size_t cols = -1;
  char trash_buffer;
  TxtMatrix >> rows >> trash_buffer >> cols;
  S21Matrix R(rows, cols);
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      double t = 0;
      TxtMatrix >> t;
      R(i, j) = t;
    }
  }
  TxtMatrix.close();
  return R;
}

void DBG_MatrixSetConstant(double constant_value_for_all_cells,
                           S21Matrix &Matrix) {
  size_t y, x;
  x = Matrix.GetColumnsNumber();
  y = Matrix.GetRowsNumber();
  if (Matrix.matrix_ != nullptr) {
    for (size_t i = 0; i < y; i++) {
      for (size_t j = 0; j < x; j++) {
        Matrix(i, j) = constant_value_for_all_cells;
      }
    }
  }
}

void DBG_matrix_printer(S21Matrix &M, const char *debug_message) {
  size_t y, x;
  x = M.GetColumnsNumber();
  y = M.GetRowsNumber();
  printf("\n%s\n", debug_message);
  printf("columns: %ld, rows: %ld\n", y, x);

  if (M.matrix_ != nullptr) {
    for (size_t i = 0; i < y; i++) {
      printf("|");
      for (size_t j = 0; j < x; j++) {
        printf("%.1f\t|", M.matrix_[i][j]);
      }
      printf(("\n"));
    }
  }
}
