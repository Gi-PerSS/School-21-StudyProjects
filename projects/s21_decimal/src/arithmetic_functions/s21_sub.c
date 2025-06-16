#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  int error = 0;
  int s1 = getsign(value_1);
  int s2 = getsign(value_2);
  setsign_0(&value_1);
  setsign_0(&value_2);
  int e = level_scale(&value_1, &value_2);
  if (!s1 && s2) {
    error = s21_add(value_1, value_2, result);
    setsign_0(result);
  } else if (s1 && !s2) {
    error = s21_add(value_1, value_2, result);
    setsign_1(result);
  } else if (s1 && s2) {
    error = s21_sub(value_2, value_1, result);
  } else {
    setsign_0(&value_1);
    setsign_0(&value_2);
    if (s21_is_greater(value_1, value_2)) {
      s21_twoscomplement(&value_2);
      setbit_1(&value_2, 97);
      error = s21_add(value_1, value_2, result);
      if (s1) {
        setsign_1(result);
      } else {
        setsign_0(result);
      }
    } else {
      if (!s21_is_equal(value_1, value_2)) {
        s21_twoscomplement(&value_1);
        setbit_1(&value_1, 97);
        error = s21_add(value_2, value_1, result);
        setsign_1(result);
      }
    }
  }
  set_scale(result, e);
  return error;
}

void s21_twoscomplement(s21_decimal *d) {
  int e = get_scale(*d);
  set_scale(d, 0);
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal tmp = {0};
  memcpy(&tmp, d, 16);
  for (int i = 0; i <= 95; i++) {
    if (getbit(tmp, i)) {
      setbit_0(d, i);
    } else {
      setbit_1(d, i);
    }
  }
  memcpy(&tmp, d, 16);
  *d = plus(tmp, d1);
  set_scale(d, e);
}
