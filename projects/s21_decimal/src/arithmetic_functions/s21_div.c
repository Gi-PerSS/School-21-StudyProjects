#include "../s21_decimal.h"

int get_error(s21_decimal value_1, s21_decimal value_2) {
  int error = 0;
  int e1 = get_scale(value_1);
  int e2 = get_scale(value_2);
  int sign1 = getsign(value_1);
  int sign2 = getsign(value_2);
  if (s21_is_greater(value_1, value_2) && (e1 + e2) >= 28) {
    error = (sign1 != sign2) ? 2 : 1;
  } else if (s21_is_greater(value_2, value_1) && (e1 - e2) >= 28) {
    error = 2;
  }
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = get_error(value_1, value_2);
  if (!error) {
    int sign1 = getsign(value_1);
    int sign2 = getsign(value_2);
    setsign_0(&value_1);
    setsign_0(&value_2);
    int e = level_scale(&value_1, &value_2);
    set_scale(&value_1, 0);
    set_scale(&value_2, 0);
    set_scale(result, e);
    s21_decimal d0 = {0};
    s21_decimal remainder = {0};
    if (s21_is_not_equal(value_2, d0)) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        s21_new_div(value_1, value_2, result, &remainder);
        if (s21_is_greater(remainder, d0)) {
          s21_n_less_than_d(remainder, value_2, &value_1);
          s21_add(*result, value_1, result);
        }
      } else {
        error = s21_n_less_than_d(value_1, value_2, result);
      }
    } else {
      error = 3;
    }
    if (sign1 != sign2) {
      setsign_1(result);
    }
  }
  return error;
}

void s21_new_div(s21_decimal value_N, s21_decimal value_D, s21_decimal *Q,
                 s21_decimal *R) {
  memset(R, 0, sizeof(*R));
  memset(Q, 0, sizeof(*Q));
  for (int i = 95; i >= 0; i--) {
    shift_left(R, 1);
    if (getbit(value_N, i)) {
      setbit_1(R, 0);
    } else {
      setbit_0(R, 0);
    }
    if (s21_is_greater_or_equal(*R, value_D)) {
      s21_sub(*R, value_D, R);
      setsign_0(R);
      setbit_1(Q, i);
    }
  }
}

int s21_n_less_than_d(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  int error = 0;
  memset(result, 0, sizeof(*result));
  int n = get_scale(*result);
  set_scale(&value_1, 0);
  set_scale(&value_2, 0);
  s21_decimal d0 = {0};
  s21_decimal tempres = {0};
  multiply_by_ten(value_1, &value_1);
  n++;
  if (n == 28) {
    error = 2;
  }
  while (s21_is_not_equal(value_1, d0) && n < 28) {
    while (s21_is_less(value_1, value_2)) {
      n++;
      multiply_by_ten(*result, result);
      multiply_by_ten(value_1, &value_1);
    }

    memset(&tempres, 0, sizeof(tempres));
    s21_new_div(value_1, value_2, &tempres, &value_1);
    s21_add(*result, tempres, result);
  }
  set_scale(result, n);
  return error;
}
