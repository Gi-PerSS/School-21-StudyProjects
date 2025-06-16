#include "s21_cat.h"

#include <stdio.h>
#include <string.h>

#define LINUX_FLAG_ERROR_MSG \
  "s21_cat: invalid option -- '%c'\nTry 'cat --help' for more information.\n"
#define LINUX_LONGFLAG_ERROR_MSG                                  \
  "s21_cat: unrecognized option '%s'\nTry 'cat --help' for more " \
  "information.\n"
#define LINUX_FILE_ERROR_MSG "s21_cat: %s: No such file or directory\n"
#ifdef __APPLE__
#define IS_MAC 1
#else
#define IS_MAC 0
#endif

static const char kCatLegalFlags[] = "bEvenstT";

static flag_case flags_case = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int actual_byte;  // эта переменная используется функцией-принтером и во
                         // всех подфункциях флагов, для простоты глобальная.
static int last_printed_char = '\n';  // используется в 2 функциях
static int line_number = 1;           // то же

void NoSuchfileMessager(char *filename) {
  fprintf(stderr, LINUX_FILE_ERROR_MSG, filename);
}

/*
FILE *FilePointerCreator(char *filename) {
  FILE *file_to_print_pointer = fopen(filename, "rb");

  if (!file_to_print_pointer)  // если указатель NULL
    NoSuchfileMessager(filename);

  return file_to_print_pointer;
}
*/
int isFlagsOk(main_data main_data) {
  // здесь происходит проверка флагов и вызов сообщения об ошибке при
  // необходимости.

  unsigned char actual_char;
  flags_case.is_flags_ok = 1;
  for (int i = 1; (main_data.argc > 1) && (*main_data.argv[i] == '-');
       i++) {  // проверка корректности флагов
    if (*(main_data.argv[i] + 1) == '-') {  // если длинный флаг
      if (strcmp(main_data.argv[i], "--number-nonblank")) {
        if (strcmp(main_data.argv[i], "--squeeze-blank")) {
          if (strcmp(main_data.argv[i], "--number")) {
            fprintf(stderr, LINUX_LONGFLAG_ERROR_MSG,
                    main_data.argv[i]);  // linux error
            flags_case.is_flags_ok = 0;
          }
        }
      }
    } else {  // если короткий
      for (int j = 1; *(main_data.argv[i] + j); j++) {
        actual_char = *(main_data.argv[i] + j);
        if (!strchr(kCatLegalFlags, actual_char)) {
          fprintf(stderr, LINUX_FLAG_ERROR_MSG,
                  actual_char);  // linux error
          flags_case.is_flags_ok = 0;
          break;
        }
      }
    }

    if (flags_case.is_flags_ok == 0) break;
  }

  return flags_case.is_flags_ok;
}

int isFlagsEnable(main_data main_data) {
  if ((main_data.argc > 1) && (*main_data.argv[1] == '-')) {
    return 1;
  } else {
    flags_case.is_empty_flags = 1;
    return 0;
  }
}

int isFilenamesEnable(main_data main_data) {
  int filenames_counter = 0;

  for (int i = 1; i < main_data.argc; i++)
    if (*main_data.argv[i] != '-') filenames_counter++;

  return filenames_counter;
}

void FlagExtractor(main_data main_data) {
  // предварительно, подразумевается, что все флаги находятся в первом аргументе
  // после знака минус. Далее, переделаю под реальное положение вещей.
  // "bEvenstT"
  //  int actual_byte;
  for (int i = 1; (main_data.argc > 1) && (*main_data.argv[i] == '-'); i++) {
    for (int line_offset = 1; *(main_data.argv[i] + line_offset);
         line_offset++) {
      actual_byte = *(main_data.argv[i] + line_offset);
      if (*(main_data.argv[i] + 1) == '-') {  // проверка на длинный флаг
        if (!strcmp(main_data.argv[i], "--number-nonblank")) flags_case.b = 1;
        if (!strcmp(main_data.argv[i], "--squeeze-blank")) flags_case.s = 1;
        if (!strcmp(main_data.argv[i], "--number")) flags_case.n = 1;
        break;
      } else {
        switch (actual_byte) {
          case 'b':
            flags_case.b = 1;
            break;
          case 'E':
            flags_case.E = 1;
            break;
          case 'v':
            flags_case.v = 1;
            break;
          case 'e':
            flags_case.e = 1;
            break;
          case 'n':
            flags_case.n = 1;
            break;
          case 's':
            flags_case.s = 1;
            break;
          case 't':
            flags_case.t = 1;
            break;
          case 'T':
            flags_case.T = 1;
            break;
        }
      }
    }
  }

  if ((flags_case.b) && (flags_case.n)) flags_case.n = 0;
}

