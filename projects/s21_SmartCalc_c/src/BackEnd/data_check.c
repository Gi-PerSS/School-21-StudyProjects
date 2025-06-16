#include "smartcalc_backend_library.h"

int IsDigit(char* pointer_to_symbol) {
  int is_digit_on_point = 0;
  if (*pointer_to_symbol >= '0' && *pointer_to_symbol <= '9') {
    is_digit_on_point = 1;
  }
  return is_digit_on_point;
}

void ErrorMessageCreator(const char* error_message) {
  sprintf(errors_in_actual_expression, "ERROR: %s", error_message);

  /*

  static size_t free_space_in_buffer = ERROR_MESSAGES_LENGTH_MAX;
  char error_prefix[11] = "ERROR: ";
  if (free_space_in_buffer > strlen(error_message) + strlen(error_prefix) + 1) {
    strcat(errors_in_actual_expression, error_prefix);
    strcat(errors_in_actual_expression, error_message);
    strcat(errors_in_actual_expression, "\n");
  } else {
    memset(errors_in_actual_expression, 0, ERROR_MESSAGES_LENGTH_MAX);
    strcat(errors_in_actual_expression, "Too many errors in line.");
  }
  */
}

//  скобки в правильном порядке и в правильном количестве
int ParenthesesChecker(const char* math_expression) {
  /*Алгоритм:
- открывающую скобку кладем в стек
- на закрывающей
  - проверяем, что стек не пуст, если пуст, то стоп
  - выбрасываем открывающую скобку из стека
- если к достижению конца строки стек пуст, значит все ок.
  - если нет, то стоп, отдаем ошибку в выражении.
*/

  int is_trouble = 0;

  char math_expression_copy[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  strcpy(math_expression_copy, math_expression);
  Stack t = {0};
  char* actual_position = math_expression_copy;

  while (*actual_position && !is_trouble) {
    switch (*actual_position) {
      case '(': {
        Push(&t, "(", 0);
        break;
      }
      case ')': {
        char token[POSSIBLE_TOKEN_LENGTH + 1] = "";
        is_trouble = Pop(&t, token);
        break;
      }
      default:
        break;
    }
    actual_position++;
  }

  if (is_trouble) {
    is_trouble = 1;
    ErrorMessageCreator("A problem with brackets has been detected.");
  }
  return is_trouble;
}

int DotChecker(const char* math_expression) {
  //  в числе одна точка.

  int is_trouble = 0;
  char math_expression_copy[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  strcpy(math_expression_copy, math_expression);
  char* actual_position = math_expression_copy;

  /*Алгоритм:
  - ищем первое вхождение точки
  - проверяем, что точка не первый и не последний символ в строке
  - проверяем, что перед точкой стоит цифра
  - что после точки стоит цифра
  - проверяем, что до конца ряда цифр нет других точек

  - повторяем цикл с адреса, следующего за окончанием ряда цифр после точки
  */

  char* first_dot_occurence = (char*)strchr(math_expression, '.');

  if (first_dot_occurence) {
    is_trouble = (first_dot_occurence == math_expression ||
                  *(first_dot_occurence + 1) == '\0');

    if (first_dot_occurence && !is_trouble) {
      is_trouble = is_trouble || (!IsDigit(first_dot_occurence - 1) ||
                                  !IsDigit(first_dot_occurence + 1));

      actual_position = first_dot_occurence + 2;
      while (IsDigit(actual_position)) {
        actual_position++;
      }
      is_trouble = is_trouble || (*actual_position == '.');
    }
  }
  if (is_trouble) {
    ErrorMessageCreator("Dot-problem has been detected.");
  }
  return is_trouble;
}

int FunctionsNameChecker(const char* math_expression) {
  int is_trouble = 0;
  char math_expression_copy[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  strcpy(math_expression_copy, math_expression);
  char* actual_position = NULL;

  /* в строке только имена функций
  Алгоритм:
  - последовательно ищем имена функций, начиная в самых длинных, замещая их
  символом пробела
  - проверяем строку посимвольно относится ли каждый символ к списку допустимых:
  математические и пробел.
    - если нет, то стоп - отдаем ошибку данных.
  */

  for (int i = 0; i < NUMBER_OF_POSSIBLE_FUNCTION; i++) {
    char* function_name_start = NULL;
    actual_position = math_expression_copy;
    function_name_start = strstr(actual_position, possible_functions[i]);

    while (function_name_start) {
      int actual_name_length = strlen(possible_functions[i]);

      for (int i = 0; i < actual_name_length; i++) {
        function_name_start[i] = ' ';
      }
      actual_position = function_name_start + actual_name_length;
      function_name_start = strstr(actual_position, possible_functions[i]);
    }
  }

  actual_position = math_expression_copy;
  while (*actual_position) {
    if (!strchr(possible_characters, *actual_position)) {
      is_trouble = 1;
      ErrorMessageCreator("Wrong function name has been detected.");
    }
    actual_position++;
  }

  return is_trouble;
}

int ParentheseAfterFunctNameChecker(const char* math_expression) {
  /* аргументы функций всегда в скобках и скобки в правильном порядке ()
  Алгоритм:
  - находим имя функции
  - проверяем, что следующий символ открывающая скобка, если я правильно
  понимаю, то этой проверки достаточно, т.к. выражение в целом уже проверено.
  */
  int is_trouble = 0;

  char math_expression_copy[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  strcpy(math_expression_copy, math_expression);
  is_trouble = ParenthesesChecker(math_expression_copy);

  if (!is_trouble) {
    char* actual_position = math_expression_copy;
    for (int i = 1; !is_trouble && i < NUMBER_OF_POSSIBLE_FUNCTION; i++) {
      char* function_name_start = NULL;
      function_name_start = strstr(actual_position, possible_functions[i]);
      while (function_name_start) {
        int function_name_length = strlen(possible_functions[i]);
        actual_position = function_name_start + function_name_length;
        if (*actual_position != '(') {
          ErrorMessageCreator("A problem with brackets has been detected.");
        }
        function_name_start = strstr(actual_position, possible_functions[i]);
      }
    }
  }
  return is_trouble;
}

int OperatorsOrderChecker(const char* math_expression) {
  char math_expression_copy[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  strcpy(math_expression_copy, math_expression);
  SpaceTrimmer(math_expression_copy);
  char* actual_position = math_expression_copy;
  // знаки математичеких операций лишь в возможной последовательности
  actual_position = math_expression_copy;
  int is_trouble = 0;
  while (!is_trouble && *actual_position) {
    char actual_char = *actual_position;
    if (actual_char == '-' || actual_char == '+') {
      /*  - Что является маркером ненормальности расстановки математических
        знаков + и - ?
        - после знака )
        - знак последний в строке
        */
      is_trouble = is_trouble || (*(actual_position + 1) == ')');
      is_trouble = is_trouble || (*(actual_position + 1) == '\0');
      is_trouble =
          is_trouble || strchr(possible_operators + 2, *(actual_position + 1));

    } else {
      if (strchr(possible_operators, actual_char)) {
        /*
        Что является маркером ненормальности расстановки прочих математических
        знаков?
        - перед знаком (
        - перед знаком любой другой знак
        - знак первый в строке
        - после знака )
        - знак последний в строке
        - после знака любой другой знак, кроме + -
        */

        is_trouble = is_trouble || (*(actual_position + 1) == ')');
        is_trouble = is_trouble || (*(actual_position + 1) == '\0');
        is_trouble = is_trouble ||
                     strchr(possible_operators + 2, *(actual_position + 1));
        is_trouble = is_trouble || (actual_position == math_expression_copy);

        if (actual_position != math_expression_copy) {
          is_trouble =
              is_trouble || strchr(possible_operators, *(actual_position - 1));

          is_trouble = is_trouble || (*(actual_position - 1) == '(');
        }
      }
    }

    actual_position++;
  }

  if (is_trouble) {
    ErrorMessageCreator(
        "A problem with the order of the operator is detected.");
  }

  return is_trouble;
}

int GeneralOrderChecker(char* math_expression) {
  int is_trouble = 0;
  /*
  - Всякая закрывающая скобка должна заканчиваться либо концом строки, либо
  математическим знаком, либо mod-ом, либо другой закрывающей скобкой
  - Всякое число должно заканчиваться либо концом строки, либо математическим
  оператором, либо mod-ом, либо закрывающей скобкой

200000,000000*(0,010000+0,010000/((1+0,010000)^24-1))
  */
  char* actual_character = math_expression;
  while (*actual_character) {
    char* next_character = actual_character + 1;
    if (*actual_character == ')') {
      if (*next_character != '\0' && *next_character != ')' &&
          strncmp(next_character, "mod", 3) &&
          !strchr(possible_operators, *next_character))
        is_trouble = 1;
    } else if (IsDigit(actual_character)) {
      /* следующий символ может быть точкой, цифрой, матем. оператором, концом
       * строки, оператором mod*/
      if (*next_character != '.' && !IsDigit(next_character) &&
          !strchr(possible_operators, *next_character) &&
          strncmp(next_character, "mod", 3) && *next_character != ')') {
        is_trouble = 1;
      }
    }
    actual_character++;
  }

  if (is_trouble) {
    ErrorMessageCreator("The mathematical operator is missing.");
  }

  return is_trouble;
}

int MathExpressionChecker(char* math_expression) {
  int is_trouble = 0;

  SpaceTrimmer(math_expression);
  is_trouble = ParenthesesChecker(math_expression);
  is_trouble = is_trouble || DotChecker(math_expression);
  is_trouble = is_trouble || FunctionsNameChecker(math_expression);
  is_trouble = is_trouble || ParentheseAfterFunctNameChecker(math_expression);
  is_trouble = is_trouble || GeneralOrderChecker(math_expression);
  is_trouble = is_trouble || OperatorsOrderChecker(math_expression);

  return is_trouble;
}

void Comma2DotConverter(char* math_expression) {
  char* position_in_line = math_expression;
  while (*position_in_line) {
    if (*position_in_line == ',') {
      *position_in_line = '.';
    }
    position_in_line++;
  }
}

void SpaceTrimmer(char* math_expression) {
  char math_expression_copy[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  char* source_read_point = math_expression;
  char* destination_write_point = math_expression_copy;
  while (*source_read_point) {
    if (*source_read_point == ' ') {
      source_read_point++;
    } else {
      *destination_write_point = *source_read_point;
      destination_write_point++;
      source_read_point++;
    }
  }

  memset(math_expression, 0, strlen(math_expression));
  strcpy(math_expression, math_expression_copy);
}