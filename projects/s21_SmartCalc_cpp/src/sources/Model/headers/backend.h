#ifndef BACKEND_H_
#define BACKEND_H_
#include <algorithm>
#include <cctype>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
namespace s21 {
class UltraCalculatorsBackEnd {
 public:
  static std::string UltraCalculatorsAPI(std::string& math_expression);
  //   static std::string TB_UnaryExpressionToNegativeConverter(
  //       const std::string& right_math_expression);

 private:
  // Константы
  enum RPC_FunctionsCodes {
    kAcos = 1,
    kCos,
    kAsin,
    kSin,
    kAtan,
    kTan,
    kSqrt,
    kLog,
    kLn
  };

  static const std::map<std::string, int> kFunctionsMap;
  enum ItPT_CaseCodes {
    kFunctions = 1,
    kBinaryOperators,
    kUnaryOperators,
    kOpenBracket,
    kCloseBracket,
    kNumber,
    kUnaryOperator
  };

  // API
  static std::string FunctionsCallManager(std::string& math_expression);

  // DataCheckers
  static void MathExpressionChecker(const std::string& math_expression);
  static void FunctionNamesChecker(const std::string& math_expression);
  static void DotCorrectnessChecker(const std::string& math_expression);
  static void PossibleCharactersChecker(const std::string& math_expression);
  static void BracketsRigthOrderChecker(const std::string& math_expression);
  static void OperatorsOrderChecker(const std::string& math_expression);
  static void SpacesTrimmer(std::string& math_expression);
  static void StringToLowerCase(std::string& string);
  static void ExponentialTranslator(std::string& math_expression);

  // TokenBreaker

  static std::vector<std::string> TokenBreaker(std::string math_expression);
  static const char* TB_NumbersHandler(const char* actual_position_in_line,
                                       std::vector<std::string>& result_tokens);
  static bool UnarySignsDetector(const std::string& math_expression,
                                 const char* actual_position_in_line);
  static void TB_OneCharacterTokensHandler(
      const std::string& math_expression, const char* actual_position_in_line,
      std::vector<std::string>& result_tokens);
  static const char* TB_FunctionsHandler(
      const char* actual_position_in_line,
      std::vector<std::string>& result_tokens);

  // InfixToPostfixTranslator
  static std::string Peek(std::stack<std::string> Stack);
  static int TokenTypeDetector(const std::string& token);
  static int PriorityDetector(const std::string& math_operator);
  static std::vector<std::string> InfixToPostfixTranslator(
      const std::vector<std::string>& infix_tokens_pack);

  static std::vector<std::string> UnarySignsInNumberTokenMover(
      const std::vector<std::string>& infix_tokens_pack);

  // RPC - PostfixCalculator
  static std::string ReversePolishCalculator(
      const std::vector<std::string>& postfix_tokens_pack);
  static void RPC_Functions(const std::string& actual_token,
                            std::stack<std::string>& Stack);
  static void RPC_FunctionsDataChecker(const std::string& token, double x);
  static void RPC_Operators(const std::string& actual_token,
                            std::stack<std::string>& Stack);
  static void RPC_CommaToPointConverter(std::string& math_expression);
  static void RPC_InsignificantZerosTrimmer(std::string& ascii_double);
  static std::string DoubleToStringWithPrecision(double x, int precision = 7);
  static double DoublesRounder(double x, int signs_after_dot);
  // Дебаг-функции
  static void TokensPrinter(std::vector<std::string> tokens_pack,
                            const std::string& source_expression);
  static void TokensPrinter(std::vector<std::string> tokens_pack);
  static void StackPrinter(std::stack<std::string> Stack, const char* dbg_msg);
};

}  // namespace s21

#endif  // BACKEND_H_