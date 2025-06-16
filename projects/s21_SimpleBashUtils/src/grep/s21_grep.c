#include "s21_grep.h"

#include "global.h"

O_FlagData *matchs_array = NULL;

int main(int argc, char *argv[]) {
  // debugg_print_main_data();
  main_data main_data;

  main_data.argc = argc;
  main_data.argv = argv;

  if (argc == 1) {
    printf(
        "usage: ./s21_grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
        "[-C[num]]\n[-e pattern] [-f file] [--binary-files=value] "
        "[--color=when]\n[--context[=num]] [--directories=action] [--label] "
        "[--line-buffered]\n[--null] [pattern] [file ...]\n");
  } else {
    GrepArgumentsExtractor(argc, argv);
    FlagsDispatcher(main_data);
    RegexSaver("", 1);  // освобождение памяти.
  }

  return 0;
}

void FlagsDispatcher(main_data main_data) {
  // Функция-диспетчер определяющая поток выполнения программы согласно
  // заданным флагам.
  char *current_line = NULL;
  size_t current_line_length = 0;
  char *output_line = NULL;
  int regex_compilation_flag = 0;
  int number_of_matches = 0;
  char last_printed_filename[FILENAME_LENGTH] = "";
  // char c_flag_output[111];
  regmatch_t matched_expression_coordinates;
  // инициализируем пакет переменных, первые два члена - filename_prefix,
  // linenumber_prefix.
  PrintersData printers_data = {"", "", output_line, current_line, 0};
  // Если нет флагов -e и -f, то первый аргумент это выражение, если есть, то
  // имя файла.
  int argc_filename_index;
  if ((grep_data.e) || (grep_data.f))
    argc_filename_index = grep_data.first_nonflag_index;
  else
    argc_filename_index = grep_data.first_nonflag_index + 1;

  // первый цикл проходит файлы.
  for (int i = argc_filename_index; main_data.argv[i] != NULL; i++) {
    char *current_filename = main_data.argv[i];
    FILE *file_pointer = FilePointerCreator(current_filename);
    if (!file_pointer) continue;

    // второй проходит строки в каждом файле
    current_line = NULL;  // для нормальной работы getline = NULL

    int line_index = 0;
    while (getline(&current_line, &current_line_length, file_pointer) != -1) {
      {  // getline считывает строку вместе со знаком перевода строки, убираем
         // это.
        char *n = strchr(current_line, '\n');
        // удаляем перевод строки из всех пустых строк, кроме последней
        if ((*current_line == '\n') && (*(current_line + 1) == '\n'))
          *(current_line + 1) = '\0';
        else if (n)
          *n = '\0';  //  и из всех прочих
      }

      line_index++;  // счетчик строк, начиная с 1
      printers_data.output_line =
          CharMemoryCAllocator(sizeof(char) * current_line_length);
      strcpy(printers_data.output_line, current_line);

      // создание префикса с именами файлов если файлов больше одного
      // за последним аргументом всегда следует NULL, если так, то файл
      // один.
      if ((grep_data.h) || (main_data.argv[argc_filename_index + 1] == NULL)) {
        printers_data.filename_prefix[0] = '\0';
      } else {
        sprintf(printers_data.filename_prefix, "%s:", main_data.argv[i]);
      }

      if (grep_data.i)
        regex_compilation_flag = REG_ICASE;  // игнорировать регистр

      RegexCompilationData regex_data = {
          NULL, current_line, regex_compilation_flag, current_line_length,
          &matched_expression_coordinates};

      int is_line_already_counted =
          0;  // переменная-флаг, показывающая не была ли данная строка уже
              // обработана, как совпадающая.

      // Третий цикл прогоняющий все данные регулярные выражения внутри каждой
      // строки.

      // strtok изменяет строку, поэтому используется буфер.
      char *strtok_tmp_buffer =
          CharMemoryCAllocator(strlen(grep_data.regex_list) + 111);

      int is_invert_match = 0;
      if (grep_data.v) {
        is_invert_match = IsInverseMatch(regex_data, strtok_tmp_buffer);
      }
      strcpy(strtok_tmp_buffer, grep_data.regex_list);
      regex_data.current_regex = strtok(strtok_tmp_buffer, "\n");
      while (regex_data.current_regex != NULL) {
        int is_regex_match = IsRegexMatch(regex_data);

        if (grep_data.v) is_regex_match = is_invert_match;

        if ((grep_data.n) && (is_regex_match) && (!is_line_already_counted)) {
          sprintf(printers_data.linenumber_prefix, "%d:", line_index);
        }

        if (grep_data.c) {  // Функция считает совпадения строк с регулярным
                            // выражением.
          if ((is_regex_match) && (!is_line_already_counted))
            number_of_matches++;
        }

        if (grep_data.l) {  // Пишутся только имена файлов
          if ((is_regex_match) && (!is_line_already_counted)) {
            if (strcmp(last_printed_filename, main_data.argv[i])) {
              fprintf(stdout, "%s\n", main_data.argv[i]);
              memset(last_printed_filename, '\0', FILENAME_LENGTH);
              strcpy(last_printed_filename, main_data.argv[i]);
            }
          }
        }

        if (grep_data.o && is_regex_match) {
          // При срабатывании флага, для каждого регулярного выражения,
          // вызывается функция сохранения всех найденных совпадений в массив.
          // При достижении конца цикла просмотра регулярных выражений
          // происходит сортировка найденного в порядке вхождения в строку,
          // далее они выводятся на печать, при этом, выводятся только самые
          // длинные совпадения, те, что являются частью более длинных, не
          // выводятся.
          MatchsSaver(regex_data, printers_data, 0);
        }
        // Печать, кроме -c, -l, -o.
        if ((is_regex_match) && (!is_line_already_counted)) {
          if ((!grep_data.c) && (!grep_data.l) && (!grep_data.o))
            ResultsPrinter(printers_data);
        }
        if (is_regex_match) is_line_already_counted = 1;
        regex_data.current_regex = strtok(NULL, "\n");
      }  // <== окончание цикла просмотра списка регулярных выражений.

      if (grep_data.o && matchs_array) {
        OrderOfOccurrenceSorter(matchs_array);
        //        MatchsArrayPrinter(matchs_array, printers_data);
        MatchsArrayPrinter(matchs_array);
        O_FlagData t;
        MatchsArrayCreator(t, 1);  // освобождение памяти.
      }
      free(strtok_tmp_buffer);
      free(printers_data.output_line);
    }  //  <== окончание цикла прохода текущего файла.

    free(current_line);
    fclose(file_pointer);

    if (grep_data.c) {
      fprintf(stdout, "%s%d\n", printers_data.filename_prefix,
              number_of_matches);
      number_of_matches = 0;
    }
  }  // <==  окончание цикла прохода файлов
}
char kGrepLegalFlags[] = "eivclnhsfo";

