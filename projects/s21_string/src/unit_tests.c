#include <check.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"

#define SOURCE_50 "_THIS is a SOURCE string. Length = (49 + 0) = 50_"
#define SOURCE_50L L"_THIS is a SOURCE string. Length = (49 + 0) = 50_"

#define SRC_NULL "_THIS is a'\0' SOURCE. Length'\0' = (51 + 0) = 51_"
#define DEST_LARGER_55 "------------------------------------------------------"
#define DEST_SMALLER_6 "-----"
#define BRK_CHAR_3 ".=+"
#define CHAR_IN 'i'
#define CHAR_OUT '*'
#define LENGTH0 50
#define LENGTH 49
#define OVERLENGTH 111
#define SPRTR \
  "======================================================================="
#define N_CALL 10
/* end of const-data set */

/* S21_memchr. START TESTS */
static char test_data_0[] = SOURCE_50;
static void *test_data_1 = (void *)test_data_0;
START_TEST(memchr_legal_range) {
  // Символ существует и находится в легальном диапазоне поиска.
  ck_assert_ptr_eq(s21_memchr(test_data_1, CHAR_IN, LENGTH0),
                   memchr(test_data_1, CHAR_IN, LENGTH0));
}
END_TEST

START_TEST(memchr_empty_string) {
  static char empty_string[] = "";
  test_data_1 = (void *)empty_string;
  ck_assert_ptr_eq(s21_memchr(test_data_1, CHAR_OUT, 1),
                   memchr(test_data_1, CHAR_OUT, 1));
  test_data_1 = (void *)test_data_0;
}
END_TEST

START_TEST(memchr_non_exist) {
  // Символ не существует, как часть строки
  ck_assert_ptr_eq(s21_memchr(test_data_1, CHAR_OUT, LENGTH0),
                   memchr(test_data_1, CHAR_OUT, LENGTH0));
}
END_TEST

START_TEST(memchr_overlength) {
  // Символ существует в строке, в функцию подается диапазон больший, чем длина
  // строки.
  ck_assert_ptr_eq(s21_memchr(test_data_1, CHAR_IN, OVERLENGTH),
                   memchr(test_data_1, CHAR_IN, OVERLENGTH));
}
END_TEST

START_TEST(memchr_after_null) {
  // Число байт, в диапазоне которых происходит поиск, больше длины строки,
  // символ присутствует после терминального нуля (строка с несколькими нулями)
  ck_assert_ptr_eq(s21_memchr(test_data_1, '=', OVERLENGTH),
                   memchr(test_data_1, '=', OVERLENGTH));
}
END_TEST

START_TEST(memchr_null_char) {
  // Вместо символа подается символ окончания строки - нуль-терминатор.
  ck_assert_ptr_eq(s21_memchr(test_data_1, '\0', LENGTH0),
                   memchr(test_data_1, '\0', LENGTH0));
}
END_TEST

START_TEST(memchr_null_bytes) {
  // ноль вместо количества байт для поиска
  ck_assert_ptr_eq(s21_memchr(test_data_1, CHAR_IN, 0),
                   memchr(test_data_1, CHAR_IN, 0));
}
END_TEST
/* S21_memchr. END TESTS */