// установка начального номера строки на 1, при вызове на печать нового файла.
void SetVariablesForNewFile(void) {
  // line_number = 1;
  last_printed_char = '\n';
  actual_byte = '\0';
}

void FlagIs_n(unsigned char *processed_substring, size_t *bytes2print) {
  // на маке нумерация начинается заново
  // для каждого файла

  unsigned char t_in[22] = "";
  unsigned char t_out[22] = "";
  memset(t_in, '\0', 22);
  memset(t_out, '\0', 22);
  memcpy(t_in, processed_substring, *bytes2print);

  // проверка на исключение строк из печати
  if ((last_printed_char == '\n') && (*bytes2print != 0)) {
    sprintf((char *)t_out, "%6d\t", line_number++);
    memcpy(processed_substring, t_out, strlen((char *)t_out));
    memcpy(processed_substring + strlen((char *)t_out), t_in, *bytes2print);
    *bytes2print = *bytes2print + strlen((char *)t_out);
  }
  last_printed_char = actual_byte;
}

void FlagIs_b(unsigned char *processed_substring, size_t *bytes2print) {
  unsigned char tmp_in[22] = "";
  unsigned char tmp_out[22] = "";
  memset(tmp_in, '\0', 22);
  memset(tmp_out, '\0', 22);
  memcpy(tmp_in, processed_substring, *bytes2print);

  if ((last_printed_char == '\n') && (actual_byte != '\n')) {
    sprintf((char *)tmp_out, "%6d\t", line_number++);
    memcpy(processed_substring, tmp_out, strlen((char *)tmp_out));
    memcpy(processed_substring + strlen((char *)tmp_out), tmp_in, *bytes2print);
    *bytes2print = *bytes2print + strlen((char *)tmp_out);
  }
  last_printed_char = actual_byte;
}

void FlagIs_s(size_t *bytes2print) {
  static int n_in_row = 2;

  // Все переводы строки, начиная с третьего включительно выбрасываются из
  // печати.

  if (actual_byte == '\n') {
    if (n_in_row > 2) {
      *bytes2print = 0;
      n_in_row++;
    } else {
      n_in_row++;
    }
  } else {
    n_in_row = 1;
  }
}

void FlagIs_E(unsigned char *processed_substring, size_t *bytes2print) {
  if (actual_byte == '\n') {
    memcpy(processed_substring, "$\n", 2);
    *bytes2print = 2;
  }
}

void FlagIs_T(unsigned char *processed_substring, size_t *bytes2print) {
  if (actual_byte == '\t') {
    memcpy(processed_substring, "^I", 2);
    *bytes2print = 2;
  }
}

