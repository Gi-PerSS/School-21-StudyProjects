#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int IsTroubleWithMatrix(matrix_t *x);
int IsTroubleWithMatrixSizes(matrix_t *X, matrix_t *Y);
int IsTroubleWithMultiplication(matrix_t *A, matrix_t *B);
int TroubleDetector(matrix_t *A, matrix_t *B);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

// Функция установки данного значения в ячеку данной матрицы
void MatrixSetValue(matrix_t *A, int row, int column, double value);
double MatrixGetValue(matrix_t *A, int row, int column);
int AreDoublesTheSame(double a, double b);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);

void MinorCreator(matrix_t *X, matrix_t *minor_X, int exclude_i, int exclude_j);
int s21_determinant(matrix_t *x, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_