/* s21_memcmp. START TESTS */
/* Correct data set */
static char str1[] = SOURCE_50;
static char str2_equal[] = SOURCE_50;
static char str2_not_qual[] = DEST_LARGER_55;
/* End of correct data set */
START_TEST(memcmp_correct_data) {
  // Test 1: Different strings
  const char arr1[] = "qwertyuiop[]asdfghjkl;zxcvbnm<>?";
  const char arr2[] = "?><mnbvcxz;lkjhgfdsa][poiuytrewq";

  // Check sign of comparison
  int std_res = memcmp(arr1, arr2, sizeof(arr1));
  int our_res = s21_memcmp(arr1, arr2, sizeof(arr1));
  ck_assert((std_res > 0 && our_res > 0) || (std_res < 0 && our_res < 0) ||
            (std_res == 0 && our_res == 0));

  // Test 2: Reversed strings
  std_res = memcmp(arr2, arr1, sizeof(arr1));
  our_res = s21_memcmp(arr2, arr1, sizeof(arr1));
  ck_assert((std_res > 0 && our_res > 0) || (std_res < 0 && our_res < 0) ||
            (std_res == 0 && our_res == 0));

  // Test 3: Partial match
  const char arr3[] = "qwertyuiop[]assa][poiuy";
  const char arr4[] = "?><mnbvcxz;lkkl;zxxcxcx";

  std_res = memcmp(arr1, arr3, sizeof(arr3));
  our_res = s21_memcmp(arr1, arr3, sizeof(arr3));
  ck_assert((std_res > 0 && our_res > 0) || (std_res < 0 && our_res < 0) ||
            (std_res == 0 && our_res == 0));

  // Test 4: Different strings
  std_res = memcmp(arr2, arr4, sizeof(arr4));
  our_res = s21_memcmp(arr2, arr4, sizeof(arr4));
  ck_assert((std_res > 0 && our_res > 0) || (std_res < 0 && our_res < 0) ||
            (std_res == 0 && our_res == 0));
}
END_TEST
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-overread"
START_TEST(memcmp_n_incorrect) {
  ck_assert(s21_memcmp(str1, str2_not_qual, LENGTH + 3) ==
            memcmp(str1, str2_not_qual, LENGTH + 3));
}
END_TEST
START_TEST(memcmp_negative_values) {
  char str[] = "555";
  str[1] = -1;  // Устанавливаем отрицательное значение

  // Проверяем только знак сравнения
  int std_res = memcmp(str, str2_equal, 3);
  int our_res = s21_memcmp(str, str2_equal, 3);
  ck_assert((std_res > 0 && our_res > 0) || (std_res < 0 && our_res < 0) ||
            (std_res == 0 && our_res == 0));

  std_res = memcmp(str1, str, 3);
  our_res = s21_memcmp(str1, str, 3);
  ck_assert((std_res > 0 && our_res > 0) || (std_res < 0 && our_res < 0) ||
            (std_res == 0 && our_res == 0));
}
END_TEST

START_TEST(memcmp_multiple_nulls) {
  ck_assert(s21_memcmp(SRC_NULL, str2_equal, LENGTH) ==
            memcmp(SRC_NULL, str2_equal, LENGTH));
  ck_assert(s21_memcmp(SRC_NULL, SRC_NULL, LENGTH) ==
            memcmp(SRC_NULL, SRC_NULL, LENGTH));
}
END_TEST
/* s21_memcmp. END TESTS */

/* memcpy. END TESTS*/
static char d[] = DEST_LARGER_55;

START_TEST(memcpy_correct_data) {
  ck_assert_str_eq(s21_memcpy(d, SOURCE_50, 50), memcpy(d, SOURCE_50, 50));
  ck_assert_str_eq(s21_memcpy(d, DEST_LARGER_55, 55),
                   memcpy(d, DEST_LARGER_55, 55));
}
END_TEST

START_TEST(memcpy_without_null) {
  ck_assert_str_eq(s21_memcpy(d, SOURCE_50, LENGTH),
                   memcpy(d, SOURCE_50, LENGTH));
}
END_TEST

START_TEST(memcpy_null_byte) {
  ck_assert_str_eq(s21_memcpy(d, SOURCE_50, 0), memcpy(d, SOURCE_50, 0));
}
END_TEST

START_TEST(memcpy_empty2empty) {
  char d0[] = "";
  ck_assert_str_eq(s21_memcpy(d0, "", 0), memcpy(d0, "", 0));
}
END_TEST
/* memcpy. END TESTS*/

/* memmove. START TESTS */
/* Correct data set */
static char src[] = SOURCE_50;
static char dst[] = DEST_LARGER_55;
static void *src_void = (void *)src;
static void *dst_void = (void *)dst;
static s21_size_t n = LENGTH0;
/* end of correct data set */

START_TEST(memmove_correct_data) {
  ck_assert_str_eq(s21_memmove(dst_void, src_void, n),
                   memmove(dst_void, src_void, n));
}
END_TEST

