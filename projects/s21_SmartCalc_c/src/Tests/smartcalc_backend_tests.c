#include <check.h>

#include "../BackEnd/smartcalc_backend_library.h"
// #include "../GUI/calculator_GUI.h"
/*=========================*/

START_TEST(ParenthesesChecker_Test) {
  ck_assert_int_eq(ParenthesesChecker("(1)"), 0);
  ck_assert_int_eq(ParenthesesChecker("((2))"), 0);
  ck_assert_int_eq(ParenthesesChecker("(3))"), 1);
  ck_assert_int_eq(ParenthesesChecker("))4(("), 1);
  ck_assert_int_eq(ParenthesesChecker(")(5)("), 1);

  char bad_math_expression[EXPRESSIONS_STRING_LENGTH] =
      "0.198574/"
      "sin(0.604423)*0.711897%0.475673*0.471105^((((((0.503837%0.844968)^0."
      "413608)^0.492537)+0.699855)/0.756441)-0.379324)*0.207333%0.802232/"
      "atan(0.920150)/"
      "acos(0.765118)^atan(0.632180)^0.176050^(((0.051649%0.583581)/"
      "0.638306)/"
      "0.762799)-sin(0.991863))";
  ck_assert_int_eq(ParenthesesChecker(bad_math_expression), 1);
}
END_TEST

START_TEST(DotChecker_Test) {
  ck_assert_int_eq(DotChecker("1111.1"), 0);
  ck_assert_int_eq(DotChecker("11111"), 0);
  ck_assert_int_eq(DotChecker("111.11.11"), 1);
  ck_assert_int_eq(DotChecker("111."), 1);
  ck_assert_int_eq(DotChecker(".111"), 1);
}

START_TEST(FunctionsNameChecker_Test) {
  const char functions_ok[EXPRESSIONS_STRING_LENGTH] = {
      "mod(1)+"
      "acos(1)+"
      "asin(1)+"
      "atan(1)+"
      "sqrt(1)+"
      "cos(1)+"
      "sin(1)+"
      "tan(1)+"
      "ln(1)+"
      "log(1)"};

  const char functions_bad_names[EXPRESSIONS_STRING_LENGTH] = {
      "mmod(1)+"
      "acos(1)+"
      "asin(1)+"
      "atan(1)+"
      "sqrt(1)+"
      "cos(1)+"
      "sin(1)+"
      "tan(1)+"
      "ln(1)+"
      "log(1)"};
  ck_assert_int_eq(FunctionsNameChecker(functions_ok), 0);
  ck_assert_int_eq(FunctionsNameChecker(functions_bad_names), 1);
}
END_TEST

START_TEST(ParentheseAfterFunctNameChecker_Test) {
  const char functions_ok[EXPRESSIONS_STRING_LENGTH] = {
      "mod(1)+"
      "acos(1)+"
      "asin(1)+"
      "atan(1)+"
      "sqrt(1)+"
      "cos(1)+"
      "sin(1)+"
      "tan(1)+"
      "ln(1)+"
      "log(1)"};

  const char functions_bad_names[EXPRESSIONS_STRING_LENGTH] = {
      "mod(1)+"
      "acos(1)+"
      "asin(1)+"
      "atan(1)+"
      "sqrt(1)+"
      "cos(1)+"
      "sin(1)+"
      "tan(1)+"
      "ln(1)+"
      "log(1))"};
  ck_assert_int_eq(ParentheseAfterFunctNameChecker(functions_ok), 0);
  ck_assert_int_eq(ParentheseAfterFunctNameChecker(functions_bad_names), 1);
}
END_TEST

START_TEST(OperatorsOrderChecker_Test) {
  ck_assert_int_eq(OperatorsOrderChecker("-1+2*3/4^5%6"), 0);
  ck_assert_int_eq(OperatorsOrderChecker("+1-2*3/4^5%6"), 0);
  ck_assert_int_eq(OperatorsOrderChecker("+1-2*3/4^5%6+"), 1);
  ck_assert_int_eq(OperatorsOrderChecker("++1-2*3/4^5%6+"), 1);
  ck_assert_int_eq(OperatorsOrderChecker("+1-2*3/4^5%6(+"), 1);
}
END_TEST

