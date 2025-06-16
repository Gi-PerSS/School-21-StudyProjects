#include "smartcalc_backend_library.h"

int RPC_Functions(char* function_name, Stack* working_stack) {
  int is_trouble = 0;
  char ascii_double[DBL_MAX_LENGTH + 1] = {0};
  is_trouble = Pop(working_stack, ascii_double);
  double x = strtod(ascii_double, NULL);
  double result = 0;
  char ascii_result[DBL_MAX_LENGTH + 1] = {0};

  int function_number = 0;
  for (int i = 1; i < NUMBER_OF_POSSIBLE_FUNCTION; i++) {
    if (!strcmp(possible_functions[i], function_name)) {
      function_number = i;
    }
  }

  switch (function_number) {
    case ACOS: {
      if (-1 <= x && x <= 1) {
        result = acos(x);
      } else {
        ErrorMessageCreator(
            "x out of range. Possible values for the 'acos' -> (-1 <= x <= "
            "1)");
        is_trouble = 1;
      }
      break;
    }

    case ASIN: {
      if (-1 <= x && x <= 1) {
        result = asin(x);
      } else {
        ErrorMessageCreator(
            "x out of range. Possible values for the 'asin' -> (-1 <= x <= "
            "1)");
        is_trouble = 1;
      }
      break;
    }

    case ATAN: {
      result = atan(x);
      break;
    }

    case SQRT: {
      if (x >= 0) {
        result = sqrt(x);
      } else {
        ErrorMessageCreator(
            "x out of range. Possible values for the 'sqrt' -> (x >= 0)");
        is_trouble = 1;
      }
      break;
    }

    case COS: {
      result = cos(x);
      break;
    }
    case SIN: {
      result = sin(x);
      break;
    }
    case TAN: {
      result = tan(x);
      break;
    }
    case LN: {
      if (x >= 0) {
        result = log(x);
      } else {
        ErrorMessageCreator(
            "x out of range. Possible values for the 'ln' -> (x >= 0).");
        is_trouble = 1;
      }
      break;
    }
    case LOG: {
      if (x >= 0) {
        result = log10(x);
      } else {
        ErrorMessageCreator(
            "x out of range. Possible values for the 'log' -> (x >= 0).");
        is_trouble = 1;
      }
      break;
    }

    default:
      break;
  }

  sprintf(ascii_result, "%.7f", result);
  is_trouble = is_trouble || Push(working_stack, ascii_result, 0);
  return is_trouble;
}

int RPC_BinaryOperators(char math_operator, Stack* stack) {
  int is_trouble = 0;
  double x = 0;
  double y = 0;
  double result = 0;
  char ascii_x[DBL_MAX_LENGTH + 1] = {0};
  char ascii_y[DBL_MAX_LENGTH + 1] = {0};
  char ascii_result[DBL_MAX_LENGTH + 1] = {0};

  if (math_operator == '~' || math_operator == '@') {
    // достаем из стека 1 операнд
    Pop(stack, ascii_x);
    x = strtod(ascii_x, NULL);
  } else {
    // иначе, 2.
    Pop(stack, ascii_y);
    //  char* p = ascii_y;
    y = strtod(ascii_y, NULL);
    Pop(stack, ascii_x);
    x = strtod(ascii_x, NULL);
  }

  switch (math_operator) {
    case '-': {
      result = x - y;
      break;
    }
    case '+': {
      result = x + y;
      break;
    }
    case '/': {
      if (y != 0) {
        result = x / y;
      } else {
        ErrorMessageCreator("Division by zero. ");
        is_trouble = 1;
      }

      break;
    }
    case '*': {
      result = x * y;
      break;
    }
    case '%': {
      result = fmod(x, y);
      break;
    }
    case '^': {
      result = pow(x, y);
      break;
    }
    case '~': {
      result = -x;
      break;
    }
    case '@': {
      result = x;
      break;
    }

    default:
      break;
  }

  sprintf(ascii_result, "%.7f", result);
  is_trouble = is_trouble || Push(stack, ascii_result, 0);

  return is_trouble;
}

int TokenCodeDetector(char* token) {
  int token_code = 0;

  char first_character = *token;

  if (first_character == '~' || first_character == '@') {
    token_code = UNARY_OPERATOR;
  } else if ((first_character >= '%' && first_character <= '/') ||
             first_character == '^') {
    token_code = BINARY_OPERATOR;

  } else if (first_character >= '0' && first_character <= '9') {
    token_code = DIGITS;
  } else {
    token_code = FUNCTIONS;
  }

  return token_code;
}

int PolishCalculator(tokens_pack* postfix_math_expression,
                     char* result_holder) {
  int is_trouble = 0;
  int case_code = 0;
  int i = 0;
  Stack stack = {0};

  while (strcmp(postfix_math_expression->separate_tokens[i], "")) {
    char actual_token[POSSIBLE_TOKEN_LENGTH] = {0};
    strcpy(actual_token, postfix_math_expression->separate_tokens[i]);
    //    case_code = postfix_math_expression->token_codes[i];
    case_code = TokenCodeDetector(actual_token);
    switch (case_code) {
      case DIGITS: {
        char next_token[POSSIBLE_TOKEN_LENGTH] = {0};
        strcpy(next_token, postfix_math_expression->separate_tokens[i + 1]);

        if (!strcmp(next_token, "~")) {
          char t[POSSIBLE_TOKEN_LENGTH + 1] = {0};
          *t = '-';
          strcat(t, actual_token);
          memset(actual_token, 0, POSSIBLE_TOKEN_LENGTH);
          strcpy(actual_token, t);
          i++;
        }

        Push(&stack, actual_token, 0);
        break;
      }
      case FUNCTIONS: {
        is_trouble = RPC_Functions(actual_token, &stack);
        break;
      }
      case BINARY_OPERATOR: {
        RPC_BinaryOperators(*actual_token, &stack);
        break;
      }

      default:
        break;
    }

    i++;
  }
  memset(result_holder, 0, DBL_MAX_LENGTH + 1);
  Pop(&stack, result_holder);
  CommaToPointConverter(result_holder);
  InsignificantZerosTrimmer(result_holder);

  return is_trouble;
}

void CommaToPointConverter(char* math_expression) {
  for (int i = 0; math_expression[i]; i++) {
    if (math_expression[i] == ',') {
      math_expression[i] = '.';
    }
  }
}

void InsignificantZerosTrimmer(char* ascii_double) {
  double t = strtod(ascii_double, NULL);
  memset(ascii_double, 0, DBL_MAX_LENGTH + 1);
  sprintf(ascii_double, "%.15g", t);
}