void ResultsPrinter(PrintersData printers_data) {
  fprintf(stdout, "%s%s%s\n", printers_data.filename_prefix,
          printers_data.linenumber_prefix, printers_data.output_line);
}

char *CharMemoryReAllocator(char *memory_area_address,
                            int desired_memory_size) {
  void *reallocated_memory;
  reallocated_memory = realloc(memory_area_address, desired_memory_size);

  if (!reallocated_memory) {
    fprintf(stderr, "Memory allocation fail.");
  }

  return (char *)reallocated_memory;
}

char *CharMemoryCAllocator(int desired_memory_size) {
  void *allocated_memory;
  allocated_memory = calloc(1, sizeof(char) * desired_memory_size);

  if (!allocated_memory) {
    fprintf(stderr, "Memory allocation fail.");
  }

  return (char *)allocated_memory;
}

O_FlagData *O_FlagDataMemoryCAllocator(size_t desired_memory_size) {
  void *allocated_memory;
  allocated_memory = calloc(1, sizeof(char) * desired_memory_size);

  if (!allocated_memory) {
    fprintf(stderr, "Memory allocation fail.");
  }

  return (O_FlagData *)allocated_memory;
}

O_FlagData *O_FlagDataMemoryReAllocator(O_FlagData *memory_area_address,
                                        int desired_memory_size) {
  void *reallocated_memory;

  reallocated_memory = realloc(memory_area_address, desired_memory_size);
  if (!reallocated_memory) {
    fprintf(stderr, "Memory allocation fail.");
  }

  return (O_FlagData *)reallocated_memory;
}