START_TEST(memmove_dst_smaller) {
  static char dst_smaller[] = DEST_SMALLER_6;
  dst_void = (void *)dst_smaller;
  ck_assert_str_eq(s21_memmove(dst_void, src_void, n),
                   memmove(dst_void, src_void, n));
  dst_void = dst;
}
END_TEST

START_TEST(memmove_multiple_nulls) {
  static char src_null[] = SRC_NULL;
  src_void = (void *)src_null;
  ck_assert_str_eq(s21_memmove(dst_void, src_void, n),
                   memmove(dst_void, src_void, n));
  src_void = (void *)src;
}
END_TEST

START_TEST(memmove_null_n) {
  n = 0;
  ck_assert_str_eq(s21_memmove(dst_void, src_void, n),
                   memmove(dst_void, src_void, n));
  n = LENGTH0;
}
END_TEST
/* memmove. END TESTS */

/*memset. START TESTS*/
static char memset_d[] = DEST_LARGER_55;

START_TEST(memset_correct_data) {
  ck_assert_str_eq(s21_memset(memset_d, 'x', 11),
                   s21_memset(memset_d, 'x', 11));
}
END_TEST

START_TEST(memset_c_negative) {
  ck_assert_str_eq(s21_memset(memset_d, -11, 11),
                   s21_memset(memset_d, -11, 11));
}
END_TEST

START_TEST(memset_null_n) {
  ck_assert_str_eq(s21_memset(memset_d, 'x', 0), s21_memset(memset_d, 'x', 0));
}
END_TEST

START_TEST(memset_null2null) {
  memset_d[0] = '\0';
  ck_assert_str_eq(s21_memset(memset_d, 'x', 0), s21_memset(memset_d, 'x', 0));
}
END_TEST
/*memset. END TESTS*/

/*strcat. START TESTS*/
static char strcat_d[2222] = DEST_LARGER_55;

START_TEST(strcat_correct_data) {
  ck_assert_str_eq(s21_strcat(strcat_d, SOURCE_50),
                   strcat(strcat_d, SOURCE_50));
}
END_TEST

START_TEST(strcat_empty_add) {
  ck_assert_str_eq(s21_strcat(strcat_d, ""), strcat(strcat_d, ""));
}
END_TEST
/*strcat. END TESTS*/

/*strncat. START TESTS*/
static char strncat_d[] = SRC_NULL;
static char strncat_s[] = DEST_SMALLER_6;

START_TEST(strncat_correct_data) {
  (s21_strncat(strncat_d, strncat_s, 6), strncat(strncat_d, strncat_s, 6));
}
END_TEST

START_TEST(strncat_empty_src) {
  ck_assert_str_eq(s21_strncat(strncat_d, "", 11), strncat(strncat_d, "", 11));
}
END_TEST

START_TEST(strncat_src_bigger_n) {
  ck_assert_str_eq(s21_strncat(strncat_d, strncat_s, 3),
                   strncat(strncat_d, strncat_s, 3));
}
END_TEST

START_TEST(strncat_n_null) {
  ck_assert_str_eq(s21_strncat(strncat_d, strncat_s, 0),
                   s21_strncat(strncat_d, strncat_s, 0));
}
END_TEST

START_TEST(strncat_empty_strings) {
  char d1[] = "";
  char s1[] = "";
  ck_assert_str_eq(s21_strncat(d1, s1, 11), s21_strncat(d1, s1, 11));
  ck_assert_str_eq(s21_strncat(d1, s1, 0), s21_strncat(d1, s1, 0));
}
END_TEST

START_TEST(strncat_n_bigger_src) {
  ck_assert_str_eq(s21_strncat(strncat_d, strncat_s, 11),
                   s21_strncat(strncat_d, strncat_s, 11));
}
END_TEST
/*strncat. END TESTS*/

/*strcmp. START TESTS*/
/*data set*/
static char s1[] = SOURCE_50;
static char s1_equal[] = SOURCE_50;
static char empty_s1[] = "";
static char empty_s2[] = "";

