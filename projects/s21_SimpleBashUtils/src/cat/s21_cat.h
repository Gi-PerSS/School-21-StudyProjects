#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

#include "../common/common.h"
#define LINUX_FLAG_ERROR_MSG \
  "s21_cat: invalid option -- '%c'\nTry 'cat --help' for more information.\n"
#define LINUX_LONGFLAG_ERROR_MSG                                  \
  "s21_cat: unrecognized option '%s'\nTry 'cat --help' for more " \
  "information.\n"
#define LINUX_FILE_ERROR_MSG "s21_cat: %s: No such file or directory\n"

/*
typedef struct main_data {
  int argc;
  char **argv;
} main_data;
*/
typedef struct flag_case {
  int is_flags_ok;
  int is_empty_flags;
  int b;
  int E;
  int v;
  int e;
  int n;
  int s;
  int t;
  int T;
} flag_case;

void NoSuchfileMessager(char *filename);

FILE *FilePointerCreator(char *filename);

int isFlagsOk(main_data main_data);

int isFlagsEnable(main_data main_data);

int isFilenamesEnable(main_data main_data);

void FlagExtractor(main_data main_data);

void SetVariablesForNewFile(void);

void FlagIs_n(unsigned char *processed_substring, size_t *bytes2print);

void FlagIs_b(unsigned char *processed_substring, size_t *bytes2print);

void FlagIs_s(size_t *bytes2print);

void FlagIs_E(unsigned char *processed_substring, size_t *bytes2print);

void FlagIs_T(unsigned char *processed_substring, size_t *bytes2print);

void NonprintableSymbols(unsigned char *processed_substring,
                         size_t *bytes2print);

void FlagIs_v(unsigned char *processed_substring, size_t *bytes2print);

void FlagIs_e(unsigned char *processed_substring, size_t *bytes2print);

void FlagIs_t(unsigned char *processed_substring, size_t *bytes2print);

int file_printer(main_data main_data);

#endif  // SRC_CAT_S21_CAT_H_
