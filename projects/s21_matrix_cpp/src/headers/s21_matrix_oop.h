#ifndef SRC_S21_MATRIX_OOP_H
#define SRC_S21_MATRIX_OOP_H
#include <cfloat>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 public:
  size_t GetRowsNumber();
  size_t GetColumnsNumber();
  void SetNewMatrixSize(size_t rows, size_t cols);

  // конструкторы-инициализаторы
  S21Matrix();  // нулевая матрица
  S21Matrix(size_t number_of_rows_and_cols);
  S21Matrix(size_t rows, size_t cols);
  S21Matrix(const S21Matrix& original);  // конструктор копирования
  S21Matrix(S21Matrix&& original);  // конструктор перемещения
  ~S21Matrix();

  // Инициализация нулевой матрицы и реинициализация существующей новыми
  // размерами с обнулением содержимого.
  void PostConstructInitializer(size_t rows, size_t columns);
  void PostConstructInitializer(size_t number_of_rows_and_cols);

  // библиотека
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  double Determinant();
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  // перегрузка операторов
  S21Matrix& operator=(const S21Matrix& original);
  S21Matrix& operator=(const std::string file_path);
  S21Matrix operator+(S21Matrix& RightHandSide);
  S21Matrix operator-(S21Matrix& RightHandSide);
  S21Matrix operator*(S21Matrix& RightHandSide);
  S21Matrix operator*(const double y);
  S21Matrix operator+=(S21Matrix& RightHandSide);
  S21Matrix operator-=(S21Matrix& RightHandSide);
  S21Matrix operator*=(S21Matrix& RightHandSide);
  bool operator==(S21Matrix& RightHandSide);
  double& operator()(size_t rows, size_t columns);
  double& operator()(size_t rows, size_t columns) const;

 private:
  size_t rows_, cols_;  // Rows and columns
  double** matrix_;     // Pointer to the memory where the matrix is allocated
  enum kExeptionCheckIDs {
    SumMatrixID = 1,
    SubMatrixID,
    MulMatrixID,
    MulNumberID,
    CalcComplementsID,
    DeterminantID,
    InverseMatrixID,
    IndexationID,
    MemoryAllocatorID,
    PostConstructInitializerID,
    SetNewMatrixSizeID
  };

  void DataChecker(int function_id);
  void DataChecker(int function_id, size_t rows, size_t cols) const;
  void DataChecker(int function_id, const S21Matrix& other) const;
  void DataChecker(const std::string file_path);

  bool AreDoublesTheSame(double a, double b) const;
  double** MemoryAllocator(size_t rows, size_t columns);
  size_t MatrixMemorySizeCalculator(size_t rows, size_t columns);
  void Copier(S21Matrix& destination, const S21Matrix& original);
  void MinorCreator(S21Matrix& X, S21Matrix& MinorOfTheX, size_t exclude_row,
                    size_t exclude_column);
  void MinorMatrixCreator(S21Matrix& A, S21Matrix& Result);
  S21Matrix MatrixFromFile(const std::string file_path);

  // отладочно-вспомогательные
  friend void DBG_matrix_printer(S21Matrix& M, const char* debug_message);
  friend void DBG_MatrixSetConstant(double constant_value_for_all_cells,
                                    S21Matrix& M);
};

#endif