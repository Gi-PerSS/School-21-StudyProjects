#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  int error = 0;
  int tmp = 0;  //  единичка в уме
  int s1 = getsign(value_1);
  int s2 = getsign(value_2);
  int e = level_scale(&value_1, &value_2);
  setsign_0(&value_1);
  setsign_0(&value_2);
  if (!s1 && s2) {
    if (s21_is_greater(value_1, value_2)) {
      s21_sub(value_1, value_2, result);
    } else {
      s21_sub(value_2, value_1, result);
      setsign_1(result);
    }
  } else if (s1 && !s2) {
    if (s21_is_greater(value_1, value_2)) {
      s21_sub(value_1, value_2, result);
      setsign_1(result);
    } else {
      s21_sub(value_2, value_1, result);
      setsign_0(result);
    }
  } else {
    for (int i = 0; i <= 95; i++) {
      int leftbit = getbit(value_1, i);
      int rightbit = getbit(value_2, i);
      if (leftbit & rightbit) {
        if (tmp == 1) {
          setbit_1(result, i);
        } else {
          tmp = 1;
        }
      } else if (leftbit ^ rightbit) {
        if (tmp != 1) {
          setbit_1(result, i);
        }
      } else if (!leftbit && !rightbit && tmp) {
        setbit_1(result, i);
        tmp = 0;
      }
    }
  }
  if (s1 && s2) {
    setsign_1(result);
  }
  if (tmp == 1 && getbit(value_2, 97) == 0) {
    if (s1 & s2) {
      error = 2;
    } else if (!s1 && !s2) {
      error = 1;
    }
    memset(result, 0, sizeof(*result));
  }
  set_scale(result, e);

  return error;
}
