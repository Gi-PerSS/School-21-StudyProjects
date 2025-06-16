#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result) {
    memset(result, 0, sizeof(*result));
    copy_decimal(value, result);
    getbit(value, 127) ? setsign_0(result) : setsign_1(result);
    error = 0;
  }
  return error;
}

void copy_decimal(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 128; i++) {
    if (getbit(value, i)) setbit_1(result, i);
  }
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0, scale, sign;
  scale = get_scale(value);
  sign = getsign(value);
  if (!result) {
    error = 1;
  } else if (scale > 28) {
    error = 1;
    memset(result, 0, sizeof(*result));
  } else if (scale) {
    memset(result, 0, sizeof(*result));
    value.bits[3] = 0;
    for (; scale; scale--) {
      divide_by_ten(value, &value);
    }
    copy_decimal(value, result);
    set_scale(result, 0);
  } else {
    memset(result, 0, sizeof(*result));
    copy_decimal(value, result);
  }
  if (sign) setsign_1(result);
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result) {
    memset(result, 0, sizeof(*result));
    s21_decimal truncated_number = {0};
    if (!s21_truncate(value, &truncated_number)) {
      if (s21_is_equal(truncated_number, value)) {
        copy_decimal(value, result);
        error = 0;
      } else {
        if (getsign(value)) {
          s21_decimal one = {{1, 0, 0, 0}};
          error = s21_sub(truncated_number, one, result);
        } else {
          copy_decimal(truncated_number, result);
          error = 0;
        }
      }
    }
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result) {
    memset(result, 0, sizeof(*result));
    int sign = getsign(value);
    if (sign) s21_negate(value, &value);
    s21_decimal one = {{1, 0, 0, 0}}, half, diff, truncated_number;
    s21_from_float_to_decimal(0.5, &half);
    if (!s21_truncate(value, &truncated_number)) {
      s21_sub(value, truncated_number, &diff);
      if (s21_is_greater_or_equal(diff, half)) {
        s21_add(truncated_number, one, result);
      } else {
        copy_decimal(truncated_number, result);
      }
      if (sign) s21_negate(*result, result);
      error = 0;
    }
  }
  return error;
}
