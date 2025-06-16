#include <stdio.h>
#include <string.h>

// Предварительный прототип для скрипта на баше

int max_name_length = 11;
char foldernames_letters[12] = "abcdefg";
char filenames_letters[12] = "abcdefg";
void Printer(char *filename) {
  char data_stamp[11] = "_111111";
  if (strlen(filename) >= 4) {
    printf("DBG-1. actual_filename: %s\n", filename);
  }
}

int main() {
  char folders_name_letters[8] = "";

  int nested_folders_number = 1;
  int min_filelength = 4;

  // Алгоритм. В цикле проходим по всем вариантам возможных сочетаний букв.
  // Условие выхода - достижение предельной длины имени файла, т.е. 255 или
  // предельной длины всего пути с файлом 4096.

  /* Требования:
  - уход в глубину циклов блокируется на глубине количества данных букв.
  - имена файлов короче 4х-символов в буквенном префиксе выбрасываются.

  */

  char actual_filename[256] = "";

  for (int i = 0; i <= nested_folders_number; i++) {
    // Цикл вложенных папок.

    int letter = 0;
    char letter1[256] = "";
    for (letter; strlen(letter1) < max_name_length;) {
      // Цикл имен файлов, инкремент первой буквы.
      char t[2] = "";
      t[0] = filenames_letters[letter];
      strcat(letter1, t);
      // Проверяем, чтобы цикл не ушел в обработку несуществующих
      // букв. ==================================================
      if (letter >= strlen(filenames_letters) - 1) {
        Printer(letter1);
      } else {
        char letter2[256] = "";
        strcpy(letter2, letter1);
        for (letter++; strlen(letter2) < max_name_length;) {
          // Цикл имен файлов, инкремент второй буквы.
          char t[2] = "";
          t[0] = filenames_letters[letter];
          strcat(letter2, t);
          // Проверяем, чтобы цикл не ушел в обработку несуществующих
          // букв. ==================================================
          if (letter >= strlen(filenames_letters) - 1) {
            Printer(letter2);
          } else {
            char letter3[256] = "";
            strcpy(letter3, letter2);
            for (letter++; strlen(letter3) < max_name_length;) {
              // Цикл имен файлов, инкремент третьей буквы.
              char t[2] = "";
              t[0] = filenames_letters[letter];
              strcat(letter3, t);
              // Проверяем, чтобы цикл не ушел в обработку несуществующих
              // букв. ==================================================
              if (letter >= strlen(filenames_letters) - 1) {
                Printer(letter3);
              } else {
                char letter4[256] = "";
                strcpy(letter4, letter3);
                for (letter++; strlen(letter4) < max_name_length;) {
                  // Цикл имен файлов, инкремент четвертой буквы.
                  char t[2] = "";
                  t[0] = filenames_letters[letter];
                  strcat(letter4, t);
                  // Проверяем, чтобы цикл не ушел в обработку несуществующих
                  // букв. ==================================================
                  if (letter >= strlen(filenames_letters) - 1) {
                    Printer(letter4);
                  } else {
                    char letter5[256] = "";
                    strcpy(letter5, letter4);
                    for (letter++; strlen(letter5) < max_name_length;) {
                      // Цикл имен файлов, инкремент пятой буквы.
                      char t[2] = "";
                      t[0] = filenames_letters[letter];
                      strcat(letter5, t);
                      // Проверяем, чтобы цикл не ушел в обработку
                      // несуществующих букв.
                      // ==================================================
                      if (letter >= strlen(filenames_letters) - 1) {
                        Printer(letter5);
                      } else {
                        char letter6[256] = "";
                        strcpy(letter6, letter5);
                        for (letter++; strlen(letter6) < max_name_length;) {
                          // Цикл имен файлов, инкремент шестой буквы.
                          char t[2] = "";
                          t[0] = filenames_letters[letter];
                          strcat(letter6, t);
                          // Проверяем, чтобы цикл не ушел в обработку
                          // несуществующих букв.
                          // ==================================================
                          if (letter >= strlen(filenames_letters) - 1) {
                            Printer(letter6);
                          } else {
                            char letter7[256] = "";
                            strcpy(letter7, letter6);
                            for (letter++; strlen(letter7) < max_name_length;) {
                              // Цикл имен файлов, инкремент седьмой буквы.
                              char t[2] = "";
                              t[0] = filenames_letters[letter];
                              strcat(letter7, t);
                              Printer(letter7);
                            }
                            letter--;
                          }
                        }
                        letter--;
                      }
                    }
                    letter--;
                  }
                }
                letter--;
              }
            }
            letter--;
          }
        }
        letter--;
      }
    }
  }
}