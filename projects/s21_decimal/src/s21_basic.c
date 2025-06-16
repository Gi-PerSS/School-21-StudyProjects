#include "s21_decimal.h"

int getbit(s21_decimal d, int i) {
  unsigned int mask = 1u << (i % 32);
  return !!(d.bits[i / 32] & mask);
}

void setbit_0(s21_decimal *d, int i) {
  unsigned int mask = ~(1u << (i % 32));
  (d->bits[i / 32]) = (d->bits[i / 32]) & mask;
}

void setbit_1(s21_decimal *d, int i) {
  unsigned int mask = (1u << (i % 32));
  (d->bits[i / 32]) = (d->bits[i / 32]) |= mask;
}

int getsign(s21_decimal d) {
  unsigned int mask = (1u << 31);
  return !!(d.bits[3] & mask);
}

void setsign_0(s21_decimal *d) {
  unsigned int mask = ~(1u << 31);
  (d->bits[3]) = (d->bits[3]) & mask;
}

void setsign_1(s21_decimal *d) {
  unsigned int mask = (1u << 31);
  (d->bits[3]) |= mask;
}

int get_highest_bit(s21_decimal dec) {
  int i = 95;
  for (; i >= 0; i--)
    if (getbit(dec, i)) break;
  return i;
}

int decimal_null(s21_decimal dec) {
  int i = 95;
  for (; i >= 0; i--)
    if (getbit(dec, i)) break;
  return !(i + 1);
}

int get_scale(s21_decimal dec) {
  int scale = 0;
  for (int i = 112; i < 120; i++) {
    if (getbit(dec, i)) scale += pow(2, i - 112);
  }
  return scale;
}

void set_scale(s21_decimal *dst, int scale) {
  unsigned int mask = 1;
  for (int i = 112; i < 120; i++) {
    if (!scale)
      setbit_0(dst, i);
    else if (scale & mask)
      setbit_1(dst, i);
    mask <<= 1;
  }
}

int level_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int error = 0;
  s21_decimal d10 = {0};
  s21_from_int_to_decimal(10, &d10);
  int e1 = get_scale(*value_1);
  int e2 = get_scale(*value_2);
  s21_decimal change = e1 > e2 ? *value_2 : *value_1;
  int max_exp = e1 > e2 ? e1 : e2;
  int min_exp = e1 < e2 ? e1 : e2;

  while (min_exp != max_exp && min_exp < 29 && !error) {
    error = multiply_by_ten(change, &change);
    min_exp++;
    set_scale(&change, min_exp);
  }
  if (!error) {
    if (e1 < e2) {
      *value_1 = change;
    } else if (e1 > e2) {
      *value_2 = change;
    }
  }
  return max_exp;
}

int shift_left(s21_decimal *d, int n) {
  int bits0;
  int bits1;
  int bits2;
  for (int i = 0; i < n; i++) {
    bits0 = getbit(*d, 31);
    d->bits[0] <<= 1;

    bits1 = getbit(*d, 63);
    d->bits[1] <<= 1;

    if (bits0) {
      setbit_1(d, 32);
    }

    bits2 = getbit(*d, 95);
    d->bits[2] <<= 1;

    if (bits1) {
      setbit_1(d, 64);
    }
  }
  return bits2;
}

s21_decimal shift_right(s21_decimal d, int n) {
  int bits0;
  int bits1;
  for (int i = 0; i < n; i++) {
    bits0 = getbit(d, 64);

    d.bits[2] >>= 1;
    setbit_0(&d, 95);

    bits1 = getbit(d, 32);
    d.bits[1] >>= 1;
    setbit_0(&d, 63);
    if (bits0) {
      setbit_1(&d, 63);
    }
    d.bits[0] >>= 1;
    setbit_0(&d, 31);

    if (bits1) {
      setbit_1(&d, 31);
    }
  }
  return d;
}

int multiply_by_ten(s21_decimal value, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  set_scale(&value, 0);
  int error = 0;
  s21_decimal d0 = {0};
  s21_decimal d10 = {{10, 0, 0, 0}};
  while (s21_is_not_equal(d10, d0)) {
    //        int ires;
    //        s21_from_decimal_to_int(*result, &ires);
    //        printf("fres: %d\n", ires);
    if (getbit(d10, 0)) {
      *result = plus(*result, value);
    }
    d10 = shift_right(d10, 1);
    error = shift_left(&value, 1);
  }
  return error;
}

void divide_by_ten(s21_decimal value, s21_decimal *result) {
  memset(result, 0, sizeof(*result));
  set_scale(&value, 0);
  s21_decimal r = {0};
  s21_decimal d9 = {{9, 0, 0, 0}};
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal temp1 = {0};
  s21_decimal temp2 = {0};
  *result = plus(shift_right(value, 1), shift_right(value, 2));
  *result = plus(*result, shift_right(*result, 4));
  *result = plus(*result, shift_right(*result, 8));
  *result = plus(*result, shift_right(*result, 16));
  *result = shift_right(*result, 3);
  shift_left(result, 2);
  temp1 = *result;
  *result = shift_right(*result, 2);
  temp2 = plus(temp1, *result);
  shift_left(&temp2, 1);
  s21_sub(value, temp2, &r);
  if (s21_is_greater(r, d9)) {
    *result = plus(*result, d1);
  }
}

// void printDecimal(s21_decimal a) {
//   for (int i = 0, bit = 3; i < 127; i++) {
//     (i == 16 || i == 48 || i == 81 || i == 113) ? printf("%d", bit--)
//                                                 : printf(" ");
//   }
//   printf("\n");
//   int current_bit = 0;
//   for (int i = 127; i >= 0; i--) {
//     current_bit = getbit(a, i);
//     if (current_bit == 1) {
//       printf(BG_WHITE "%d" RESET, current_bit);
//     } else {
//       printf("%d", current_bit);
//     }
//     if (i == 32 || i == 64 || i == 96 || i == 112) {
//       printf("%c", '|');
//     }
//   }
//   printf("\n");
// }
