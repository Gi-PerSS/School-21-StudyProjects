#include "smartcalc_backend_library.h"
/* Стек */

int Push(Stack* stack, const char* value, int token_code) {
  int is_trouble = 0;

  if (stack->size >= STACK_MAX_SIZE) {
    //    printf("Attempt to push in full stack.\n");
    is_trouble = PUSH_IN_FULL_STACK;
  } else {
    strcpy(stack->data[stack->size], value);
    stack->token_codes[stack->size] = token_code;
    stack->size++;
  }
  return is_trouble;
}

int Pop(Stack* stack, char* value_holder) {
  // Возвращает код токена на стеке или код ошибки, если стек пуст.
  int token_code = 0;
  if (stack->size == 0) {
    //    printf("Attempt to pop from empty stack.\n");
    token_code = POP_FROM_EMPTY_STACK;
  } else {
    stack->size--;
    strcpy(value_holder, stack->data[stack->size]);
    token_code = stack->token_codes[stack->size];
  }
  return token_code;
}

int Peek(Stack* stack, char* value_holder) {
  int token_code = 0;
  if (stack->size == 0) {
    //    printf("Attempt to peek from empty stack.\n");
    token_code = PEEK_FROM_EMPTY_STACK;
  } else {
    strcpy(value_holder, stack->data[stack->size - 1]);
    token_code = stack->token_codes[stack->size - 1];
  }
  return token_code;
}
