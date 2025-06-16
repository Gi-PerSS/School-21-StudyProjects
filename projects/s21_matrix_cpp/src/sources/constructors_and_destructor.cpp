#include "../headers/s21_matrix_oop.h"

// конструкторы и деструктор

size_t S21Matrix::MatrixMemorySizeCalculator(size_t rows, size_t columns) {
  // вычисляет объем памяти, необходимый  для размещения матрицы
  size_t memory_size =
      (rows * sizeof(double *) + columns * rows * sizeof(double));
  return memory_size;
}

double **S21Matrix::MemoryAllocator(size_t rows, size_t columns) {
  /*
  Алгоритм выделения памяти:
  - выделяем память одним куском и размечаем ее следующим образом: первая часть
  выделенной памяти будет содержать в себе адреса начал строк, вторая часть -
  содержимое этих строк.
  */
  double **t;
  if (columns > 0 && rows > 0) {
    try {
      t = new double *[MatrixMemorySizeCalculator(columns, rows)];
    } catch (std::bad_alloc &exc) {
      std::cerr << "Hi! We have a problem with memory allocation - it was not "
                   "allocated. Stop.\n"
                << exc.what() << std::endl;
      std::terminate();
    }

    t[0] = (double *)(t + rows);
    for (size_t i = 1; i < rows; i++) {
      t[i] = t[0] + i * columns;
    }

    // Память выделялась под double**, поэтому внутри лежат нули неправильного
    // типа, делаем нули правильного типа (чтобы избежать погрешности при
    // вычислениях с неинициализированной матрицей)
    for (size_t row = 0; row != rows_; row++) {
      for (size_t column = 0; column != cols_; column++) {
        t[row][column] = 0.0;
      }
    }
  } else {
    t = nullptr;
  }
  return t;
}

// конструктор по умолчанию
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// конструктор с инициализацией значений и выделением памяти
S21Matrix::S21Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
  matrix_ = MemoryAllocator(rows, cols);
}

// конструктор квадратной матрицы
S21Matrix::S21Matrix(size_t number_of_rows_and_cols)
    : rows_(number_of_rows_and_cols), cols_(number_of_rows_and_cols) {
  matrix_ = MemoryAllocator(number_of_rows_and_cols, number_of_rows_and_cols);
}

// конструктор копирования
void S21Matrix::Copier(S21Matrix &destination, const S21Matrix &original) {
  /* Предполагается, что память в destination очищена вызывающей стороной */
  destination.rows_ = original.rows_;
  destination.cols_ = original.cols_;
  destination.matrix_ = MemoryAllocator(original.rows_, original.cols_);

  for (size_t i = 0; i < destination.rows_; i++) {
    for (size_t j = 0; j < destination.cols_; j++) {
      destination.matrix_[i][j] = original.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix &original) { Copier(*this, original); }

// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix &&original)
    : rows_(original.rows_), cols_(original.cols_), matrix_(original.matrix_) {
  original.matrix_ = nullptr;
  original.cols_ = 0;
  original.rows_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    delete[] matrix_;
  }
}

// инициализатор пустой матрицы 0x0, изменение размерности существующей матрицы.
void S21Matrix::PostConstructInitializer(size_t rows, size_t cols) {
  // Функция изменения размера существующей матрицы с полной реинициализацией.
  if (rows != rows_ && cols != cols_) {
    rows_ = rows;
    cols_ = cols;
    delete[] matrix_;
    matrix_ = MemoryAllocator(rows_, cols_);
  }
}

void S21Matrix::PostConstructInitializer(size_t number_of_rows_and_cols) {
  if (number_of_rows_and_cols != rows_ && number_of_rows_and_cols != cols_) {
    rows_ = number_of_rows_and_cols;
    cols_ = number_of_rows_and_cols;
    delete[] matrix_;
    matrix_ = MemoryAllocator(rows_, cols_);
  }
}