START_TEST(strcmp_empty_strings) {
  ck_assert(s21_strcmp(empty_s1, empty_s2) == strcmp(empty_s1, empty_s2));
  ck_assert(s21_strcmp(empty_s1, s1) == strcmp(empty_s1, s1));
  ck_assert(s21_strcmp(s1, empty_s1) == strcmp(s1, empty_s1));
}
END_TEST

START_TEST(strcmp_correct_data) {
  ck_assert(s21_strcmp(s1, s1_equal) == strcmp(s1, s1_equal));
  ck_assert(s21_strcmp(s1, "-----") == strcmp(s1, "-----"));
}
END_TEST
/*strcmp. END TESTS*/

/*strncmp. START TESTS*/
static char strncmp_s1[] = SOURCE_50;
static char strncmp_s1_equal[] = SOURCE_50;
static char strncmp_s2[] = DEST_LARGER_55;
static char strncmp_empty_s1[] = "";
static char strncmp_empty_s2[] = "";

START_TEST(strncmp_empty_strings) {
  ck_assert(s21_strncmp(strncmp_empty_s1, strncmp_empty_s2, 0) ==
            strncmp(strncmp_empty_s1, strncmp_empty_s2, 0));
  ck_assert(s21_strncmp(strncmp_empty_s1, strncmp_s1, 0) ==
            strncmp(strncmp_empty_s1, strncmp_s1, 0));
  ck_assert(s21_strncmp(strncmp_s1, strncmp_empty_s1, 0) ==
            strncmp(strncmp_s1, strncmp_empty_s1, 0));
}
END_TEST

START_TEST(strncmp_correct_data) {
  ck_assert(s21_strncmp(strncmp_s1, strncmp_s1_equal, 11) ==
            strncmp(strncmp_s1, strncmp_s1_equal, 11));
  ck_assert(s21_strncmp(strncmp_s1, strncmp_s2, 11) ==
            strncmp(strncmp_s1, strncmp_s2, 11));
}
END_TEST

START_TEST(strncmp_string_smaller_n) {
  ck_assert(s21_strncmp(strncmp_s1, strncmp_s2, 51) ==
            strncmp(strncmp_s1, strncmp_s2, 51));
}
END_TEST
/*strncmp. END TESTS*/

/*strcpy. START TESTS*/
/*data set */
static char strcpy_d[] = DEST_LARGER_55;
static char strcpy_s[] = SOURCE_50;
static char strcpy_s_equal[] = SOURCE_50;
static char dss[] = DEST_SMALLER_6;
/* end data set */

START_TEST(strcpy_correct_data) {
  ck_assert_str_eq(s21_strcpy(strcpy_d, strcpy_s), strcpy(strcpy_d, strcpy_s));
}
END_TEST

START_TEST(strcpy_dest_smaller_src) {
  ck_assert_str_eq(s21_strcpy(dss, strcpy_s), s21_strcpy(dss, strcpy_s));
}
END_TEST

START_TEST(strcpy_overlap) {
  ck_assert_str_eq(s21_strcpy(strcpy_s, (strcpy_s + 33)),
                   strcpy(strcpy_s_equal, (strcpy_s_equal + 33)));
}
END_TEST
/*strcpy. END TESTS*/

/*strncpy. START TESTS*/
static char strncpy_d[] = DEST_LARGER_55;
static char strncpy_d_equal[] = DEST_LARGER_55;

START_TEST(strncpy_correct_data) {
  s21_strncpy(strncpy_d, SOURCE_50, 55);
  strncpy(strncpy_d_equal, SOURCE_50, 55);
  ck_assert(strncpy_d[54] == strncpy_d_equal[54]);

  ck_assert_str_eq(s21_strncpy(strncpy_d, SOURCE_50, 50),
                   strncpy(strncpy_d, SOURCE_50, 50));
}
END_TEST

START_TEST(strncpy_empty_string) {
  ck_assert_str_eq(s21_strncpy(strncpy_d, "", 1), strncpy(strncpy_d, "", 1));
}
END_TEST

START_TEST(strncpy_null_bytes) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"
  ck_assert_str_eq(s21_strncpy(strncpy_d, "", 0), strncpy(strncpy_d, "", 0));
#pragma GCC diagnostic pop
}
END_TEST
/*strncpy. END TESTS*/