void LinuxNonprintableSymbols(unsigned char *processed_substring,
                              size_t *bytes2print) {
  // При первом вызове формируется массив строк для подмены непечатных символов
  // соответствующими кодами.
  static char nonprintable_table[256][11] = {{0, 0}};

  if (!nonprintable_table[0][0]) {
    for (int i = 0; i < 256; i++) memset(nonprintable_table[i], '\0', 11);
    // заполнение массива префиксами
    for (int i = 0; i < 32; i++) nonprintable_table[i][0] = '^';
    nonprintable_table[127][0] = '^';
    for (int i = 128; i < 160; i++) strcpy(nonprintable_table[i], "M-");
    for (int i = 160; i <= 255; i++) strcpy(nonprintable_table[i], "M-");

    // заполнение массива
    strcat(nonprintable_table[0], "@");
    for (int i = 1; i < 27; i++)
      memset(nonprintable_table[i] + 1, i + 64,
             1);  // смещение к бувам начиная с 'A' с кодом 65
    // 9 - '\t', 10 - '\n'
    strcpy(nonprintable_table[9], "\t");
    strcpy(nonprintable_table[10], "\n");

    strcat(nonprintable_table[27], "[");
    strcat(nonprintable_table[28], "\\");
    strcat(nonprintable_table[29], "]");
    strcat(nonprintable_table[30], "^");
    strcat(nonprintable_table[31], "_");

    for (int i = 32; i < 127; i++) nonprintable_table[i][0] = i;

    strcat(nonprintable_table[127], "?");

    for (int i = 128; i < 256; i++)
      strcat(nonprintable_table[i], nonprintable_table[i - 128]);

    strcpy(nonprintable_table[9 + 128], "M-^I");
    strcpy(nonprintable_table[10 + 128], "M-^J");
  }

  // не трогаем строку, если печатается перевод строки или таб, это нужно для
  // корректной работы соответствующих подфункций.
  if ((actual_byte != '\n') && (actual_byte != '\t')) {
    *bytes2print = strlen(nonprintable_table[actual_byte]);
    memcpy(processed_substring, nonprintable_table[actual_byte], *bytes2print);
  }
}
void MacNonprintableSymbols(unsigned char *processed_substring,
                            size_t *bytes2print) {
  // При первом вызове формируется массив строк для подмены непечатных символов
  // соответствующими кодами.
  static char nonprintable_table[256][11] = {{94, 64, 0},
                                             {94, 65, 0},
                                             {94, 66, 0},
                                             {94, 67, 0},
                                             {94, 68, 0},
                                             {94, 69, 0},
                                             {94, 70, 0},
                                             {94, 71, 0},
                                             {94, 72, 0},
                                             {9, 0},
                                             {46, 0},
                                             {94, 75, 0},
                                             {94, 76, 0},
                                             {94, 77, 0},
                                             {94, 78, 0},
                                             {94, 79, 0},
                                             {94, 80, 0},
                                             {94, 81, 0},
                                             {94, 82, 0},
                                             {94, 83, 0},
                                             {94, 84, 0},
                                             {94, 85, 0},
                                             {94, 86, 0},
                                             {94, 87, 0},
                                             {94, 88, 0},
                                             {94, 89, 0},
                                             {94, 90, 0},
                                             {94, 91, 0},
                                             {94, 92, 0},
                                             {94, 93, 0},
                                             {94, 94, 0},
                                             {94, 95, 0},
                                             {32, 0},
                                             {33, 0},
                                             {34, 0},
                                             {35, 0},
                                             {36, 0},
                                             {37, 0},
                                             {38, 0},
                                             {39, 0},
                                             {40, 0},
                                             {41, 0},
                                             {42, 0},
                                             {43, 0},
                                             {44, 0},
                                             {45, 0},
                                             {46, 0},
                                             {47, 0},
                                             {48, 0},
                                             {49, 0},
                                             {50, 0},
                                             {51, 0},
                                             {52, 0},
                                             {53, 0},
                                             {54, 0},
                                             {55, 0},
                                             {56, 0},
                                             {57, 0},
                                             {58, 0},
                                             {59, 0},
                                             {60, 0},
                                             {61, 0},
                                             {62, 0},
                                             {63, 0},
                                             {64, 0},
                                             {65, 0},
                                             {66, 0},
                                             {67, 0},
                                             {68, 0},
                                             {69, 0},
                                             {70, 0},
                                             {71, 0},
                                             {72, 0},
                                             {73, 0},
                                             {74, 0},
                                             {75, 0},
                                             {76, 0},
                                             {77, 0},
                                             {78, 0},
                                             {79, 0},
                                             {80, 0},
                                             {81, 0},
                                             {82, 0},
                                             {83, 0},
                                             {84, 0},
                                             {85, 0},
                                             {86, 0},
                                             {87, 0},
                                             {88, 0},
                                             {89, 0},
                                             {90, 0},
                                             {91, 0},
                                             {92, 0},
                                             {93, 0},
                                             {94, 0},
                                             {95, 0},
                                             {96, 0},
                                             {97, 0},
                                             {98, 0},
                                             {99, 0},
                                             {100, 0},
                                             {101, 0},
                                             {102, 0},
                                             {103, 0},
                                             {104, 0},
                                             {105, 0},
                                             {106, 0},
                                             {107, 0},
                                             {108, 0},
                                             {109, 0},
                                             {110, 0},
                                             {111, 0},
                                             {112, 0},
                                             {113, 0},
                                             {114, 0},
                                             {115, 0},
                                             {116, 0},
                                             {117, 0},
                                             {118, 0},
                                             {119, 0},
                                             {120, 0},
                                             {121, 0},
                                             {122, 0},
                                             {123, 0},
                                             {124, 0},
                                             {125, 0},
                                             {126, 0},
                                             {94, 63, 0},
                                             {77, 45, 94, 64, 0},
                                             {77, 45, 94, 65, 0},
                                             {77, 45, 94, 66, 0},
                                             {77, 45, 94, 67, 0},
                                             {77, 45, 94, 68, 0},
                                             {77, 45, 94, 69, 0},
                                             {77, 45, 94, 70, 0},
                                             {77, 45, 94, 71, 0},
                                             {77, 45, 94, 72, 0},
                                             {77, 45, 94, 73, 0},
                                             {77, 45, 94, 74, 0},
                                             {77, 45, 94, 75, 0},
                                             {77, 45, 94, 76, 0},
                                             {77, 45, 94, 77, 0},
                                             {77, 45, 94, 78, 0},
                                             {77, 45, 94, 79, 0},
                                             {77, 45, 94, 80, 0},
                                             {77, 45, 94, 81, 0},
                                             {77, 45, 94, 82, 0},
                                             {77, 45, 94, 83, 0},
                                             {77, 45, 94, 84, 0},
                                             {77, 45, 94, 85, 0},
                                             {77, 45, 94, 86, 0},
                                             {77, 45, 94, 87, 0},
                                             {77, 45, 94, 88, 0},
                                             {77, 45, 94, 89, 0},
                                             {77, 45, 94, 90, 0},
                                             {77, 45, 94, 91, 0},
                                             {77, 45, 94, 92, 0},
                                             {77, 45, 94, 93, 0},
                                             {77, 45, 94, 94, 0},
                                             {77, 45, 94, 95, 0},
                                             {-96, 0},
                                             {-95, 0},
                                             {-94, 0},
                                             {-93, 0},
                                             {-92, 0},
                                             {-91, 0},
                                             {-90, 0},
                                             {-89, 0},
                                             {-88, 0},
                                             {-87, 0},
                                             {-86, 0},
                                             {-85, 0},
                                             {-84, 0},
                                             {-83, 0},
                                             {-82, 0},
                                             {-81, 0},
                                             {-80, 0},
                                             {-79, 0},
                                             {-78, 0},
                                             {-77, 0},
                                             {-76, 0},
                                             {-75, 0},
                                             {-74, 0},
                                             {-73, 0},
                                             {-72, 0},
                                             {-71, 0},
                                             {-70, 0},
                                             {-69, 0},
                                             {-68, 0},
                                             {-67, 0},
                                             {-66, 0},
                                             {-65, 0},
                                             {-64, 0},
                                             {-63, 0},
                                             {-62, 0},
                                             {-61, 0},
                                             {-60, 0},
                                             {-59, 0},
                                             {-58, 0},
                                             {-57, 0},
                                             {-56, 0},
                                             {-55, 0},
                                             {-54, 0},
                                             {-53, 0},
                                             {-52, 0},
                                             {-51, 0},
                                             {-50, 0},
                                             {-49, 0},
                                             {-48, 0},
                                             {-47, 0},
                                             {-46, 0},
                                             {-45, 0},
                                             {-44, 0},
                                             {-43, 0},
                                             {-42, 0},
                                             {-41, 0},
                                             {-40, 0},
                                             {-39, 0},
                                             {-38, 0},
                                             {-37, 0},
                                             {-36, 0},
                                             {-35, 0},
                                             {-34, 0},
                                             {-33, 0},
                                             {-32, 0},
                                             {-31, 0},
                                             {-30, 0},
                                             {-29, 0},
                                             {-28, 0},
                                             {-27, 0},
                                             {-26, 0},
                                             {-25, 0},
                                             {-24, 0},
                                             {-23, 0},
                                             {-22, 0},
                                             {-21, 0},
                                             {-20, 0},
                                             {-19, 0},
                                             {-18, 0},
                                             {-17, 0},
                                             {-16, 0},
                                             {-15, 0},
                                             {-14, 0},
                                             {-13, 0},
                                             {-12, 0},
                                             {-11, 0},
                                             {-10, 0},
                                             {-9, 0},
                                             {-8, 0},
                                             {-7, 0},
                                             {-6, 0},
                                             {-5, 0},
                                             {-4, 0},
                                             {-3, 0},
                                             {-2, 0}};

  nonprintable_table[10][0] = '\n';

  // не трогаем строку, если печатается перевод строки или таб, это нужно для
  // корректной работы соответствующих подфункций.
  if ((actual_byte != '\n') && (actual_byte != '\t')) {
    *bytes2print = strlen(nonprintable_table[actual_byte]);
    memcpy(processed_substring, nonprintable_table[actual_byte], *bytes2print);
  }
}

