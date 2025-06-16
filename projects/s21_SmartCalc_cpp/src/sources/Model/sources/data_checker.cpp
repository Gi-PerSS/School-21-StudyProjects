#include "../headers/backend.h"
namespace s21 {
void UltraCalculatorsBackEnd::DotCorrectnessChecker(
    const std::string& math_expression) {
  /*
  Проверка на правильность точки:
- до и после точки любое количество цифр и первый символ
перед/после ними - не точка.
*/
  bool is_trouble = 0;
  auto position_in_line = math_expression.begin();
  while (position_in_line != math_expression.end()) {
    char c = *position_in_line;
    if (c == '.') {
      if (position_in_line + 1 == math_expression.end() ||
          position_in_line == math_expression.begin()) {
        is_trouble = 1;
      } else {
        auto forward = position_in_line + 1;
        auto backward = position_in_line - 1;
        while (isdigit(*forward) && forward != math_expression.end()) {
          forward++;
        }
        while (isdigit(*backward) && backward != math_expression.begin()) {
          backward--;
        }
        if (*forward == '.' || *backward == '.') {
          is_trouble = 1;
        }
      }
      if (is_trouble) {
        throw std::invalid_argument(
            "We have a problen with a point in the number.");
      }
    }
    position_in_line++;
  }
}  // namespace
   // UltraCalculatorsBackEnd::DotCorrectnessChecker(conststd::string&math_expression)

void UltraCalculatorsBackEnd::FunctionNamesChecker(
    const std::string& math_expression) {
  auto position_in_line = math_expression.begin();
  while (position_in_line != math_expression.end()) {
    std::string function_name = "";
    if (isalpha(*position_in_line)) {
      while (isalpha(*position_in_line)) {
        function_name += *position_in_line;
        position_in_line++;
      }

      if (function_name != "mod") {
        if (!kFunctionsMap.count(function_name) || *position_in_line != '(') {
          throw std::invalid_argument("Incorrect function name. Check it out.");
        }
      }

      position_in_line--;
    }
    position_in_line++;
  }
}

void UltraCalculatorsBackEnd::PossibleCharactersChecker(
    const std::string& math_expression) {
  // допустимые символы
  std::regex regex("^[a-zA-Z0-9+\\-*/^(). ]+$");
  bool is_data_ok = 0;
  is_data_ok = regex_match(math_expression, regex);
  if (!is_data_ok) {
    throw std::invalid_argument(
        "Incorrect characters in the string. Check it out.");
  }
}

void UltraCalculatorsBackEnd::BracketsRigthOrderChecker(
    const std::string& math_expression) {
  bool is_trouble = 0;
  auto position_in_line = math_expression.begin();
  std::stack<char> Stack;
  while (position_in_line != math_expression.end()) {
    char actual_char = *position_in_line;
    switch (actual_char) {
      case '(': {
        Stack.push(actual_char);
      } break;
      case ')': {
        if (!Stack.empty()) {
          Stack.pop();
        } else {
          is_trouble = 1;
        }
      } break;
      default:
        break;
    }
    position_in_line++;
  }
  if (!Stack.empty() || is_trouble) {
    throw std::invalid_argument("The problem with brackets. Check it out.");
  }
}

void UltraCalculatorsBackEnd::OperatorsOrderChecker(
    const std::string& math_expression) {
  bool is_trouble = 0;
  std::vector<std::string> tokens =
      UltraCalculatorsBackEnd::TokenBreaker(math_expression);
  is_trouble = (UltraCalculatorsBackEnd::TokenTypeDetector(tokens.back()) !=
                    UltraCalculatorsBackEnd::kCloseBracket &&
                UltraCalculatorsBackEnd::TokenTypeDetector(tokens.back()) !=
                    UltraCalculatorsBackEnd::kNumber);
  int t_previous = 0;  // маркер начала строки
  for (auto it = tokens.begin(); it != tokens.end() && !is_trouble; it++) {
    int t = TokenTypeDetector(*it);
    switch (t) {
      case kNumber: {
        /*
        если токен число, то перед ним возможны:
        - открывающая скобка
        - унарный знак
        - бинарный знак
        - начало строки
        */
        if (t_previous != 0 && t_previous != kUnaryOperator &&
            t_previous != kBinaryOperators && t_previous != kOpenBracket) {
          throw std::invalid_argument(
              "Error in:\n\t OperatorsOrderChecker\n\t case: kNumber");
        }
      } break;
      case kUnaryOperator: {
        /*
        если токен унарный знак, перед ним возможны:
    - бинарный знак
    - открывающая скобка
    - начало строки
        */
        if (t_previous != 0 && t_previous != kBinaryOperators &&
            t_previous != kOpenBracket) {
          throw std::invalid_argument(
              "Error in:\n\t OperatorsOrderChecker\n\t case: kUnaryOperator");
        }
      } break;

      case kBinaryOperators: {
        /*
      если токен бинарный знак, перед ним возможны:
    - число
    - закрывающая скобка
        */
        if (t_previous != kNumber && t_previous != kCloseBracket) {
          throw std::invalid_argument(
              "Error in:\n\t OperatorsOrderChecker\n\t case: kBinaryOperators");
        }
      } break;

      case kOpenBracket: {
        /*
если токен открывающая скобка, перед ней возможны:
    - бинарный знак
    - унарный знак
    - функция
    - начало строки
    - открывающая скобка
        */
        if (t_previous != kBinaryOperators && t_previous != kUnaryOperator &&
            t_previous != kFunctions && t_previous != 0 &&
            t_previous != kOpenBracket) {
          throw std::invalid_argument(
              "Error in:\n\t OperatorsOrderChecker\n\t case: kOpenBracket");
        }
      } break;

      case kCloseBracket: {
        /*
      если токен закрывающая скобка, перед ней возможны:
    - число
    - закрывающая скобка
        */
        if (t_previous != kNumber && t_previous != kCloseBracket) {
          throw std::invalid_argument(
              "Error in:\n\t OperatorsOrderChecker\n\t case: kCloseBracket");
        }
      } break;

      default:
        break;
    }
    t_previous = t;
  }

  if (is_trouble) {
    throw std::invalid_argument(
        "The problem is with the order of things. Check it out.");
  }
}

void UltraCalculatorsBackEnd::MathExpressionChecker(
    const std::string& math_expression) {
  UltraCalculatorsBackEnd::PossibleCharactersChecker(math_expression);
  UltraCalculatorsBackEnd::FunctionNamesChecker(math_expression);
  UltraCalculatorsBackEnd::DotCorrectnessChecker(math_expression);
  UltraCalculatorsBackEnd::BracketsRigthOrderChecker(math_expression);
  UltraCalculatorsBackEnd::OperatorsOrderChecker(math_expression);
}
}  // namespace s21
