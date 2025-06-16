
#ifndef SRC_CORRECT_MATH_EXPRESSION_GENERATOR_H
#define SRC_CORRECT_MATH_EXPRESSION_GENERATOR_H

char LastCharInLine(char* math_expression);
int RandomTokenGenerator(int is_subexpression_possible);
int OperationOnlyGenerator(void);
double RandomDoubleGenerator(void);
void ExpressionsFileWriter(char* actual_math_expresion);
void NestedExpressionGenerator(char* math_expression, char* temp_expression);
int MathExpressionsGenerator(int token_code, char* math_expression);
void CEO();

#endif