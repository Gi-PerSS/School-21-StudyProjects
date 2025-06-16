#include "s21_decimal.h"

int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  // d1 > d2
  int sign1 = getsign(d1);
  int sign2 = getsign(d2);
  int result = 0;
  if (!sign1 && sign2) {  // если 1 число - положительное, 2 - отрицательное
    result = 1;
  } else {
    level_scale(&d1, &d2);
    if (sign1 == sign2 && !s21_is_equal(d1, d2)) {
      for (int i = 95; i >= 0; i--) {
        if (getbit(d1, i) && !getbit(d2, i)) {
          result = 1;
        }
        if (result || (!getbit(d1, i) && getbit(d2, i))) {
          break;
        }
      }
    }
    if (sign1 && sign2) result = result ? 0 : 1;
  }
  return result;
}

int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  int result = 1;
  for (int i = 0; i < 128; i++) {
    if (getbit(d1, i) != getbit(d2, i)) {
      result = 0;
      break;
    }
  }
  return result;
}

int s21_is_less(s21_decimal d1, s21_decimal d2) {
  return (!s21_is_greater(d1, d2) && !s21_is_equal(d1, d2));
}

int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_is_greater(d1, d2) || s21_is_equal(d1, d2));
}

int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return (!s21_is_greater(d1, d2) || s21_is_equal(d1, d2));
}

int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  return !(s21_is_equal(d1, d2));
}
