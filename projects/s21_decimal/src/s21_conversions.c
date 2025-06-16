#include "s21_decimal.h"

int getBinExp(float num) {
  unsigned int result = *((int *)&num), exp = 0, count = 0;
  for (unsigned int mask = 0x80000000; count <= 8; count++, mask >>= 1) {
    if (!!(result & mask) && count != 0) exp += pow(2, 8 - count);
  }
  result = exp - 127;
  return result;
}

unsigned int set_mask(int position) {
  unsigned int mask = 1;
  for (int i = 1; i <= position; i++) mask <<= 1;
  return mask;
}

int normalize_number(float *num, int *binexp) {
  int scale = 0;
  for (; !((int)(*num)) || *num <= pow(2, 20); scale++, *num *= 10) {
  }
  *num = round(*num);
  for (; !((int)*num % 10) && scale; *num /= 10, scale--) {
  }
  *binexp = getBinExp(*num);
  return scale;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if (!dst) {
    error = 1;
  } else {
    memset(dst, 0, sizeof(*dst));
    if (isinf(src) || isnan(src)) {
      error = 1;
    } else if (src) {
      int negative = 0;
      if (src < 0) {
        negative = 1;
        src *= -1;
      }
      int binexp = getBinExp(src);
      if (binexp > 95 || binexp < -94) {
        error = 1;
      } else {
        int scale = normalize_number(&src, &binexp);
        if (scale > 28) {
          error = 1;
        } else {
          setbit_1(dst, binexp);
          unsigned int mask = set_mask(22);
          unsigned int fsrc = *((unsigned int *)&src);
          for (int pos = binexp - 1; mask; mask >>= 1, pos--) {
            if (!!(fsrc & mask)) setbit_1(dst, pos);
          }
          set_scale(dst, scale);
          if (negative) setbit_1(dst, 127);
          error = 0;
        }
      }
    }
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  if (dst == NULL || get_scale(src) > 28) {
    error = 1;
  } else {
    *dst = 0.0;
    long double tmp = 0;
    for (int i = 0; i < 96; i++) {
      if (getbit(src, i)) {
        tmp += pow(2, i);
      }
    }
    int scale = get_scale(src);
    for (int i = 0; i < scale; i++) tmp /= 10;
    if (getbit(src, 127)) tmp *= -1;
    *dst = tmp;
  }
  return error;
}

// INT

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = int_errors(src, dst);
  if (!error) {
    memset(dst, 0, sizeof(*dst));
    if (src < 0) {
      setsign_1(dst);
      src *= -1;
    }
    dst->bits[0] = src;
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 1;
  if (dst) {
    s21_decimal truncated_number = {0};
    s21_truncate(src, &truncated_number);
    int highest_bit = get_highest_bit(src);
    if (highest_bit <= 31) {
      *dst = 0;
      for (int i = 0; i <= highest_bit; i++) {
        *dst += getbit(truncated_number, i) * pow(2, i);
      }
      if (getsign(src)) *dst *= -1;
      error = 0;
    }
  }
  return error;
}

int int_errors(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;  // Проверка указателя
  if (src == INT_MAX || src == INT_MIN) return 1;  // Проверка на переполнение
  return 0;
}