void NoSuchfileMessager(char *filename) {
  if (!grep_data.s)
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
}
/*
FILE *FilePointerCreator(char *filename) {
  FILE *file_to_print_pointer = fopen(filename, "rb");
  if (!file_to_print_pointer)  // если указатель NULL
    NoSuchfileMessager(filename);
  return file_to_print_pointer;
}
*/
char *RegexSaver(char *current_regex, int do_I_need_to_free_memory) {
  // Функция принимает строку с регулярным выражением и дописывает в выделенную
  // область памяти, разделяя выражения знаком перевода строки, реаллоцируя
  // память для каждого нового выражения.
  // По-идее, сделано не правильно, нужно сохранять в массив указателей. Но
  // переделывать нет смысла.

  static char *regex_holder = NULL;
  static int is_freed = 0;
  int t = 0;

  if (!regex_holder) {
    t = strlen(current_regex) + 1 + 1;  // '\0' + '\n'
    regex_holder = CharMemoryCAllocator(t);
    strcpy(regex_holder, current_regex);
    strcat(regex_holder, "\n");
  } else {
    t = strlen(current_regex) + strlen(regex_holder) + 1 + 1;
    regex_holder = CharMemoryReAllocator(regex_holder, t);
    strcat(regex_holder, current_regex);
    strcat(regex_holder, "\n");
  }

  if ((!is_freed) && (do_I_need_to_free_memory)) {
    free(regex_holder);
    is_freed = 1;
  }

  return regex_holder;
}

GrepData grep_data;
void GrepArgumentsExtractor(int argc, char *argv[]) {
  char kGrepLegalFlags[] = "e:ivclnhsf:o";
  int current_flag = 0;
  grep_data.regex_list = NULL;

  while ((current_flag = getopt(argc, argv, kGrepLegalFlags)) != -1) {
    switch (current_flag) {
      case 'e': {
        grep_data.e = 1;
        grep_data.regex_list = RegexSaver(optarg, 0);
        break;
      }
      case 'i': {
        grep_data.i = 1;
        break;
      }
      case 'v': {
        grep_data.v = 1;
        break;
      }
      case 'c': {
        grep_data.c = 1;
        break;
      }
      case 'l': {
        grep_data.l = 1;
        break;
      }
      case 'n': {
        grep_data.n = 1;
        break;
      }
      case 'h': {
        grep_data.h = 1;
        break;
      }
      case 's': {
        grep_data.s = 1;
        break;
      }
      case 'f': {
        grep_data.f = 1;

        char *current_line = NULL;
        size_t current_line_length = 0;
        FILE *regex_list_filepointer = FilePointerCreator(optarg);
        if (!regex_list_filepointer) break;
        while (getline(&current_line, &current_line_length,
                       regex_list_filepointer) != -1) {
          grep_data.regex_list = RegexSaver(current_line, 0);
        }
        free(current_line);
        fclose(regex_list_filepointer);
        break;
      }
      case 'o': {
        grep_data.o = 1;
        break;
      }
      case '?':
        printf("Error found !\n");
        break;
    }
  }
  // сохраняем адрес первого аргумента после флагов
  grep_data.first_nonflag_pointer = argv[optind];
  grep_data.first_nonflag_index = optind;
  // флаг отсутствия флагов
  if (grep_data.first_nonflag_index == 1) grep_data.is_without_flags = 1;
  // если регулярные выражения не заданы в файле или через флаг е, сохраняем из
  // аргументов
  if ((!grep_data.f) && (!grep_data.e))
    grep_data.regex_list = RegexSaver(grep_data.first_nonflag_pointer, 0);

  // Обнуляем лишние флаги при множественном их указании и конфликтах

  if (grep_data.c) {
    grep_data.n = 0;
    grep_data.o = 0;
  }
  if (grep_data.l) {
    grep_data.c = 0;
    grep_data.n = 0;
    grep_data.h = 0;
    grep_data.o = 0;
  }
  //  if ((grep_data.o) && (grep_data.v)) grep_data.is_skip_ov = 1;
}

