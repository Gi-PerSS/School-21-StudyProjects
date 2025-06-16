#ifndef SRC_BACKEND_SMARTCALC_BACKEND_LIBRARY_H
#define SRC_BACKEND_SMARTCALC_BACKEND_LIBRARY_H

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*библиотека необходима для правильной обработки чисел с точкой, поступающих из
 * GTK*/
#include <locale.h>

#define DBL_MAX_LENGTH 333
#define EXPRESSIONS_STRING_LENGTH 255
#define POSSIBLE_TOKEN_LENGTH DBL_MAX_LENGTH
#define NUMBER_OF_POSSIBLE_FUNCTION 10
#define NUMBER_OF_POSSIBLE_CHARACTERS 20
#define NUMBER_OF_POSSIBLE_OPERATORS 6
// #define END_OF_TOKENS "END"

// Error codes
#define ERROR_MESSAGES_LENGTH_MAX 333
#define ERROR_STRING_LENGTH_MAX 55
extern const char error_messages[][ERROR_STRING_LENGTH_MAX + 1];
extern char errors_in_actual_expression[ERROR_MESSAGES_LENGTH_MAX + 1];

#define WRONG_DATA_IN_LINE 11
#define PARENTHESES_PROBLEM 22
#define POP_FROM_EMPTY_STACK 111
#define PUSH_IN_FULL_STACK 222
#define PEEK_FROM_EMPTY_STACK 333

enum token_codes {
  PARENTHESES_OPEN = 1,
  PARENTHESES_CLOSE,
  DIGITS,
  FUNCTIONS,
  POW,
  MATH_SIGNES,
  MOD,
  BINARY_OPERATOR,
  UNARY_OPERATOR
};
enum function_codes { ACOS = 1, ASIN, ATAN, SQRT, COS, SIN, TAN, LN, LOG };
extern const char possible_functions[][POSSIBLE_TOKEN_LENGTH + 1];
extern const char possible_characters[NUMBER_OF_POSSIBLE_CHARACTERS + 1];
extern const char possible_operators[NUMBER_OF_POSSIBLE_OPERATORS + 1];

// для передачи массива в функцию
typedef struct tokens_pack {
  char separate_tokens[EXPRESSIONS_STRING_LENGTH + 1]
                      [EXPRESSIONS_STRING_LENGTH + 1];
  int token_codes[EXPRESSIONS_STRING_LENGTH];
} tokens_pack;

// Построение графика функции
double FunctionValueDefiner(double x, const char* function_formula);
// стек
#define STACK_MAX_SIZE (DBL_MAX_LENGTH + 1)
typedef struct Stack_tag {
  char data[STACK_MAX_SIZE][DBL_MAX_LENGTH + 1];
  int token_codes[EXPRESSIONS_STRING_LENGTH];
  int size;
} Stack;
int SmartCalcBackEnd_API(char math_expression[EXPRESSIONS_STRING_LENGTH + 1],
                         char result_holder[DBL_MAX_LENGTH + 1]);
int RPC_Functions(char* function_name, Stack* working_stack);
int RPC_BinaryOperators(char math_operator, Stack* stack);
int PolishCalculator(tokens_pack* postfix_math_expression, char* result_holder);
void CommaToPointConverter(char* math_expression);
void InsignificantZerosTrimmer(char* ascii_double);
void SpaceTrimmer(char* math_expression);
int MathExpressionChecker(char* math_expression);
int ParenthesesChecker(const char* math_expression);
int DotChecker(const char* math_expression);
int FunctionsNameChecker(const char* math_expression);
int ParentheseAfterFunctNameChecker(const char* math_expression);
int OperatorsOrderChecker(const char* math_expression);
int GeneralOrderChecker(char* math_expression);
int Push(Stack* stack, const char* value, int token_code);
int Pop(Stack* stack, char* value_holder);
int Peek(Stack* stack, char* value_holder);

void ErrorMessageCreator(const char* error_message);
// void ErrorHandler(int error_code);
int InfixToPostfixTranslator(tokens_pack* infix_math_expression,
                             tokens_pack* postfix_math_expression);
int TokenBreaker(const char* math_expression, tokens_pack* separate_tokens);
int TokenCodeDetector(char* token);
void Comma2DotConverter(char* math_expression);
// Дебаг-функции
void DBG_MathExpressionFromTokens(char* math_expression_holder,
                                  tokens_pack* tokens);
void DBG_StackPrinter(Stack* stack);

void DBG_TokenCodesPrinter(tokens_pack* tokens, const char* info_message);
#endif