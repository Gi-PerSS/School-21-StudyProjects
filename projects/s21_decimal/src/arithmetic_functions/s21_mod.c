#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int e = level_scale(&value_1, &value_2);
  set_scale(&value_1, 0);
  set_scale(&value_2, 0);
  int sign1 = getsign(value_1);
  int sign2 = getsign(value_2);
  setsign_0(&value_1);
  setsign_0(&value_2);
  s21_decimal d0 = {0};
  s21_decimal quotient = {0};
  if (s21_is_not_equal(value_2, d0)) {
    s21_new_div(value_1, value_2, &quotient, result);
  } else {
    error = 3;
  }
  if (sign1 != sign2 && !decimal_null(*result)) {
    setsign_1(result);
  }
  set_scale(result, e);
  return error;
}
