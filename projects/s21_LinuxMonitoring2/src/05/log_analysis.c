#include <stdio.h>
#include <string.h>

// Программа на си для анализа логов, для последующей трансляции на язык awk
// Неверный подход. Надо просто написать алгоритм в псевдокоде и сразу
// реализовывать на awk

void ResponceCodeEntries() {
  // Формат имен файлов nginx_logfile_1.log
  int lines_counter = 0;
  for (int i = 1; i <= 5; i++) {
    char actual_filename[33] = "";
    sprintf(actual_filename, "../04/nginx_logfile_%d.log", i);

    FILE* log_file = fopen(actual_filename, "r");
    // Обработка строк
    char buffer_line[222] = "";
    while (NULL != fgets(buffer_line, 221, log_file)) {
      printf("%s", buffer_line);
      lines_counter++;
    }

    fclose(log_file);
  }

  printf("number of line is %d\n", lines_counter);
}

int main(void) {
  ResponceCodeEntries();

  /*
   int x = 0;
    printf("Enter a random number from 1 to 4\n");
    scanf("%d", &x);

    switch (x) {
      case 1: {
      } break;
      case 2: {
      } break;
      case 3: {
      } break;
      case 4: {
      } break;
      default: {
        printf("wrong number = %d \n", x);
      } break;
    }
  */

  return 0;
}

/*

== Задание ==
Написать bash-скрипт для разбора логов nginx из Части 4 через awk.
Скрипт запускается с 1 параметром, который принимает значение 1, 2, 3 или 4.
В зависимости от значения параметра вывести:

Все записи, отсортированные по коду ответа
Все уникальные IP, встречающиеся в записях
Все запросы с ошибками (код ответа - 4хх или 5хх)
Все уникальные IP, которые встречаются среди ошибочных запросов

*/