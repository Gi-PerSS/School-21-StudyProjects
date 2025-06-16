#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal d = {0};
  memset(result, 0, sizeof(*result));
  int sign1 = getsign(value_1);
  int sign2 = getsign(value_2);
  if (s21_is_equal(value_1, d) || s21_is_equal(value_2, d)) {
    *result = d;
  } else {
    int highest_bit = get_highest_bit(value_2);
    d = value_1;
    for (int i = 0; i <= highest_bit; i++) {
      if (getbit(value_2, i)) {
        (*result) = plus((*result), d);
      }
      error = shift_left(&d, 1);
    }
    int scale_sum = get_scale(value_1) + get_scale(value_2);
    if (scale_sum > 28) {
      error = 2;
    } else {
      set_scale(result, scale_sum);
    }
  }
  if (sign1 != sign2) {
    setsign_1(result);
  }
  if (error == 1 && (sign1 + sign2) == 1) {
    error = 2;
  }
  return error;
}

s21_decimal plus(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal d = {0};
  int tmp = 0;  // единичка "в уме"
  for (int i = 0; i < 96; i++) {
    if (getbit(value_1, i) && getbit(value_2, i)) {
      if (tmp) {
        setbit_1(&d, i);
      }
      tmp = 1;
    } else if (getbit(value_1, i) || getbit(value_2, i)) {
      if (!tmp) {
        setbit_1(&d, i);
      }
    } else if (tmp) {
      setbit_1(&d, i);
      tmp = 0;
    }
  }
  return d;
}
