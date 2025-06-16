#include "../cat/s21_cat.h"
#include "../common/common.h"
#include "../grep/s21_grep.h"

FILE *FilePointerCreator(char *filename) {
  FILE *file_to_print_pointer = fopen(filename, "rb");

  if (!file_to_print_pointer)  // если указатель NULL
    NoSuchfileMessager(filename);

  return file_to_print_pointer;
}
