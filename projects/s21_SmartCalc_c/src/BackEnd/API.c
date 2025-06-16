#include "smartcalc_backend_library.h"

// ===>API
int SmartCalcBackEnd_API(char math_expression[EXPRESSIONS_STRING_LENGTH + 1],
                         char result_holder[DBL_MAX_LENGTH + 1]) {
  /*директива необходима для корректной работы функции strtod (представление
   * десятичной точки как точки, а не запятой)*/
  setlocale(LC_NUMERIC, "C");
  Comma2DotConverter(math_expression);
  int is_trouble = MathExpressionChecker(math_expression);
  char t_result_holder[DBL_MAX_LENGTH + 1] = {0};
  SpaceTrimmer(math_expression);
  tokens_pack infix = {0};
  is_trouble = is_trouble || TokenBreaker(math_expression, &infix);
  tokens_pack postfix = {0};
  is_trouble = is_trouble || InfixToPostfixTranslator(&infix, &postfix);
  memset(t_result_holder, 0, DBL_MAX_LENGTH + 1);
  is_trouble = is_trouble || PolishCalculator(&postfix, t_result_holder);
  if (!is_trouble) {
    memset(result_holder, 0, DBL_MAX_LENGTH + 1);
    strcpy(result_holder, t_result_holder);
  } else {
    *result_holder = '0';
  }
  //  DBG_TokenCodesPrinter(&postfix, "postfix");
  return is_trouble;
}