void FileNameExtractor(main_data main_data, char *filename_holder,
                       int current_filename_index) {
  strcpy(filename_holder, main_data.argv[current_filename_index]);
}

int Comparator(const void *x, const void *y) {
  const O_FlagData *t1 = x;
  const O_FlagData *t2 = y;
  return (t1->match_position - t2->match_position);
}

void OrderOfOccurrenceSorter(O_FlagData *match_array) {
  size_t array_length = (match_array->arrays_last_index) + 1;
  qsort(match_array, array_length, sizeof(match_array[0]), Comparator);
}

int IsPartOfAnotherMatch(O_FlagData *matchs_array, int array_index_with_match) {
  int return_value = 0;
  for (size_t i = array_index_with_match + 1;
       i <= matchs_array->arrays_last_index; i++) {
    //    char *t = NULL;

    if (matchs_array[i].match_position ==
        matchs_array[array_index_with_match].match_position) {
      if (matchs_array[i].match_length >=
          matchs_array[array_index_with_match].match_length) {
        return_value = 1;
        break;
      }
    }
  }
  return return_value;
}

// void MatchsArrayPrinter(O_FlagData *matchs_array, PrintersData printers_data)
void MatchsArrayPrinter(O_FlagData *matchs_array) {
  for (size_t i = 0; i <= matchs_array->arrays_last_index; i++) {
    if (!IsPartOfAnotherMatch(matchs_array, i))
      fprintf(stdout, "%s%s%s\n", matchs_array[i].filename_prefix,
              matchs_array[i].linenumber_prefix, matchs_array[i].regex_match);
  }
}

O_FlagData *MatchsArrayCreator(O_FlagData data2write,
                               int do_I_need_to_free_memory) {
  /* Что здесь происходит? При первом вызове создается массив, размером в один
   * элемент. При каждом последующем длина массива увеличивается на один. АДрес
   * массива сохраняется в глобальной переменной.
   */

  static size_t array_new_size = 1;

  if ((do_I_need_to_free_memory)) {
    array_new_size = 1;

    for (size_t i = 0; i <= matchs_array->arrays_last_index; i++) {
      free(matchs_array[i].regex_match);
    }
    free(matchs_array);
    matchs_array = NULL;
  } else {
    matchs_array = O_FlagDataMemoryReAllocator(
        matchs_array, sizeof(O_FlagData) * array_new_size);

    matchs_array->arrays_last_index = array_new_size - 1;
    size_t last = matchs_array->arrays_last_index;
    // Для корректных результатов после сортировки в каждом члене массива должен
    // содеражться корректный индекс последнего элемента.
    for (size_t i = 0; i <= last; i++) {
      matchs_array[i].arrays_last_index = array_new_size - 1;
    }
    matchs_array[last].match_length = data2write.match_length;
    matchs_array[last].match_position = data2write.match_position;
    matchs_array[last].regex_match = data2write.regex_match;
    strcpy(matchs_array[last].linenumber_prefix, data2write.linenumber_prefix);
    strcpy(matchs_array[last].filename_prefix, data2write.filename_prefix);
    array_new_size++;
  }
  return matchs_array;
}

