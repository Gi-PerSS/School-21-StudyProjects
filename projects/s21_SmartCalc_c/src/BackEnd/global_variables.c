#include "smartcalc_backend_library.h"

/* порядок перечисления функций и операторов важен. То, что в начале должно там
 * же и оставаться.*/

char errors_in_actual_expression[ERROR_MESSAGES_LENGTH_MAX + 1] = {0};

const char possible_functions[][POSSIBLE_TOKEN_LENGTH + 1] = {
    "mod", "acos", "asin", "atan", "sqrt", "cos", "sin", "tan", "ln", "log"};

const char possible_characters[NUMBER_OF_POSSIBLE_CHARACTERS + 1] =
    "-+*/%^()0123456789. ";

const char possible_operators[NUMBER_OF_POSSIBLE_OPERATORS + 1] = "-+*/^%";
