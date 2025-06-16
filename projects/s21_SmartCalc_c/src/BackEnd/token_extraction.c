#include "smartcalc_backend_library.h"

int TokenBreaker(const char* source_math_expression,
                 tokens_pack* separate_tokens) {
  /* Функция разбивает математическое выражение на лексемы и сохраняет по
   * указанному адресу в массив строк.*/

  char math_expression[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  strcpy(math_expression, source_math_expression);

  memset(separate_tokens, 0, sizeof(tokens_pack));
  int is_trouble = 0;
  char* actual_position_in_line = math_expression;
  int table_place_for_token = 0;

  // Разбираем строку на лексемы
  while (*actual_position_in_line) {
    // инициализируем переменные
    char actual_token[DBL_MAX_LENGTH + 1] = "";
    char actual_character = 0;
    memset(actual_token, '\0', sizeof(char) * (POSSIBLE_TOKEN_LENGTH + 1));
    actual_character = *actual_position_in_line;

    // детектор кодов для разных ситуаций
    int case_code = 0;  // <== за пределами диапазона возможных значений.

    if (actual_character == '(') {
      case_code = PARENTHESES_OPEN;
      actual_token[0] = actual_character;
      strcpy(separate_tokens->separate_tokens[table_place_for_token],
             actual_token);
      separate_tokens->token_codes[table_place_for_token] = case_code;
    }

    if (actual_character == ')') {
      case_code = PARENTHESES_CLOSE;
      actual_token[0] = actual_character;
      strcpy(separate_tokens->separate_tokens[table_place_for_token],
             actual_token);
      separate_tokens->token_codes[table_place_for_token] = case_code;
    }

    if (strchr(possible_operators, actual_character)) {
      actual_token[0] = actual_character;
      // определение кода лексемы
      switch (actual_character) {
        case '*':
        case '/':
        case '%':
        case '^': {
          case_code = BINARY_OPERATOR;
          break;
        }

        case '-':
        case '+': {
          int is_unary = 0;

          if (actual_position_in_line == math_expression) {
            is_unary = 1;
          } else {
            char previous_character = *(actual_position_in_line - 1);
            is_unary = is_unary || (previous_character == '(');
            is_unary = is_unary || (previous_character == '*');
            is_unary = is_unary || (previous_character == '/');
            is_unary = is_unary || (previous_character == '%');
            is_unary = is_unary || (previous_character == '^');
          }

          if (is_unary) {
            if (actual_character == '-') {
              // идентификатор унарного минуса
              actual_token[0] = '~';
            } else {
              // идентификатор унарного плюса
              actual_token[0] = '@';
            }

            case_code = FUNCTIONS;
          } else {
            case_code = BINARY_OPERATOR;
          }

        } break;

        default:
          printf("DBG. actual_character = '%c'\nSomething goes wrong! Stop!\n",
                 actual_character);
          exit(1);
          break;
      }

      strcpy(separate_tokens->separate_tokens[table_place_for_token],
             actual_token);
      separate_tokens->token_codes[table_place_for_token] = case_code;
    }

    if (actual_character >= '0' && actual_character <= '9') {
      case_code = DIGITS;
      // Ищем первую не цифру после начала числа
      char* is_non_digit = actual_position_in_line;
      while ((*is_non_digit >= '0' && *is_non_digit <= '9') ||
             *is_non_digit == '.') {
        is_non_digit++;
      }

      // копируем найденное
      int number_length = is_non_digit - actual_position_in_line;
      strncpy(actual_token, actual_position_in_line, number_length);
      strcpy(separate_tokens->separate_tokens[table_place_for_token],
             actual_token);
      actual_position_in_line += number_length - 1;

      // Выставляем в параллельный массив цифровой код лексемы
      separate_tokens->token_codes[table_place_for_token] = case_code;
    }

    if (strchr("aclst", actual_character)) {
      case_code = FUNCTIONS;
      // копируем во временную переменную отрезок строки длиной в
      // максимально возможное имя функции.
      char t[POSSIBLE_TOKEN_LENGTH + 1] = "";
      strncpy(t, actual_position_in_line, POSSIBLE_TOKEN_LENGTH);
      char* function_name_starts = NULL;
      for (int i = 0; i <= 9; i++) {  // <== проверяем на все возможные функции
        function_name_starts = strstr(t, possible_functions[i]);
        // начало имени функции в строке - первая позиция, а не
        // какая-то другая ==>
        if (function_name_starts == t) {
          strcpy(actual_token, possible_functions[i]);
          strcpy(separate_tokens->separate_tokens[table_place_for_token],
                 actual_token);
          actual_position_in_line += strlen(possible_functions[i]) - 1;
          break;
        }
      }

      if (!function_name_starts) {
        ErrorMessageCreator("Wromg function name has been detected.");
        is_trouble = 1;
      }
      separate_tokens->token_codes[table_place_for_token] = case_code;
    }

    if (actual_character == 'm') {
      case_code = BINARY_OPERATOR;
      // mod - бинарный оператор, транслируется в %
      char t[POSSIBLE_TOKEN_LENGTH + 1] = "";
      strncpy(t, actual_position_in_line, POSSIBLE_TOKEN_LENGTH);
      char* function_name_starts = strstr(t, possible_functions[0]);
      if (function_name_starts == t) {
        actual_token[0] = '%';
        strcpy(separate_tokens->separate_tokens[table_place_for_token],
               actual_token);
        actual_position_in_line += strlen(possible_functions[0]) - 1;
      }

      if (!function_name_starts) {
        ErrorMessageCreator("Wrong function name has been detected.");
        is_trouble = 1;
      }
      separate_tokens->token_codes[table_place_for_token] = case_code;
    }

    if (!case_code) {
      ErrorMessageCreator("Unknown error has been detected.");
      is_trouble = 1;
    }

    actual_position_in_line++;
    table_place_for_token++;
  }

  return is_trouble;
}