void MatchsSaver(RegexCompilationData regex_data,
                 PrintersData printers_datapack, size_t match_overall_offset) {
  /*
  Переменная match_overall_offset нужна для вычисления позиции совпадения от
  начала строки и при первом вызове всегда равна 0.

  Здесь происходит рекурсивный вызов до окончания нахождения совпадений.
    Совпадения сохраняются следующим образом:
    - создается массив структур с данными о совпадениях, который динамически
    увеличивается.
    - для каждого совпадения выделяется память, совпавший фрагмент сохраняется в
    своем элементе структуры
    - содержимое массива сортируется согласно порядку вхождения в строку
    - совпадения, являющиеся составными для совпадений большей длины исключаются
    из печати.
    - массив распечатывается, параллельно, освобождается память задействованная
    для хранения выражений
    - освобождается память самого массива.

  */

  int is_match = IsRegexMatch(regex_data);

  if (is_match) {
    int match_length = regex_data.matched_expression_coordinates->rm_eo -
                       regex_data.matched_expression_coordinates->rm_so;

    O_FlagData t;
    t.regex_match = CharMemoryCAllocator(sizeof(char) * (match_length + 1));
    memcpy(t.regex_match,
           regex_data.current_line +
               regex_data.matched_expression_coordinates->rm_so,
           match_length);
    t.match_length = match_length;

    t.match_position =
        regex_data.matched_expression_coordinates->rm_so + match_overall_offset;

    match_overall_offset +=
        regex_data.matched_expression_coordinates->rm_so + match_length;

    strcpy(t.filename_prefix, printers_datapack.filename_prefix);
    strcpy(t.linenumber_prefix, printers_datapack.linenumber_prefix);
    t.arrays_last_index =
        -1;  // Здесь всегда должен быть индекс последнего элемента.
    MatchsArrayCreator(t, 0);

    char *line_after_first_match =
        regex_data.current_line +
        regex_data.matched_expression_coordinates->rm_eo;

    regex_data.current_line = line_after_first_match;

    MatchsSaver(regex_data, printers_datapack, match_overall_offset);
  }
}

int IsRegexMatch(RegexCompilationData regex_data) {
  // Функция, компилирующая регулярные выражения и сопоставляющая их с данной
  // строкой. Возвращает 1, если выражение совпало.
  int is_match = 0;
  regex_t compiled_regex;
  int is_problem;
  char msgbuf[100];

  /* Compile regular expression */
  is_problem = regcomp(&compiled_regex, regex_data.current_regex,
                       regex_data.regex_compilation_flag);
  if (is_problem) {
    fprintf(stderr, "Could not compile regex\n");
    return (0);
  }

  /* Функция regexec.

  int regexec (const regex_t *restrict compiled, const char *restrict string,
    size_t nmatch, regmatch_t matchptr[restrict], int eflags)

    - первый параметр откомпилированное выражение
    - второй - строка для сопоставления
    - третий, nmatch, указывает сколько всего подсовпадений должно быть
  сохранено. Например,  "this (\w+) costs (\d+) USD", имеет 2 подвыражения, плюс
  все выражение целиком. Итого - три. Таким образом, чтобы сохранились позиции
  всех выражений nmatch должен быть >= 3.
  - четвертый, matchptr, содержит в себе массив структуры regmatch_t, где есть
  два поля: rm_so и rm_eo, т.е. начало совпадения выражения и следующий символ
  после окончания совпадения. Значение rm_so = -1 говорит о том, что данные о
  смещениях закончились. Т.е. для использования, создаем переменную типа
  regmatch, и отдаем в функцию ее адрес, после вызова переменная будет содержать
  адрес массива структур указанного типа.
  - пятый параметр используется в случаях, когда в функцию подается часть
  строки, концы которой не должны срабатывать на операторах ^ и $.
*/

  /* Execute regular expression */
  is_problem =
      regexec(&compiled_regex, regex_data.current_line, 2,
              regex_data.matched_expression_coordinates,
              0);  // число 2 - максимум, при котором выражение компилируется,
                   // если больше, то нет. Почему не понял.
  if (!is_problem) {
    is_match = 1;
  } else if (is_problem == REG_NOMATCH) {
    is_match = 0;
  } else {
    regerror(is_problem, &compiled_regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    return (0);
  }

  /* Free compiled regular expression if you want to use the regex_t again */
  regfree(&compiled_regex);

  return is_match;
}

int IsInverseMatch(RegexCompilationData regex_data, char *buffer_for_strtok) {
  // Функция проходит по всему списку регулярных выражений, выставляя флаг в
  // случае, если не совпадает ни одно из них.
  int is_invert_match = 1;
  //  int is_any_regex_match = 0;
  strcpy(buffer_for_strtok, grep_data.regex_list);
  regex_data.current_regex = strtok(buffer_for_strtok, "\n");
  while (regex_data.current_regex != NULL) {
    if (IsRegexMatch(regex_data)) {
      //    is_any_regex_match = 1;
      is_invert_match = 0;
      break;
    }
    regex_data.current_regex = strtok(NULL, "\n");
  }
  return is_invert_match;
}
