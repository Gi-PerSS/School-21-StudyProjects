#include "smartcalc_backend_library.h"

// ===> Function graph formula parser
double FunctionValueDefiner(double x, const char* function_formula) {
  char t[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  //  char x[DBL_MAX_LENGTH] = {0};
  char math_expression[EXPRESSIONS_STRING_LENGTH + 1] = {0};

  char* actual_position = (char*)function_formula;
  while (*actual_position) {
    if (*actual_position == 'x' || *actual_position == 'X') {
      sprintf(t, "%g", x);
      strcat(math_expression, t);
    } else {
      t[0] = *actual_position;
      strcat(math_expression, t);
    }
    memset(t, 0, EXPRESSIONS_STRING_LENGTH);
    actual_position++;
  }

  double y = 0;
  char ascii_y[DBL_MAX_LENGTH + 1] = {0};
  SmartCalcBackEnd_API(math_expression, ascii_y);
  y = strtod(ascii_y, NULL);
  return y;
}
