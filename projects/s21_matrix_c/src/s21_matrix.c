#include "s21_matrix.h"

#include <float.h>
#include <math.h>

int IsTroubleWithMatrix(matrix_t *x) {
  int is_trouble = 0;
  if ((*x).rows <= 0 || (*x).columns <= 0 || (*x).matrix == NULL) {
    is_trouble = 1;
  }

  return is_trouble;
}

int IsTroubleWithMatrixSizes(matrix_t *X, matrix_t *Y) {
  int is_trouble = 0;

  if (X->rows != Y->rows || X->columns != Y->columns) {
    is_trouble = 2;
  }

  return is_trouble;
}

int IsTroubleWithMultiplication(matrix_t *X, matrix_t *Y) {
  // Проверяем адекватность размеров исходных матриц и матрицы для результата

  /*
Операция умножения двух матриц выполнима только в том случае, если число
столбцов в первом сомножителе равно числу строк во втором; в этом случае
говорят, что матрицы согласованы.
    */
  int is_trouble = 0;

  is_trouble = IsTroubleWithMatrix(X) || IsTroubleWithMatrix(Y);

  if (!is_trouble) {
    if (X->columns != Y->rows) {
      is_trouble = 2;
    }
  }
  return is_trouble;
}

int TroubleDetector(matrix_t *A, matrix_t *B) {
  int is_trouble = 0;

  is_trouble = IsTroubleWithMatrix(A) || IsTroubleWithMatrix(B);

  if (!is_trouble) {
    is_trouble = IsTroubleWithMatrixSizes(A, B);
  }

  return is_trouble;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  /*
     Алгоритм
     - выделяем память одним куском и размечаем ее согласно данным. При этом,
 первая часть выделенной памяти будет содержать в себе адреса начал строк,
 вторая часть - содержимое этих строк. По следующей схеме:

 const int M = 100;
 const int N = 200;
 int **a = NULL;
 int i, j;

 a = (int**) malloc(M * sizeof(int*) + N * M * sizeof(int));
 a[0] = (int*)(a + M);
 for (i = 1; i < M; i++) {
     a[i] = a[0] + i * N;
 }
   */
  int is_trouble = 0;
  if (rows <= 0 || columns <= 0) {
    is_trouble = 1;
  }

  if (!is_trouble) {
    double **t = NULL;
    t = (double **)calloc(
        1, rows * sizeof(double *) + columns * rows * sizeof(double));

    t[0] = (double *)(t + rows);
    for (int i = 1; i < rows; i++) {
      t[i] = t[0] + i * columns;
    }

    result->rows = rows;
    result->columns = columns;
    result->matrix = t;

    is_trouble = IsTroubleWithMatrix(result);
  }
  return is_trouble;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

void MatrixSetValue(matrix_t *A, int row, int column, double value) {
  // отсчет индекса от 0.
  if (row >= (A->rows) || column >= (A->columns)) {
    printf("Wrong data on MatrixSetValue. Stop\n");
    exit(1);
  } else {
    A->matrix[row][column] = value;
    /*    double **target_row = A->matrix + row;
    double *target_column = *(target_row) + column;
    *target_column = value;*/
  }
}

double MatrixGetValue(matrix_t *A, int row, int column) {
  double r = 0;
  // отсчет индекса от 0.
  if (row >= (A->rows) || column >= (A->columns)) {
    printf("Wrong data on MatrixGetValue. Stop\n");
    exit(1);
  } else {
    r = A->matrix[row][column];
    /*   double **target_row = A->matrix + row;
        double *target_column = *(target_row) + column;
        r = *target_column;*/
  }
  return r;
}

int AreDoublesTheSame(double a, double b) {
  int r = 0;

  // Число ли это?
  if (isfinite(a) && isfinite(b)) {
    r = fabs(a - b) < 1e-7;
    return r;
  } else {
    // Если нет, то что?

    if (isinf(a) && isinf(b)) {
      if (a > DBL_MAX && b > DBL_MAX) {
        r = 1;
      } else {
        if (a < -DBL_MAX && b < -DBL_MAX) {
          r = 1;
        }
      }
    }
    if (isnan(a) && isnan(b)) {
      r = 1;
    }
  }

  return r;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int r = FAILURE;
  int is_trouble = TroubleDetector(A, B);

  if (!is_trouble) {
    r = SUCCESS;
    for (int row = 0; row != A->rows && r; row++) {
      for (int column = 0; column != A->columns && r; column++) {
        r = AreDoublesTheSame(MatrixGetValue(A, row, column),
                              MatrixGetValue(B, row, column));
      }
    }
  }

  return r;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int is_trouble = TroubleDetector(A, B);

  if (!is_trouble) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row != A->rows; row++) {
      for (int column = 0; column != A->columns; column++) {
        double summ =
            MatrixGetValue(A, row, column) + MatrixGetValue(B, row, column);
        MatrixSetValue(result, row, column, summ);
      }
    }
  }
  return is_trouble;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int is_trouble = TroubleDetector(A, B);

  if (!is_trouble) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row != A->rows; row++) {
      for (int column = 0; column != A->columns; column++) {
        double diff =
            MatrixGetValue(A, row, column) - MatrixGetValue(B, row, column);
        MatrixSetValue(result, row, column, diff);
      }
    }
  }
  return is_trouble;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int is_trouble = IsTroubleWithMatrix(A);

  if (!is_trouble) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row != A->rows; row++) {
      for (int column = 0; column != A->columns; column++) {
        double r = MatrixGetValue(A, row, column) * number;
        MatrixSetValue(result, row, column, r);
      }
    }
  }
  return is_trouble;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int is_trouble = IsTroubleWithMultiplication(A, B);

  if (!is_trouble) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int r_row = 0; r_row != result->rows; r_row++) {
      for (int r_column = 0; r_column != result->columns; r_column++) {
        double temp_r = 0;
        for (int a_column = 0; a_column != A->columns; a_column++) {
          temp_r += MatrixGetValue(A, r_row, a_column) *
                    MatrixGetValue(B, a_column, r_column);
        }
        MatrixSetValue(result, r_row, r_column, temp_r);
      }
    }
  }

  return is_trouble;
}

