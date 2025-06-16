#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "../common/common.h"
#define LINENUMBER_LENGTH 22
#define FILENAME_LENGTH \
  255  // максимальная длина имени файла в unix системе 255
/*
typedef struct main_data {
  int argc;
  char **argv;
} main_data;
*/
typedef struct grep_data {
  int is_skip_ov;
  int is_without_flags;
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  char *regex_list;
  char *filenames_list;
  int o;
  char *first_nonflag_pointer;
  int first_nonflag_index;
} GrepData;

typedef struct regex_data {
  char *current_regex;
  char *current_line;
  int regex_compilation_flag;
  size_t current_line_length;
  regmatch_t *matched_expression_coordinates;
} RegexCompilationData;

typedef struct printers_data {
  char filename_prefix[FILENAME_LENGTH + 3];
  char linenumber_prefix[FILENAME_LENGTH];
  char *output_line;
  char *current_line;
  int is_regex_match;
} PrintersData;

typedef struct o_flag_data {
  size_t arrays_last_index;
  char *regex_match;
  size_t match_position;  // смещение от начала строки совпадения
  size_t match_length;
  char filename_prefix[FILENAME_LENGTH + 3];
  char linenumber_prefix[FILENAME_LENGTH];
} O_FlagData;

void OrderOfOccurrenceSorter(O_FlagData *match_array);
// void MatchsArrayPrinter(O_FlagData *matchs_array, PrintersData
// printers_data);
void MatchsArrayPrinter(O_FlagData *matchs_array);
int IsInverseMatch(RegexCompilationData regex_data, char *buffer_for_strtok);
O_FlagData *MatchsArrayCreator(O_FlagData data2write,
                               int do_I_need_to_free_memory);
O_FlagData *O_FlagDataMemoryReAllocator(O_FlagData *memory_area_address,
                                        int desired_memory_size);
O_FlagData *O_FlagDataMemoryCAllocator(size_t desired_memory_size);
void MatchsSaver(RegexCompilationData regex_data,
                 PrintersData printers_datapack, size_t match_overall_offset);
int IsRegexMatch(RegexCompilationData regex_data);
char *CharMemoryReAllocator(char *memory_area_address, int desired_memory_size);
char *CharMemoryCAllocator(int desired_memory_size);
void NoSuchfileMessager(char *filename);
FILE *FilePointerCreator(char *filename);
char *RegexSaver(char *current_regex, int do_I_need_to_free_memory);
void GrepArgumentsExtractor(int argc, char *argv[]);
void FileNameExtractor(main_data main_data, char *filename_holder,
                       int current_filename_index);
void ResultsPrinter(PrintersData printers_data);

void FlagsDispatcher(main_data main_data);
#endif  // SRC_GREP_S21_GREP_H_
