#include "smartcalc_backend_library.h"

int PriorityDetector(char math_operator) {
  int priority = 0;

  switch (math_operator) {
    case '~':
    case '^': {
      priority = 10;
      break;
    }

    case '/':
    case '%':
    case '*': {
      priority = 8;
      break;
    }

    case '+':
    case '-': {
      priority = 6;
      break;
    }

    default:
      break;
  }

  return priority;
}

int InfixToPostfixTranslator(tokens_pack* infix_math_expression,
                             tokens_pack* postfix_math_expression) {
  int is_trouble = 0;
  /*
  ВОзможные варианты событий:
  - число
  - унарный оператор или функция
  - бинарный оператор
  - скобка

  - число сразу на выход
  */

  Stack stack = {0};
  char token_on_stack[POSSIBLE_TOKEN_LENGTH + 1] = {0};

  int i = 0;
  int p = 0;
  while (!is_trouble && infix_math_expression->token_codes[i] != 0) {
    int case_code = 0;
    case_code = infix_math_expression->token_codes[i];

    char actual_token[EXPRESSIONS_STRING_LENGTH + 1] = {0};
    strcpy(actual_token, infix_math_expression->separate_tokens[i]);

    switch (case_code) {
      case FUNCTIONS: {
        if (actual_token[0] != '@') {
          Push(&stack, infix_math_expression->separate_tokens[i], FUNCTIONS);
        }
        break;
      }
      case DIGITS: {
        strcpy(postfix_math_expression->separate_tokens[p],
               infix_math_expression->separate_tokens[i]);
        p++;
        break;
      }
      case BINARY_OPERATOR: {
        memset(token_on_stack, 0, POSSIBLE_TOKEN_LENGTH);

        if (stack.size > 0) {
          Peek(&stack, token_on_stack);

          /* Условие извлечения токена со стека:
          - оператор выше по приоритету или равен, при этом,
            - если оператор на входе правоассоциативен, то токен со стека не
          достается (если приоритет равен, иначе, достается)
          */

          /*Если токен — оператор op1, то:
          Пока присутствует на вершине стека токен оператор op2, чей приоритет
          выше или равен приоритету op1, и при равенстве приоритетов op1
          является левоассоциативным: Переложить op2 из стека в выходную
          очередь; Положить op1 в стек.*/

          while ((PriorityDetector(token_on_stack[0]) >=
                  PriorityDetector(actual_token[0])) &&
                 actual_token[0] != '^') {
            Pop(&stack, token_on_stack);
            strcpy(postfix_math_expression->separate_tokens[p], token_on_stack);
            p++;
            memset(token_on_stack, 0, POSSIBLE_TOKEN_LENGTH);
            Peek(&stack, token_on_stack);
          }
        }

        Push(&stack, actual_token, BINARY_OPERATOR);
        break;
      }

      case PARENTHESES_OPEN: {
        // Если символ является открывающей скобкой, помещаем его в стек.
        if (*infix_math_expression->separate_tokens[i] == '(') {
          Push(&stack, infix_math_expression->separate_tokens[i], 0);
        }
        break;
      }

      case PARENTHESES_CLOSE: {
        Pop(&stack, token_on_stack);

        while (*token_on_stack != '(') {
          if (stack.size > 0) {
            strcpy(postfix_math_expression->separate_tokens[p], token_on_stack);
            p++;
            memset(token_on_stack, 0, POSSIBLE_TOKEN_LENGTH);
            Pop(&stack, token_on_stack);
          } else {
            ErrorMessageCreator("A problem with brackets has been detected.");
            is_trouble = 1;
            break;
          }
        }

        /*
          Если токен на вершине стека — функция, переложить её
          в выходную очередь.
        */
        memset(token_on_stack, 0, POSSIBLE_TOKEN_LENGTH);
        int operator_code = Peek(&stack, token_on_stack);
        /* printf("DBG. operator_code=%d, token=%s\n", operator_code,
                       token_on_stack);
        */
        if (operator_code == FUNCTIONS && token_on_stack[0] != '~') {
          Pop(&stack, token_on_stack);
          strcpy(postfix_math_expression->separate_tokens[p], token_on_stack);
          p++;
        }

        break;
      }

      default:
        break;
    }
    i++;
  }

  // Когда входная строка закончилась, выталкиваем все символы из стека в
  // выходную строку.
  while (stack.size) {
    memset(token_on_stack, 0, POSSIBLE_TOKEN_LENGTH);
    Pop(&stack, token_on_stack);
    strcpy(postfix_math_expression->separate_tokens[p], token_on_stack);
    p++;
  }
  return is_trouble;
}