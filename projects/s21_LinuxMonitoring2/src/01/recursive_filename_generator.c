#include <stdio.h>
#include <string.h>
#define LENGTH 22
#define how_many_nested_folders 3

// Предварительный прототип для скрипта на баше

int max_name_length = 11;
char filenames_letters[12] = "ab";
char foldernames_letters[12] = "abcd";

void Printer(char* filename) {
  char data_stamp[11] = "_111111";
  if (strlen(filename) >= 4) {
    //    printf("DBG. actual_filename: %s%s\n", filename, data_stamp);
    printf("%s\n", filename);
  }
}

int how_many_files = 0;
void RFilenamesGenerator(int letter_index, char* filename) {
  while (strlen(filename) != max_name_length) {
    char t[2] = "";
    t[0] = filenames_letters[letter_index];
    strcat(filename, t);
    if (letter_index < strlen(filenames_letters) - 1) {
      char f[LENGTH] = "";
      strcpy(f, filename);
      RFilenamesGenerator(letter_index++, f);
    } else {
      // В баше выделяем само имя без пути и сравниваем по нему. Здесь нет
      // смысла возиться с этим.
      if (strlen(filename) >= 4) {
        Printer(filename);
      }
    }
  }
}

void RFoldernamesGenerator(int how_many_nested_folder, char* path) {
  // В задании ничего не сказано об уникальности имен папок. Делаем длину имени
  // 4, если меньше.

  char foldername[8] = "";
  memset(foldername, '\0', sizeof(foldername));
  strcpy(foldername, foldernames_letters);
  char t[2] = "";
  t[0] = *(strchr(foldername, '\0') - 1);
  while (strlen(foldername) < 4) {
    strcat(foldername, t);
  }

  char t_path[222] = "";
  char filename[333] = "";
  for (int i = 0; i < how_many_nested_folder; i++) {
    strcat(t_path, foldername);
    strcat(t_path, "/");
    memset(filename, '\0', sizeof(filename));
    strcpy(filename, t_path);
    //    printf("DBG. %s\n", path);
    RFilenamesGenerator(0, filename);
  }
}

int main() {
  char filename[LENGTH * how_many_nested_folders] = "";
  int letter_index = 0;
  // RFoldernamesGenerator(how_many_nested_folders, filename);
  RFilenamesGenerator(0, filename);
}