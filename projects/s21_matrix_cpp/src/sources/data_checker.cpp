#include "../headers/s21_matrix_oop.h"
// Проверка данных
void S21Matrix::DataChecker(const std::string file_path) {
  // Перегрузка присваивания из файлов, для тестов.
  bool is_file_exist = 1;

  try {
    if (!is_file_exist) {
      throw "Assignment from file overloader\nHi! The file does not exist. Stop.";
    }
  } catch (const char *error_message) {
    std::cerr << "About file: " << file_path << std::endl;
    std::cerr << error_message << std::endl;
    std::terminate();
  }
  std::ifstream TxtMatrix;
  TxtMatrix.open(file_path);
  size_t rows = 0;
  size_t cols = 0;
  char trash_buffer;
  TxtMatrix >> rows >> trash_buffer >> cols;
  double t = 0;
  size_t check_summ = 0;
  while (TxtMatrix >> t) {
    check_summ++;
  }
  try {
    if (check_summ != (rows * cols)) {
      throw std::runtime_error(
          "Assignment from file overloader\nHi! The dimensions of the matrix "
          "do not coincide with the declared ones.");
    }
  } catch (const std::exception &e) {
    TxtMatrix.close();
    std::cerr << "In file: " << file_path << std::endl;
    std::cerr << e.what() << std::endl;
    std::cerr << "Checksumm (rows * columns): " << check_summ << std::endl;
    std::cerr << "Actual rows & columns: " << rows << " & " << cols
              << std::endl;
    std::terminate();
  }
  TxtMatrix.close();
}

void S21Matrix::DataChecker(int function_id, size_t rows, size_t cols) const {
  switch (function_id) {
    case IndexationID: {
      bool is_data_ok = (cols < cols_) && (rows < rows_);
      if (!is_data_ok) {
        throw std::runtime_error(
            "Indexation overloader\nHi! We have a problem with the index - "
            "something is wrong with it. Stop.");
      }
    } break;

    default: {
      std::cerr << "Wrong call on\n"
                << "void S21Matrix::DataChecker(int function_id, size_t rows, "
                   "size_t cols) const\n"
                << "by the ID: " << function_id << std::endl;
    } break;
  }
  return;
}

void S21Matrix::DataChecker(int function_id, const S21Matrix &other) const {
  switch (function_id) {
    case SumMatrixID: {
      bool is_data_ok = (other.cols_ == cols_ && other.rows_ == rows_);
      if (!is_data_ok) {
        throw std::runtime_error(
            "SumMatrix()\nHi! We have a problem: the dimensions of the "
            "matrices do not match. Stop.");
      }
    } break;
    case SubMatrixID: {
      bool is_data_ok = (other.cols_ == cols_ && other.rows_ == rows_);
      if (!is_data_ok) {
        throw std::runtime_error(
            "SubMatrix()\nHi! We have a problem: the dimensions of the "
            "matrices do not match. Stop.");
      }

    } break;
    case MulMatrixID: {
      bool is_data_ok = (other.cols_ == rows_ && other.rows_ == cols_);
      if (!is_data_ok) {
        throw std::runtime_error(
            "MulMatrix()\nHi! We have a problem with matching the dimension "
            "of the matrices. Stop.");
      }

    } break;

    default: {
      std::cerr << "Wrong call on\n"
                << "void S21Matrix::DataChecker(int function_id, const "
                   "S21Matrix &other) const\n"
                << "by the ID: " << function_id << std::endl;
    } break;
  }

  return;
}

void S21Matrix::DataChecker(int function_id) {
  // Проверки для операций объекта над собой.
  switch (function_id) {
    case InverseMatrixID: {
      bool is_data_ok = (Determinant() != 0);
      if (!is_data_ok) {
        throw std::runtime_error(
            "InverseMatrix()\nHi! Determinant is zero. Stop.");
      }

    } break;
    case DeterminantID: {
      bool is_data_ok = (cols_ == rows_);
      is_data_ok = is_data_ok && (cols_ != 0 && rows_ != 0);
      if (!is_data_ok) {
        throw std::runtime_error(
            "Determinant()\nHi! We have a problem with the dimension of the "
            "matrix. Stop.");
      }

    } break;
    case MulNumberID: {
      bool is_data_ok = (cols_ != 0 && rows_ != 0);
      if (!is_data_ok) {
        throw std::runtime_error(
            "MulNumber()\nHi! Someone is trying to multiply the matrix 0x0 "
            "by a number. Stop.");
      }

    } break;
    case CalcComplementsID: {
      bool is_data_ok = (cols_ > 1 && rows_ > 1);
      is_data_ok = is_data_ok && (cols_ == rows_);
      if (!is_data_ok) {
        throw std::runtime_error(
            "CalcComplements()\nHi! We have a problem with the dimension of "
            "the matrix. Stop.");
      }

    } break;
    default: {
      std::cerr << "Wrong call on\n"
                << "void S21Matrix::DataChecker(int function_id)\n"
                << "by the ID: " << function_id << std::endl;
    } break;
  }
}