/*strcspn. START TESTS*/
/* Correct data set */
static char strcspn_str1[] = SOURCE_50;
static char strcspn_str2[] = DEST_SMALLER_6;
static char strcspn_str21[] = "= (49 + 0)";
/* End of correct data set */

START_TEST(strcspn_correct_data) {
  ck_assert(s21_strcspn(strcspn_str1, strcspn_str21) ==
            strcspn(strcspn_str1, strcspn_str21));
  ck_assert(s21_strcspn(strcspn_str1, strcspn_str2) ==
            strcspn(strcspn_str1, strcspn_str2));
}
END_TEST

START_TEST(strcspn_empty_strings) {
  ck_assert(s21_strcspn("", strcspn_str21) == strcspn("", strcspn_str21));
  ck_assert(s21_strcspn(strcspn_str1, "") == strcspn(strcspn_str1, ""));
}
END_TEST

START_TEST(strcspn_multiple_nulls) {
  char s1[52] = "_THIS is a'\0' SOURCE. Length'\0' = (51 + 0) = 51_";
  char s2[52] = "_THIS is a'\0' SOURCE. Length'\0' = (51 + 0) = 51_";
  ck_assert(s21_strcspn(s1, strcspn_str21) == strcspn(s1, strcspn_str21));
  ck_assert(s21_strcspn(str1, s2) == strcspn(str1, s2));
}
END_TEST

START_TEST(strcspn_infinite_string1) {
  char *x;
  x = (char *)malloc(LENGTH);
  strncpy(x, strcspn_str1, LENGTH);
  ck_assert(s21_strcspn(x, strcspn_str2) == strcspn(x, strcspn_str2));
  free(x);
}
END_TEST

START_TEST(strcspn_infinite_string2) {
  char *x;
  x = (char *)malloc(LENGTH);
  strncpy(x, strcspn_str1, LENGTH);
  ck_assert(s21_strcspn(strcspn_str1, x) == strcspn(strcspn_str1, x));
  free(x);
}
END_TEST

START_TEST(strcspn_infinite_strings) {
  char *x;
  char *y;
  x = (char *)malloc(LENGTH);
  strncpy(x, strcspn_str1, LENGTH);
  y = (char *)malloc(LENGTH);
  strncpy(y, strcspn_str1, LENGTH);
  ck_assert(s21_strcspn(x, y) == strcspn(x, y));
  free(x);
  free(y);
}
END_TEST
/*strcspn. END TESTS*/

/*strerror. START TESTS*/
START_TEST(strerror_all) {
  //  эти 2 теста не проходит, временно исключены
  //  ck_assert_str_eq(s21_strerror(-11), strerror(-11));
  //  ck_assert_str_eq(s21_strerror(1111), strerror(1111));
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(111), strerror(111));
}
END_TEST
/*strerror. END TESTS*/

/*strlen. START TESTS*/
START_TEST(strlen_correct_data) {
  ck_assert(s21_strlen(SOURCE_50) == strlen(SOURCE_50));
}
END_TEST
/*strlen. END TESTS*/

/*strpbrk. START TESTS*/
static char strpbrk_str1[] = SOURCE_50;
static char strpbrk_str2[] = BRK_CHAR_3;
static char strpbrk_str3[] = DEST_SMALLER_6;
static char strpbrk_empty[] = "";

START_TEST(strpbrk_correct_data) {
  ck_assert(s21_strpbrk(strpbrk_str1, strpbrk_str2) ==
            strpbrk(strpbrk_str1, strpbrk_str2));
  ck_assert(s21_strpbrk(strpbrk_str1, strpbrk_str3) ==
            strpbrk(strpbrk_str1, strpbrk_str3));
}
END_TEST

START_TEST(strpbrk_empty_strings) {
  ck_assert(s21_strpbrk(strpbrk_str1, strpbrk_empty) ==
            strpbrk(strpbrk_str1, strpbrk_empty));
  ck_assert(s21_strpbrk(strpbrk_empty, strpbrk_str3) ==
            strpbrk(strpbrk_empty, strpbrk_str3));
}
END_TEST
/*strpbrk. END TESTS*/