START_TEST(MathExpressionChecker_Test) {
  char math_expression[EXPRESSIONS_STRING_LENGTH] =
      "- 0.198574 / sin(0.604423) ";

  char bad_math_expression[EXPRESSIONS_STRING_LENGTH] =
      "0.198574/"
      "sin(0.604423)*0.711897%0.475673*0.471105^((((((0.503837%0.844968)^0."
      "413608)^0.492537)+0.699855)/0.756441)-0.379324)*0.207333%0.802232/"
      "atan(0.920150)/"
      "acos(0.765118)^atan(0.632180)^0.176050^(((0.051649%0.583581)/"
      "0.638306)/"
      "0.762799)-sin(0.991863))";

  ck_assert_int_eq(MathExpressionChecker(math_expression), 0);
  ck_assert_int_eq(MathExpressionChecker(bad_math_expression), 1);
}
END_TEST

START_TEST(InfixToPostfixTranslator_Test) {
  char t[][EXPRESSIONS_STRING_LENGTH + 1] = {
      "2^3^4",       "0*2^3^4+1", "1+sin(1-1)*2", "-(1+3)",
      "-(1+3)*5/11", "1%5",       "0*1/2*3",      ""};
  char t_reference[][EXPRESSIONS_STRING_LENGTH + 1] = {
      "234^^",     "0234^^*1+", "111-sin2*+", "13+~",
      "13+~5*11/", "15%",       "01*2/3*"};

  for (int i = 0; t[i][0] != '\0'; i++) {
    tokens_pack infix = {0};
    tokens_pack postfix = {0};
    char postfix_string[EXPRESSIONS_STRING_LENGTH + 1] = {0};
    TokenBreaker(t[i], &infix);
    InfixToPostfixTranslator(&infix, &postfix);
    DBG_MathExpressionFromTokens(postfix_string, &postfix);
    printf("==================================\n");
    printf("Start Math Expression   = '%s'\n", t[i]);
    printf("Postfix MUST BE:        = '%s'\n", t_reference[i]);
    printf("Postfix Math Expression = '%s'\n", postfix_string);
    ck_assert_str_eq(postfix_string, t_reference[i]);
  }
}

END_TEST

START_TEST(TokenBreakerTest_1_PARENTHESES_and_MATH_SIGNES) {
  {
    char math_expression[EXPRESSIONS_STRING_LENGTH] = "()+-*/";
    char math_expression_from_tokens[EXPRESSIONS_STRING_LENGTH] = "";
    tokens_pack separate_tokens = {0};
    TokenBreaker(math_expression, &separate_tokens);
    for (int i = 0; i < EXPRESSIONS_STRING_LENGTH; i++) {
      strcat(math_expression_from_tokens, separate_tokens.separate_tokens[i]);
    }

    printf("math_expression = %s\n", math_expression);
    printf("separate_tokens = %s\n", math_expression_from_tokens);
    ck_assert_str_eq(math_expression, math_expression_from_tokens);
    printf("\n");
  }
}
END_TEST

START_TEST(TokenBreakerTest_2_FUNCTIONS) {
  {
    char math_expression[EXPRESSIONS_STRING_LENGTH] =
        "cos()sin()tan()acos()asin()atan()sqrt()ln()log()";
    char math_expression_from_tokens[EXPRESSIONS_STRING_LENGTH] = "";

    tokens_pack separate_tokens = {0};
    TokenBreaker(math_expression, &separate_tokens);
    for (int i = 0; i < EXPRESSIONS_STRING_LENGTH; i++) {
      strcat(math_expression_from_tokens, separate_tokens.separate_tokens[i]);
    }

    printf("math_expression = %s\n", math_expression);
    printf("separate_tokens = %s\n", math_expression_from_tokens);
    ck_assert_str_eq(math_expression, math_expression_from_tokens);
    printf("\n");
  }
}
END_TEST

START_TEST(TokenBreakerTest_3_MOD) {
  {
    char math_expression[EXPRESSIONS_STRING_LENGTH] = "mod";
    char math_expression_from_tokens[EXPRESSIONS_STRING_LENGTH] = "";

    tokens_pack separate_tokens = {0};
    TokenBreaker(math_expression, &separate_tokens);
    for (int i = 0; i < EXPRESSIONS_STRING_LENGTH; i++) {
      strcat(math_expression_from_tokens, separate_tokens.separate_tokens[i]);
    }

    printf("math_expression = %s\n", math_expression);
    printf("separate_tokens = %s\n", math_expression_from_tokens);
    ck_assert_str_eq("%", math_expression_from_tokens);
    printf("\n");
  }
}
END_TEST