int IsTroubleWithTranspose(matrix_t *X, matrix_t *Y) {
  int is_trouble = 0;

  is_trouble = IsTroubleWithMatrix(X) || IsTroubleWithMatrix(Y);

  if (!is_trouble) {
    if (X->columns != Y->rows || X->rows != Y->columns) {
      is_trouble = 2;
    }
  }
  return is_trouble;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int is_trouble = IsTroubleWithMatrix(A);

  if (!is_trouble) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i != A->rows; i++) {
      for (int j = 0; j != A->columns; j++) {
        MatrixSetValue(result, j, i, MatrixGetValue(A, i, j));
      }
    }
  }

  return is_trouble;
}

void MinorCreator(matrix_t *X, matrix_t *minor_X, int exclude_row,
                  int exclude_column) {
  // создаем минор матрицы по указанными координатам.
  int is_trouble = IsTroubleWithMatrix(X) || IsTroubleWithMatrix(minor_X);

  if (!is_trouble) {
    for (int i = 0, minor_i = 0; i < X->rows; i++, minor_i++) {
      for (int j = 0, minor_j = 0; j < X->columns; j++, minor_j++) {
        // встречаем ненужную строку, пропускаем
        if (i == exclude_row) {
          i++;
        }

        // то же, встречая ненужный столбец
        if (j == exclude_column) {
          j++;
        }

        // все остальное копируем в минор
        // Проверка на выход за пределы размерности матрицы.
        if (j < X->columns && i < X->rows) {
          MatrixSetValue(minor_X, minor_i, minor_j, MatrixGetValue(X, i, j));
        }
      }
    }
  } else {
    printf("Trouble with matricies in MinorCreator. Stop\n");
    exit(1);
  }
}

int IsTroubleWithDeterminant(matrix_t *A) {
  int is_trouble = 0;
  is_trouble = IsTroubleWithMatrix(A);

  if (!is_trouble && A->columns != A->rows) {
    is_trouble = 2;
  } else {
    if (A->rows == 1) {
      // определяем не единичная ли матрица
      is_trouble = 3;
    }
  }
  return is_trouble;
}

