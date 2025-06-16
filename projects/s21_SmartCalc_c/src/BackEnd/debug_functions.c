#include "smartcalc_backend_library.h"

/* Дебаг-функции */

/*===> Дебаг-функции */

void DBG_MathExpressionFromTokens(char* math_expression_holder,
                                  tokens_pack* tokens) {
  memset(math_expression_holder, 0, EXPRESSIONS_STRING_LENGTH + 1);
  for (int i = 0; i < EXPRESSIONS_STRING_LENGTH; i++) {
    strcat(math_expression_holder, tokens->separate_tokens[i]);
  }
}

void DBG_StackPrinter(Stack* stack) {
  printf("Stack from DOWN =-> TOP:\n");
  for (int i = 0; i <= (stack->size - 1); i++) {
    printf("'%s' | ", stack->data[i]);
  }
  printf("\n");
}

void DBG_TokenCodesPrinter(tokens_pack* tokens, const char* info_message) {
  printf("%s\n", info_message);
  printf("Token codes in array: \n");
  int i = 0;
  while (strcmp(tokens->separate_tokens[i], "")) {
    printf("%s\t==> %d\n", tokens->separate_tokens[i], tokens->token_codes[i]);
    i++;
  }

  printf("\n");
}