START_TEST(TokenBreakerTest_4_DIGITS) {
  {
    char math_expression[EXPRESSIONS_STRING_LENGTH] = "123.321(111)";
    char math_expression_from_tokens[EXPRESSIONS_STRING_LENGTH] = "";

    tokens_pack separate_tokens = {0};
    TokenBreaker(math_expression, &separate_tokens);
    for (int i = 0; i < EXPRESSIONS_STRING_LENGTH; i++) {
      strcat(math_expression_from_tokens, separate_tokens.separate_tokens[i]);
    }

    printf("math_expression = %s\n", math_expression);
    printf("separate_tokens = %s\n", math_expression_from_tokens);
    ck_assert_str_eq(math_expression, math_expression_from_tokens);
    printf("\n");
  }
}
END_TEST

START_TEST(TokenCodesTest_5) {
  {
    char math_expression[EXPRESSIONS_STRING_LENGTH] =
        "0.198574/"
        "sin(0.604423)*0.711897%0.475673*0.471105^((((((0.503837%0.844968)^0."
        "413608)^0.492537)+0.699855)/0.756441)-0.379324)*0.207333%0.802232/"
        "atan(0.920150)/"
        "acos(0.765118)^atan(0.632180)^0.176050^(((0.051649%0.583581)/"
        "0.638306)/"
        "0.762799)-sin(0.991863)";
    //    char math_expression_from_tokens[EXPRESSIONS_STRING_LENGTH] = "";

    tokens_pack separate_tokens = {0};
    TokenBreaker(math_expression, &separate_tokens);
    for (int i = 0; i < 255; i++) {
      if (*separate_tokens.separate_tokens[i] != '\0') {
        printf("Token = '%s', token_codes=%d\n",
               separate_tokens.separate_tokens[i],
               separate_tokens.token_codes[i]);
      }
    }
  }
}
END_TEST

START_TEST(TokenBreakerTest_5_GENERAL) {
  {
    char math_expression[EXPRESSIONS_STRING_LENGTH] =
        "0.198574/"
        "sin(0.604423)*0.711897%0.475673*0.471105^((((((0.503837%0.844968)^0."
        "413608)^0.492537)+0.699855)/0.756441)-0.379324)*0.207333%0.802232/"
        "atan(0.920150)/"
        "acos(0.765118)^atan(0.632180)^0.176050^(((0.051649%0.583581)/"
        "0.638306)/"
        "0.762799)-sin(0.991863)";
    char math_expression_from_tokens[EXPRESSIONS_STRING_LENGTH] = "";

    tokens_pack separate_tokens = {0};
    TokenBreaker(math_expression, &separate_tokens);
    for (int i = 0; i < EXPRESSIONS_STRING_LENGTH; i++) {
      strcat(math_expression_from_tokens, separate_tokens.separate_tokens[i]);
    }

    printf("math_expression = %s\n", math_expression);
    printf("separate_tokens = %s\n", math_expression_from_tokens);
    ck_assert_str_eq(math_expression, math_expression_from_tokens);
    printf("\n");
  }
}
END_TEST

START_TEST(Push_Pop_test) {
  {
    Stack t = {0};
    for (int i = 0; i < 255; i++) {
      char tt[POSSIBLE_TOKEN_LENGTH + 1] = "test";
      Push(&t, tt, 0);
      Pop(&t, tt);
      ck_assert_str_eq("test", tt);
    }
  }
}
END_TEST

START_TEST(Peek_test) {
  {
    Stack t = {0};
    for (int i = 0; i < 255; i++) {
      char tt[POSSIBLE_TOKEN_LENGTH + 1] = "test";
      Push(&t, tt, 0);
      Peek(&t, tt);
      //      printf("Peek.tst. i=%d\n", i);
      ck_assert_str_eq("test", tt);
    }
  }
}
END_TEST