int s21_determinant(matrix_t *A, double *result) {
  // рекурсивно определяем детерминант, редуцируя исходную матрицу через
  // миноризацию до матрицы 2х2, параллельно накапливая результат-детерминант.

  int is_trouble = IsTroubleWithDeterminant(A);
  double determinant = 0;

  if (!is_trouble) {
    if (A->rows == 2) {
      determinant = MatrixGetValue(A, 0, 0) * MatrixGetValue(A, 1, 1) -
                    MatrixGetValue(A, 1, 0) * MatrixGetValue(A, 0, 1);
    } else {
      // Формула: A[1,1]*(-1)^(1+1)*D|minor|+ ...

      for (int i = 0; i != A->columns; i++) {
        // раскладываем детерминант по первой строке
        double t = 0;
        t = MatrixGetValue(A, 0, i);
        t *= pow((-1), (1 + (i + 1)));
        // создаем минор по первой строке
        matrix_t minor;
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        MinorCreator(A, &minor, 0, i);
        double Dt = 0;
        s21_determinant(&minor, &Dt);
        s21_remove_matrix(&minor);
        t *= Dt;
        determinant += t;
      }
    }
  } else {
    // для матрицы 1 на 1.
    if (is_trouble == 3) {
      determinant = MatrixGetValue(A, 0, 0);
      is_trouble = 0;
    }
  }

  *result = determinant;
  return is_trouble;
}

int IsTroubleWithMinor(matrix_t *X) {
  int is_trouble = 0;
  is_trouble = IsTroubleWithMatrix(X);
  if (!is_trouble) {
    if (X->rows == 1 || X->columns == 1 || X->rows != X->columns) {
      is_trouble = 2;
    }
  }
  return is_trouble;
}

int MinorMatrixCreator(matrix_t *A, matrix_t *result) {
  // Создаем миноры, вычисляем из них детерминанты и кладем значение в новую
  // матрицу.

  int is_trouble = 0;
  is_trouble = IsTroubleWithMinor(A);

  if (!is_trouble) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i != A->rows; i++) {
      for (int j = 0; j != A->columns; j++) {
        matrix_t t;
        s21_create_matrix(A->rows - 1, A->columns - 1, &t);
        MinorCreator(A, &t, i, j);
        double d;
        s21_determinant(&t, &d);
        MatrixSetValue(result, i, j, d);
        s21_remove_matrix(&t);
      }
    }
  }

  return is_trouble;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // Создаем матрицу миноров, после умножаем каждый элемент на -1 в нужной
  // степени.

  int is_trouble = 0;
  is_trouble = IsTroubleWithMinor(A);

  if (!is_trouble) {
    // Память выделяется под result внутри минор-креатора
    //    s21_create_matrix(A->rows, A->columns, result);
    MinorMatrixCreator(A, result);
    for (int i = 0; i != A->rows; i++) {
      for (int j = 0; j != A->columns; j++) {
        MatrixSetValue(result, i, j,
                       pow(-1, i + 1 + j + 1) * MatrixGetValue(result, i, j));
      }
    }
  }

  return is_trouble;
}

int IsTroubleWithInversMatrix(matrix_t *A) {
  int is_trouble = IsTroubleWithDeterminant(A);

  double determinant;

  if (!is_trouble || is_trouble == 3 /*матрица 1x1*/) {
    is_trouble = 0;
    s21_determinant(A, &determinant);

    if (AreDoublesTheSame(determinant, 0.0)) {
      is_trouble = 2;
    }
  }

  return is_trouble;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  // Формула: A^(-1) =  1/|A| * M^T.
  int is_trouble = IsTroubleWithInversMatrix(A);
  if (!is_trouble) {
    double determinant;
    s21_determinant(A, &determinant);

    if (A->columns == 1 && A->rows == 1) {
      // Если матрица единичная
      MatrixSetValue(result, 0, 0, (1.0 / MatrixGetValue(A, 0, 0)));
    } else {
      matrix_t complements_matrix;
      s21_calc_complements(A, &complements_matrix);

      matrix_t transpose_complement;
      s21_transpose(&complements_matrix, &transpose_complement);

      double one_divide_det = 0;
      one_divide_det = 1.0 / determinant;
      s21_mult_number(&transpose_complement, one_divide_det, result);

      s21_remove_matrix(&complements_matrix);
      s21_remove_matrix(&transpose_complement);
    }
  }

  return is_trouble;
}