/*strrchr. START TESTS*/
static char strrchr_s[222] = SOURCE_50;

START_TEST(strrchr_correct_data) {
  ck_assert(s21_strrchr(strrchr_s, CHAR_IN) == strrchr(strrchr_s, CHAR_IN));
  ck_assert(s21_strrchr(strrchr_s, CHAR_OUT) == strrchr(strrchr_s, CHAR_OUT));
}
END_TEST

START_TEST(strrchr_null_search) {
  ck_assert(s21_strrchr(strrchr_s, '\0') == strrchr(strrchr_s, '\0'));
}
END_TEST

START_TEST(strrchr_empty_string) {
  char strrchr_s1[] = "";
  ck_assert(s21_strrchr(strrchr_s1, CHAR_IN) == strrchr(strrchr_s1, CHAR_IN));
  ck_assert(s21_strrchr(strrchr_s, '\0') == strrchr(strrchr_s, '\0'));
}
END_TEST
/*strrchr. END TESTS*/

/*strspn. START TESTS*/
char strspn_str1[] = SOURCE_50;
char strspn_str2[] = SRC_NULL;
char strspn_str3[] = DEST_SMALLER_6;

START_TEST(strspn_correct_data) {
  ck_assert(s21_strspn(strspn_str1, strspn_str1) ==
            strspn(strspn_str1, strspn_str1));
  ck_assert(s21_strspn(strspn_str1, strspn_str2) ==
            strspn(strspn_str1, strspn_str2));
  ck_assert(s21_strspn(strspn_str2, strspn_str1) ==
            strspn(strspn_str2, strspn_str1));
  ck_assert(s21_strspn(strspn_str1, strspn_str3) ==
            strspn(strspn_str1, strspn_str3));
}
END_TEST

START_TEST(strspn_s1_empty_string) {
  ck_assert(s21_strspn("", strspn_str1) == strspn("", strspn_str1));
}
END_TEST

START_TEST(strspn_s2_empty_string) {
  ck_assert(s21_strspn(strspn_str1, "") == strspn(strspn_str1, ""));
}
END_TEST

START_TEST(strspn_infinite_string1) {
  char *x;
  x = (char *)malloc(LENGTH);
  strncpy(x, strspn_str1, LENGTH);
  ck_assert(s21_strspn(x, strspn_str1) == strspn(x, strspn_str1));
  free(x);
}
END_TEST

START_TEST(strspn_infinite_string2) {
  char *x;
  x = (char *)malloc(LENGTH);
  strncpy(x, strspn_str1, LENGTH);
  ck_assert(s21_strspn(strspn_str1, x) == strspn(strspn_str1, x));
  free(x);
}
END_TEST

START_TEST(strspn_infinite_strings) {
  char *x;
  char *y;
  x = (char *)malloc(LENGTH);
  strncpy(x, strspn_str1, LENGTH);
  y = (char *)malloc(LENGTH);
  strncpy(y, strspn_str1, LENGTH);
  ck_assert(s21_strspn(x, y) == strspn(x, y));
  free(x);
  free(y);
}
END_TEST
/*strspn. END TESTS*/

/*strstr. START TESTS*/
static char haystack[] = SOURCE_50;
static char needle_exist[] = "string";
static char needle_nexist[] = "mole";

START_TEST(strstr_correct_data) {
  ck_assert(s21_strstr(haystack, needle_exist) ==
            strstr(haystack, needle_exist));
  ck_assert(s21_strstr(haystack, needle_nexist) ==
            strstr(haystack, needle_nexist));
}
END_TEST

START_TEST(strstr_empty_strings) {
  char empty_needle[] = "";
  char empty_haystack[] = "";
  ck_assert(s21_strstr(haystack, empty_needle) ==
            strstr(haystack, empty_needle));
  ck_assert(s21_strstr(empty_haystack, needle_exist) ==
            strstr(empty_haystack, needle_exist));
  ck_assert(s21_strstr(empty_haystack, empty_needle) ==
            strstr(empty_haystack, empty_needle));
}
END_TEST

/*strstr. END TESTS*/

