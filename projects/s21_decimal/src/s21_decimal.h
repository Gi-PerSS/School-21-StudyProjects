#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK "\033[0;30m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"
#define BG_WHITE "\033[0;47m"

#define S21_DECIMAL_MAX_STRING "79228162514264337593543950335"
#define S21_DECIMAL_MIN_STRING "-79228162514264337593543950335"

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int getbit(s21_decimal d, int i);
void setbit_0(s21_decimal* d, int i);
void setbit_1(s21_decimal* d, int i);
int getsign(s21_decimal d);
void setsign_0(s21_decimal* d);
void setsign_1(s21_decimal* d);
int get_highest_bit(s21_decimal dec);
int decimal_null(s21_decimal dec);
int level_scale(s21_decimal* value_1, s21_decimal* value_2);
void divide_by_ten(s21_decimal value, s21_decimal *result);
void printDecimal(s21_decimal a);

int s21_is_greater(s21_decimal d1, s21_decimal d2);
int s21_is_less(s21_decimal d1, s21_decimal d2);
int s21_is_equal(s21_decimal d1, s21_decimal d2);
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_not_equal(s21_decimal d1, s21_decimal d2);

void s21_twoscomplement(s21_decimal* d);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int shift_left(s21_decimal* d, int n);
s21_decimal shift_right(s21_decimal d, int n);
int get_firstone(s21_decimal d);
int div_func(s21_decimal* value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
void s21_new_div(s21_decimal value_N, s21_decimal value_D, s21_decimal* Q,
                 s21_decimal* R);
int s21_n_less_than_d(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal* result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int multiply_by_ten(s21_decimal value, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
s21_decimal plus(s21_decimal a, s21_decimal b);

int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int getBinExp(float num);
unsigned int set_mask(int position);
int get_scale(s21_decimal dec);
void set_scale(s21_decimal* dst, int scale);
int normalize_number(float* num, int* binexp);
int int_errors(int src, s21_decimal* dst);

int s21_negate(s21_decimal value, s21_decimal* result);
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
void copy_decimal(s21_decimal value, s21_decimal* result);
void get_rem(s21_decimal remainder, int* rem);

#endif  // SRC_S21_DECIMAL_H_