void InASCIICalculation(char math_operator, double x, double y,
                        char *ascii_result) {
  memset(ascii_result, 0, DBL_MAX_LENGTH + 1);

  char ascii_x[DBL_MAX_LENGTH + 1] = {0};
  char ascii_y[DBL_MAX_LENGTH + 1] = {0};
  sprintf(ascii_x, "%.7f", x);
  sprintf(ascii_y, "%.7f", y);
  Stack t = {0};

  if (math_operator != '~' && math_operator != '@') {
    Push(&t, ascii_x, 0);
    Push(&t, ascii_y, 0);
  } else {
    Push(&t, ascii_x, 0);
  }

  RPC_BinaryOperators(math_operator, &t);
  Pop(&t, ascii_result);
}

void DoubleResultToASCIIReferenceResult(double reference_result,
                                        char *ascii_reference_result) {
  memset(ascii_reference_result, 0, DBL_MAX_LENGTH + 1);
  sprintf(ascii_reference_result, "%.7f", reference_result);
}

START_TEST(RPC_Operators_Test) {
  // #define number_of_tests 7
  double xx[7] = {-DBL_MAX, -1, -0.9, 0, 0.09, 1, DBL_MAX};
  char ascii_test_result[DBL_MAX_LENGTH + 1] = {0};
  char ascii_reference_result[DBL_MAX_LENGTH + 1] = {0};
  //  double x, y;
  double reference_result = 0;

  for (int i = 0; i < NUMBER_OF_POSSIBLE_OPERATORS; i++) {
    //    printf("x = %.7f\n", xx[i]);
    reference_result = xx[i] / 2;
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    InASCIICalculation('/', xx[i], 2, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = xx[i] * 2;
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    InASCIICalculation('*', xx[i], 2, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = xx[i] + xx[i];
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    InASCIICalculation('+', xx[i], xx[i], ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = xx[i] - xx[i];
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    InASCIICalculation('-', xx[i], xx[i], ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = -xx[i];
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    InASCIICalculation('~', xx[i], xx[i], ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = +xx[i];
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    InASCIICalculation('@', xx[i], xx[i], ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = pow(1, xx[i]);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    InASCIICalculation('^', 1, xx[i], ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);
  }
}
END_TEST

void DoubleXToASCIIResult(char *function_name, double x,
                          char *ascii_test_result) {
  char ascii_x[DBL_MAX_LENGTH + 1] = {0};
  sprintf(ascii_x, "%.7f", x);
  Stack stack = {0};
  Push(&stack, ascii_x, 0);
  RPC_Functions(function_name, &stack);
  memset(ascii_test_result, 0, DBL_MAX_LENGTH + 1);
  Pop(&stack, ascii_test_result);
}

START_TEST(RPC_Functions_Test) {
#define number_of_tests 5
  double xx[number_of_tests] = {-1, -0.9, 0, 0.09, 1};
  char ascii_test_result[DBL_MAX_LENGTH + 1] = {0};
  char ascii_reference_result[DBL_MAX_LENGTH + 1] = {0};
  double x = 0;
  double reference_result = 0;

  for (int i = 0; i < number_of_tests; i++) {
    //  printf("test pass\n");
    x = xx[i];
    reference_result = acos(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    DoubleXToASCIIResult("acos", x, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = asin(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    DoubleXToASCIIResult("asin", x, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = cos(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    DoubleXToASCIIResult("cos", x, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = sin(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    DoubleXToASCIIResult("sin", x, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = tan(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    DoubleXToASCIIResult("tan", x, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = atan(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    DoubleXToASCIIResult("atan", x, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    x = fabs(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);

    reference_result = log(x);
    DoubleResultToASCIIReferenceResult(reference_result,
                                       ascii_reference_result);
    DoubleXToASCIIResult("ln", x, ascii_test_result);
    ck_assert_str_eq(ascii_reference_result, ascii_test_result);
  }
}
END_TEST

START_TEST(PolishCalculator_Test) {
#define PolishCalculator_Tests_N 19
  /*
  The C function log is the natural logarithm, which mathematicians usually
  write as "ln".

  The C function log10 is the logarithm base 10, which is sometimes written
  "log".
  */

  char test_expressions[PolishCalculator_Tests_N][POSSIBLE_TOKEN_LENGTH + 1] = {
      "2*-3",      "-0-2",        "1+2",
      "6/2",       "2-3",         "1",
      "2",         "acos(0.7)",   "atan(0.6)",
      "sqrt(9)",   "cos(0.8)",    "sin(0.9)",
      "tan(-0.5)", "ln(1.1)",     "log(2.2)",
      "10 mod 3",  "-0.698461^2", "0.698461^sqrt(0.924092)",
      "56^(-1)"};

  double reference_results[] = {2 * -3,
                                -0 - 2,
                                1 + 2,
                                6 / 2,
                                2 - 3,
                                1,
                                2,
                                acos(0.7),
                                atan(0.6),
                                sqrt(9),
                                cos(0.8),
                                sin(0.9),
                                tan(-0.5),
                                log(1.1),
                                log10(2.2),
                                fmod(10, 3),
                                0.4878478,
                                0.70823000306974769114,
                                pow(56, (-1))};

  for (int i = 0; i < PolishCalculator_Tests_N; i++) {
    char ascii_reference_result[DBL_MAX_LENGTH] = {0};
    sprintf(ascii_reference_result, "%.7f", reference_results[i]);
    MathExpressionChecker(test_expressions[i]);
    tokens_pack infix = {0};
    printf("DBG. texp=%s\n", test_expressions[i]);
    TokenBreaker(test_expressions[i], &infix);
    //    DBG_TokenCodesPrinter(&infix, "infix");

    tokens_pack postfix = {0};
    InfixToPostfixTranslator(&infix, &postfix);
    //    DBG_TokenCodesPrinter(&postfix, "postfix");

    char ascii_result[DBL_MAX_LENGTH + 1] = {0};
    PolishCalculator(&postfix, ascii_result);

    printf(
        "==================================\nPolishCalculator. Test №%d\n"
        "==================================\n",
        i);
    printf("Start Math Expression   = '%s'\n", test_expressions[i]);
    printf("Result MUST BE:         = '%s'\n", ascii_reference_result);
    printf("Real result             = '%s'\n", ascii_result);

    double result = strtod(ascii_result, NULL);
    memset(ascii_result, 0, DBL_MAX_LENGTH + 1);
    sprintf(ascii_result, "%.7f", result);

    ck_assert_str_eq(ascii_reference_result, ascii_result);
  }
}
END_TEST

START_TEST(API_Test) {
#define API_Tests_N 21
  /*
  The C function log is the natural logarithm, which mathematicians usually
  write as "ln".

  The C function log10 is the logarithm base 10, which is sometimes written
  "log".
  */

  char test_expressions[][POSSIBLE_TOKEN_LENGTH + 1] = {
      "2*-3",      "-0-2",        "1+2",
      "6/2",       "2-3",         "1",
      "2",         "acos(0.7)",   "atan(0.6)",
      "sqrt(9)",   "cos(0.8)",    "sin(0.9)",
      "tan(-0.5)", "ln(1.1)",     "log(2.2)",
      "10 mod 3",  "-0.698461^2", "0.698461^sqrt(0.924092)",
      "56^(-1)",   "3*0.2",       "5ln"};

  double reference_results[] = {2 * -3,
                                -0 - 2,
                                1 + 2,
                                6 / 2,
                                2 - 3,
                                1,
                                2,
                                acos(0.7),
                                atan(0.6),
                                sqrt(9),
                                cos(0.8),
                                sin(0.9),
                                tan(-0.5),
                                log(1.1),
                                log10(2.2),
                                fmod(10, 3),
                                0.4878478,
                                0.70823000306974769114,
                                pow(56, (-1)),
                                3 * 0.2,
                                0};

  for (int i = 0; i < API_Tests_N; i++) {
    char ascii_reference_result[DBL_MAX_LENGTH + 1] = {0};
    sprintf(ascii_reference_result, "%.7f", reference_results[i]);

    char ascii_result[DBL_MAX_LENGTH + 1] = {0};
    SmartCalcBackEnd_API(test_expressions[i], ascii_result);
    printf(
        "==================================\nAPI. Test №%d\n"
        "==================================\n",
        i);
    printf("Start Math Expression   = '%s'\n", test_expressions[i]);
    printf("Result MUST BE:         = '%s'\n", ascii_reference_result);
    printf("Real result             = '%s'\n", ascii_result);

    double result = strtod(ascii_result, NULL);
    memset(ascii_result, 0, DBL_MAX_LENGTH + 1);
    sprintf(ascii_result, "%.7f", result);

    ck_assert_str_eq(ascii_reference_result, ascii_result);
  }
}
END_TEST

START_TEST(FunctionValueDefiner_Test) {
  printf("DBG. In test\n");
#define N_Tests 5
  char formulas[][EXPRESSIONS_STRING_LENGTH] = {"x", "-x", "x*2", "0.1-x",
                                                "x+x"};
  double x = 10.0000001;

  double answers[5] = {x, -x, x * 2, 0.1 - x, x + x};
  for (int i = 0; i < N_Tests; i++) {
    double test_answer = FunctionValueDefiner(x, formulas[i]);
    char ascii_result[DBL_MAX_LENGTH + 1] = {0};
    char ascii_reference_result[DBL_MAX_LENGTH + 1] = {0};
    sprintf(ascii_result, "%g", test_answer);
    sprintf(ascii_reference_result, "%g", answers[i]);
    printf(
        "==================================\nAPI. Test №%d\n"
        "==================================\n",
        i);
    printf("Start Math Expression   = '%s'\n", formulas[i]);
    printf("Result MUST BE:         = '%s'\n", ascii_reference_result);
    printf("Real result             = '%s'\n", ascii_result);
    ck_assert_str_eq(ascii_reference_result, ascii_result);
  }
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  TCase *TokenBreaker = tcase_create("TokenBreaker_tests");
  suite_add_tcase(s1, TokenBreaker);
  tcase_add_test(TokenBreaker, TokenBreakerTest_1_PARENTHESES_and_MATH_SIGNES);
  tcase_add_test(TokenBreaker, TokenBreakerTest_2_FUNCTIONS);
  tcase_add_test(TokenBreaker, TokenBreakerTest_3_MOD);
  tcase_add_test(TokenBreaker, TokenBreakerTest_4_DIGITS);
  tcase_add_test(TokenBreaker, TokenCodesTest_5);
  tcase_add_test(TokenBreaker, TokenBreakerTest_5_GENERAL);

  TCase *InfixToPostfixTranslator =
      tcase_create("InfixToPostfixTranslator_tests");
  suite_add_tcase(s1, InfixToPostfixTranslator);
  tcase_add_test(InfixToPostfixTranslator, InfixToPostfixTranslator_Test);

  TCase *StackFunctions = tcase_create("StackFunction_tests");
  suite_add_tcase(s1, StackFunctions);
  tcase_add_test(StackFunctions, Push_Pop_test);
  tcase_add_test(StackFunctions, Peek_test);

  TCase *MathExpressionChecker = tcase_create("MathExpressionChecker_tests");
  suite_add_tcase(s1, MathExpressionChecker);
  tcase_add_test(MathExpressionChecker, ParenthesesChecker_Test);
  tcase_add_test(MathExpressionChecker, DotChecker_Test);
  tcase_add_test(MathExpressionChecker, FunctionsNameChecker_Test);
  tcase_add_test(MathExpressionChecker, ParentheseAfterFunctNameChecker_Test);
  tcase_add_test(MathExpressionChecker, OperatorsOrderChecker_Test);
  tcase_add_test(MathExpressionChecker, MathExpressionChecker_Test);

  TCase *RPC = tcase_create("RPC_tests");
  suite_add_tcase(s1, RPC);
  tcase_add_test(RPC, RPC_Functions_Test);
  tcase_add_test(RPC, RPC_Operators_Test);
  tcase_add_test(RPC, PolishCalculator_Test);

  TCase *API = tcase_create("API_tests");
  suite_add_tcase(s1, API);
  tcase_add_test(API, API_Test);

  TCase *GUI = tcase_create("GUI_tests");
  suite_add_tcase(s1, GUI);
  tcase_add_test(GUI, FunctionValueDefiner_Test);
  /*
  ======================
    void srunner_run_all (SRunner * sr, enum print_output print_mode);

    void srunner_run (SRunner *sr, const char *sname, const char *tcname,
                      enum print_output print_mode);
  ======================
  */
  srunner_run_all(sr, CK_ENV);
  //  srunner_run(sr, "Core", "GUI_tests", CK_VERBOSE);
  //  srunner_run(sr, "Core", "InfixToPostfixTranslator_tests", CK_VERBOSE);
  //  srunner_run(sr, "Core", "MathExpressionChecker_tests", CK_VERBOSE);
  //  srunner_run(sr, "Core", "RPC_tests", CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