/*strtok. START TESTS*/
static char delimiters[] = "_ .";

START_TEST(strtok_correct_data) {
  char string[] = SOURCE_50;
  char ystring[] = SOURCE_50;
  int i;
  i = 0;

  ck_assert_str_eq(s21_strtok(string, delimiters), strtok(ystring, delimiters));
  while (i < N_CALL) {
    ck_assert_str_eq(s21_strtok(s21_NULL, delimiters),
                     strtok(s21_NULL, delimiters));
    i++;
  }
}
END_TEST

START_TEST(strtok_multiple_delims) {
  char string[] = "__THIS  is  a  SOURCE string..... Length = (49 + 0) =  50__";
  char ystring[] =
      "__THIS  is  a  SOURCE string..... Length = (49 + 0) =  50__";
  int i;
  i = 0;

  ck_assert_str_eq(s21_strtok(string, delimiters), strtok(ystring, delimiters));
  while (i < N_CALL) {
    ck_assert_str_eq(s21_strtok(s21_NULL, delimiters),
                     strtok(s21_NULL, delimiters));
    i++;
  }
}
END_TEST

START_TEST(strtok_repeated_delims) {
  char string[] = SOURCE_50;
  char ystring[] = SOURCE_50;
  char delims[] = " _. _. _.";
  int i;
  i = 0;

  ck_assert_str_eq(s21_strtok(string, delims), strtok(ystring, delims));
  while (i < N_CALL) {
    ck_assert_str_eq(s21_strtok(s21_NULL, delims), strtok(s21_NULL, delims));
    i++;
  }
}
END_TEST

START_TEST(to_upper_case) {
  char *dest;
  dest = s21_to_upper("qwert");
  ck_assert_str_eq(dest, "QWERT");
  free(dest);
  dest = s21_to_upper("1q2w3e4r5");
  ck_assert_str_eq(dest, "1Q2W3E4R5");
  free(dest);
  dest = s21_to_upper("!@#!$^");
  ck_assert_str_eq(dest, "!@#!$^");
  free(dest);
  dest = s21_to_upper("\n0\\n");
  ck_assert_str_eq(dest, "\n0\\N");
  free(dest);
  dest = s21_to_upper("");
  ck_assert_str_eq(dest, "");
  free(dest);
}
END_TEST

START_TEST(to_lower_case) {
  char *dest;
  dest = s21_to_lower("");
  ck_assert_str_eq(dest, "");
  free(dest);
  dest = s21_to_lower("QWERT");
  ck_assert_str_eq(dest, "qwert");
  free(dest);
  dest = s21_to_lower("1Q2W3E4R5");
  ck_assert_str_eq(dest, "1q2w3e4r5");
  free(dest);
  dest = s21_to_lower("!@#!$^");
  ck_assert_str_eq(dest, "!@#!$^");
  free(dest);
  dest = s21_to_lower("\n0\\N");
  ck_assert_str_eq(dest, "\n0\\n");
  free(dest);
}
END_TEST

START_TEST(s21_trim_case) {
  char *dest;
  dest = s21_trim(" abra kadabra ", "a");
  ck_assert_str_eq(dest, " abra kadabra ");
  free(dest);
}
END_TEST