void FlagIs_v(unsigned char *processed_substring, size_t *bytes2print) {
  if (IS_MAC)
    MacNonprintableSymbols(processed_substring, bytes2print);
  else
    LinuxNonprintableSymbols(processed_substring, bytes2print);
}

void FlagIs_e(unsigned char *processed_substring, size_t *bytes2print) {
  FlagIs_v(processed_substring, bytes2print);
  FlagIs_E(processed_substring, bytes2print);
}

void FlagIs_t(unsigned char *processed_substring, size_t *bytes2print) {
  FlagIs_v(processed_substring, bytes2print);
  FlagIs_T(processed_substring, bytes2print);
}

int file_printer(main_data main_data) {
  int return_value = 0;
  int is_filenames_started = 0;
  SetVariablesForNewFile();
  for (int i = 1; i < main_data.argc; i++) {
    if (*main_data.argv[i] != '-') is_filenames_started = 1;
    if ((*main_data.argv[i] == '-') && (!is_filenames_started)) continue;

    char *filename = main_data.argv[i];
    FILE *file_pointer = FilePointerCreator(filename);
    if (!file_pointer)
      continue;
    else if (IS_MAC)
      SetVariablesForNewFile();

    // настолько большой размер массива под один символ, ради возможности
    // печатать очень большие файлы с номерами строк.
    unsigned char processed_substring[22];
    memset(processed_substring, '\0', 22);

    actual_byte = fgetc(file_pointer);
    *processed_substring = (unsigned char)actual_byte;
    size_t bytes2print = sizeof(unsigned char);
    while (actual_byte != EOF) {
      if (flags_case.v) FlagIs_v(processed_substring, &bytes2print);
      if (flags_case.E) FlagIs_E(processed_substring, &bytes2print);
      if (flags_case.T) FlagIs_T(processed_substring, &bytes2print);

      if (flags_case.e) FlagIs_e(processed_substring, &bytes2print);
      if (flags_case.t) FlagIs_t(processed_substring, &bytes2print);
      if (flags_case.s) FlagIs_s(&bytes2print);
      if (flags_case.b) FlagIs_b(processed_substring, &bytes2print);
      if (flags_case.n) FlagIs_n(processed_substring, &bytes2print);
      fwrite(processed_substring, sizeof(unsigned char), bytes2print, stdout);

      actual_byte = fgetc(file_pointer);
      memset(processed_substring, '\0', 22);
      *processed_substring = (unsigned char)actual_byte;
      bytes2print = sizeof(unsigned char);
    }

    fclose(file_pointer);
  }

  return return_value;
}

int main(int argc, char *argv[]) {
  main_data main_data;
  main_data.argc = argc;
  main_data.argv = argv;
  int return_code = 0;

  if (isFilenamesEnable(main_data))
    if (isFlagsEnable(main_data))
      if (isFlagsOk(main_data)) FlagExtractor(main_data);

  if ((flags_case.is_empty_flags) || (flags_case.is_flags_ok))
    return_code = file_printer(main_data);
  else
    return_code = 1;

  return return_code;
}
