/* Программа для генерации правильных математических выражений.
 */
#include "correct_math_expression_generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIST_LENGTH 11
#define EXPRESSIONS_STRING_LENGTH 255
#define EXPRESSIONS_IN_FILE 100
#define POSSIBLE_NUMBER_TOKEN 19
#define POSSIBLE_TOKEN_LENGTH 4
#define RESULT_FILENAME "correct_math_expressions.txt"

/*
tokens[1], [2] - унарные плюс и минус.
 Функции начинаются с 9-го индекса
*/
const char tokens[][POSSIBLE_TOKEN_LENGTH + 1] = {
    "()",  "+",   "-",   "+",    "-",    "*",    "/",    "^",  "%",
    "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};

int RandomTokenGenerator(int is_subexpression_possible) {
  /*
    В общем случае если нам нужно получить числа из отрезка [A;B], то необходимо
   воспользоваться следующей конструкцией: A + rand()%(B-A+1).
  */
  int token_code = -1;
  int high_border = 19;

  if (is_subexpression_possible) {
    token_code = rand() % high_border;
  } else {
    token_code = 1 + rand() % high_border;
  }

  return token_code;
}

int OperationOnlyGenerator(void) {
  // Генерируем знак операции перед скобкой
  int new_token_code = RandomTokenGenerator(0);
  while (new_token_code < 3 || new_token_code > 8) {
    new_token_code = RandomTokenGenerator(0);
  }
  return new_token_code;
}

double RandomDoubleGenerator(void) { return (double)rand() / (RAND_MAX); }

void ExpressionsFileWriter(char* actual_math_expresion) {
  printf("%s\n", actual_math_expresion);

  FILE* f = fopen(RESULT_FILENAME, "a");
  fprintf(f, "%s\n\n", actual_math_expresion);
  fclose(f);
}

char LastCharInLine(char* math_expression) {
  char last_char_in_line = 'z';
  if (math_expression[0] != '\0') {
    last_char_in_line = *(strchr(math_expression, '\0') - 1);
  }

  return last_char_in_line;
}

void UnaryOperatorExpressionsGenerator(char* math_expression,
                                       char* temp_expression, int token_index) {
  char temp_double_string[EXPRESSIONS_STRING_LENGTH - 1 + 1] = "";
  char last_char_in_line = LastCharInLine(math_expression);
  double t = RandomDoubleGenerator();

  if (strlen(math_expression) == 0 || last_char_in_line == '(') {
    // если унарный плюс первый в строке
    strcat(temp_expression, tokens[token_index]);
    sprintf(temp_double_string, "%f", t);
    strcat(temp_expression, temp_double_string);

  } else {
    // если нет игнор.
  }
}

void BinaryOperatorExpressionsGenerator(char* math_expression,
                                        char* temp_expression,
                                        int token_index) {
  char temp_double_string[EXPRESSIONS_STRING_LENGTH - 1 + 1] = "";
  char last_char_in_line = LastCharInLine(math_expression);
  double number_1 = RandomDoubleGenerator();
  double number_2 = RandomDoubleGenerator();

  // Если выражение первое в строке сначала цепляем число.
  if (strlen(math_expression) == 0 || last_char_in_line == '(') {
    sprintf(temp_double_string, "%f", number_1);
    strcat(temp_expression, temp_double_string);
    temp_double_string[0] = '\0';
  }

  strcat(temp_expression, tokens[token_index]);
  sprintf(temp_double_string, "%f", number_2);
  strcat(temp_expression, temp_double_string);
  temp_double_string[0] = '\0';
}

void FuctionsExpressionsGenerator(char* math_expression, char* temp_expression,
                                  int token_index) {
  char temp_double_string[EXPRESSIONS_STRING_LENGTH - 1 + 1] = "";
  char last_char_in_line = LastCharInLine(math_expression);
  double number_1 = RandomDoubleGenerator();

  if (strlen(math_expression) != 0 && last_char_in_line != '(') {
    // Если перед выражение что-то есть цепляем сначала знак операции
    int t = OperationOnlyGenerator();
    strcat(temp_expression, tokens[t]);
  }

  strcat(temp_expression, tokens[token_index]);
  strcat(temp_expression, "(");

  sprintf(temp_double_string, "%f", number_1);
  strcat(temp_expression, temp_double_string);
  temp_double_string[0] = '\0';

  strcat(temp_expression, ")");
}

void NestedExpressionGenerator(char* math_expression, char* temp_expression) {
  char temp_double_string[EXPRESSIONS_STRING_LENGTH - 1 + 1] = "";
  int new_token_code;
  char last_char_in_line = LastCharInLine(math_expression);

  int level_of_nestedness = 2 + rand() % 5;

  if (strlen(math_expression) != 0 && last_char_in_line != '(') {
    // Если перед выражение что-то есть цепляем сначала знак операции
    new_token_code = OperationOnlyGenerator();
    strcat(temp_expression, tokens[new_token_code]);
  }

  for (int i = 1; i <= level_of_nestedness; i++) {
    strcat(temp_expression, "(");
  }

  while (level_of_nestedness) {
    new_token_code = OperationOnlyGenerator();
    MathExpressionsGenerator(new_token_code, temp_expression);
    strcat(temp_expression, ")");
    level_of_nestedness--;
  }
}

int MathExpressionsGenerator(int token_code, char* math_expression) {
  char temp_expression[EXPRESSIONS_STRING_LENGTH + 1] = "";
  char temp_double_string[EXPRESSIONS_STRING_LENGTH - 1 + 1] = "";

  char last_char_in_line = LastCharInLine(math_expression);

  int new_token_code;
  switch (token_code) {
    /*
    const char tokens[][POSSIBLE_TOKEN_LENGTH + 1] = {
    "()",  "+",   "-",   "+",    "-",    "*",    "/",    "^",  "%",
    "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
    */
    case 0: {
      NestedExpressionGenerator(math_expression, temp_expression);
      break;
    }
    case 1: {
      UnaryOperatorExpressionsGenerator(math_expression, temp_expression, 1);

      break;
    }
    case 2: {
      UnaryOperatorExpressionsGenerator(math_expression, temp_expression, 2);

      break;
    }
    case 3: {
      BinaryOperatorExpressionsGenerator(math_expression, temp_expression, 3);
      break;
    }
    case 4: {
      BinaryOperatorExpressionsGenerator(math_expression, temp_expression, 4);
      break;
    }
    case 5: {
      BinaryOperatorExpressionsGenerator(math_expression, temp_expression, 5);
      break;
    }
    case 6: {
      BinaryOperatorExpressionsGenerator(math_expression, temp_expression, 6);
      break;
    }
    case 7: {
      BinaryOperatorExpressionsGenerator(math_expression, temp_expression, 7);
      break;
    }
    case 8: {
      BinaryOperatorExpressionsGenerator(math_expression, temp_expression, 8);
      break;
    }
    case 9: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 9);
      break;
    }
    case 10: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 10);
      break;
    }
    case 11: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 11);
      break;
    }
    case 12: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 12);
      break;
    }
    case 13: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 13);
      break;
    }
    case 14: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 14);
      break;
    }
    case 15: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 15);
      break;
    }
    case 16: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 16);
      break;
    }
    case 17: {
      FuctionsExpressionsGenerator(math_expression, temp_expression, 17);
      break;
    }
    default: {
      break;
    }
  }

  int general_lenth = strlen(math_expression) + strlen(temp_expression);
  if (general_lenth >= EXPRESSIONS_STRING_LENGTH) {
    return 1;
  } else {
    strcat(math_expression, temp_expression);
    return 0;
  }
}

void CEO() {
  srand(time(NULL));

  for (int i = 0; i < LIST_LENGTH; i++) {
    char math_expression[EXPRESSIONS_STRING_LENGTH + 1] = "";
    int is_string_full = 0;

    while (!is_string_full) {
      int token = RandomTokenGenerator(1);
      is_string_full = MathExpressionsGenerator(token, math_expression);
    }

    ExpressionsFileWriter(math_expression);
  }
}

int main() {
  CEO();
  return 0;
}