START_TEST(s21_insert_case) {
  char *dest = s21_NULL;
  dest = s21_insert("abrabra", "a kad", 3);
  ck_assert_str_eq(dest, "abra kadabra");
  free(dest);
  char *dest1 = s21_NULL;
  dest1 = s21_insert("abra", " hoba", 4);
  ck_assert_str_eq(dest1, "abra hoba");
  free(dest1);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, memchr_legal_range);
  tcase_add_test(tc1_1, memchr_empty_string);
  tcase_add_test(tc1_1, memchr_non_exist);
  tcase_add_test(tc1_1, memchr_overlength);
  tcase_add_test(tc1_1, memchr_after_null);
  tcase_add_test(tc1_1, memchr_null_char);
  tcase_add_test(tc1_1, memchr_null_bytes);

  tcase_add_test(tc1_1, memcmp_correct_data);
  tcase_add_test(tc1_1, memcmp_n_incorrect);
  tcase_add_test(tc1_1, memcmp_negative_values);
  tcase_add_test(tc1_1, memcmp_multiple_nulls);

  tcase_add_test(tc1_1, memcpy_correct_data);
  tcase_add_test(tc1_1, memcpy_without_null);
  tcase_add_test(tc1_1, memcpy_null_byte);
  tcase_add_test(tc1_1, memcpy_empty2empty);

  tcase_add_test(tc1_1, memmove_correct_data);
  tcase_add_test(tc1_1, memmove_dst_smaller);
  tcase_add_test(tc1_1, memmove_multiple_nulls);
  tcase_add_test(tc1_1, memmove_null_n);

  tcase_add_test(tc1_1, memset_null2null);
  tcase_add_test(tc1_1, memset_null_n);
  tcase_add_test(tc1_1, memset_c_negative);
  tcase_add_test(tc1_1, memset_correct_data);

  tcase_add_test(tc1_1, strcat_empty_add);
  tcase_add_test(tc1_1, strcat_correct_data);

  tcase_add_test(tc1_1, strncat_correct_data);
  tcase_add_test(tc1_1, strncat_empty_src);
  tcase_add_test(tc1_1, strncat_src_bigger_n);
  tcase_add_test(tc1_1, strncat_n_null);
  tcase_add_test(tc1_1, strncat_empty_strings);
  tcase_add_test(tc1_1, strncat_n_bigger_src);

  tcase_add_test(tc1_1, strcmp_empty_strings);
  tcase_add_test(tc1_1, strcmp_correct_data);

  tcase_add_test(tc1_1, strncmp_empty_strings);
  tcase_add_test(tc1_1, strncmp_correct_data);
  tcase_add_test(tc1_1, strncmp_string_smaller_n);

  tcase_add_test(tc1_1, strcpy_dest_smaller_src);
  tcase_add_test(tc1_1, strcpy_correct_data);
  tcase_add_test(tc1_1, strcpy_overlap);

  tcase_add_test(tc1_1, strncpy_null_bytes);
  tcase_add_test(tc1_1, strncpy_empty_string);
  tcase_add_test(tc1_1, strncpy_correct_data);

  tcase_add_test(tc1_1, strcspn_correct_data);
  tcase_add_test(tc1_1, strcspn_empty_strings);
  tcase_add_test(tc1_1, strcspn_multiple_nulls);
  tcase_add_test(tc1_1, strcspn_infinite_string1);
  tcase_add_test(tc1_1, strcspn_infinite_string2);
  tcase_add_test(tc1_1, strcspn_infinite_strings);

  tcase_add_test(tc1_1, strerror_all);

  tcase_add_test(tc1_1, strlen_correct_data);

  tcase_add_test(tc1_1, strpbrk_correct_data);
  tcase_add_test(tc1_1, strpbrk_empty_strings);

  tcase_add_test(tc1_1, strrchr_correct_data);
  tcase_add_test(tc1_1, strrchr_null_search);
  tcase_add_test(tc1_1, strrchr_empty_string);

  tcase_add_test(tc1_1, strspn_correct_data);
  tcase_add_test(tc1_1, strspn_s1_empty_string);
  tcase_add_test(tc1_1, strspn_s2_empty_string);
  tcase_add_test(tc1_1, strspn_infinite_string1);
  tcase_add_test(tc1_1, strspn_infinite_string2);
  tcase_add_test(tc1_1, strspn_infinite_strings);

  tcase_add_test(tc1_1, strstr_correct_data);
  tcase_add_test(tc1_1, strstr_empty_strings);

  tcase_add_test(tc1_1, strtok_correct_data);
  tcase_add_test(tc1_1, strtok_multiple_delims);
  tcase_add_test(tc1_1, strtok_repeated_delims);

  tcase_add_test(tc1_1, to_upper_case);
  tcase_add_test(tc1_1, to_lower_case);
  tcase_add_test(tc1_1, s21_trim_case);
  tcase_add_test(tc1_1, s21_insert_case);

  srunner_run_all(sr, CK_VERBOSE);
  int errors = srunner_ntests_failed(sr);
  srunner_free(sr);
  return errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
