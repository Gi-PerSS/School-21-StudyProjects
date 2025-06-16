#include <map>
#include <sstream>

#include "../headers/backend.h"

namespace s21 {
const std::map<std::string, int> UltraCalculatorsBackEnd::kFunctionsMap = {
    {"acos", RPC_FunctionsCodes::kAcos}, {"cos", RPC_FunctionsCodes::kCos},
    {"asin", RPC_FunctionsCodes::kAsin}, {"sin", RPC_FunctionsCodes::kSin},
    {"atan", RPC_FunctionsCodes::kAtan}, {"tan", RPC_FunctionsCodes::kTan},
    {"sqrt", RPC_FunctionsCodes::kSqrt}, {"log", RPC_FunctionsCodes::kLog},
    {"ln", RPC_FunctionsCodes::kLn}};

void UltraCalculatorsBackEnd::RPC_FunctionsDataChecker(
    const std::string& actual_token, double x) {
  int case_code = kFunctionsMap.at(actual_token);

  switch (case_code) {
    case kAcos: {
      if (x < -1 || x > 1) {
        throw std::invalid_argument("x out of range: 'acos' -> (-1 <= x <= 1)");
      }
    } break;
    case kAsin: {
      if (x < -1 || x > 1) {
        throw std::invalid_argument("x out of range: 'asin' -> (-1 <= x <= 1)");
      }
    } break;
    case kSqrt: {
      if (x < 0) {
        throw std::invalid_argument("x out of range: 'sqrt' -> (x >= 0)");
      }
    } break;
    case kLn: {
      if (x < 0) {
        throw std::invalid_argument("x out of range: 'ln' -> (x >= 0)");
      }
    } break;
    case kLog: {
      if (x < 0) {
        throw std::invalid_argument("x out of range: 'log' -> (x >= 0)");
      }
    } break;
    default: {
      // No exeptions for other.
    } break;
  }
}

double UltraCalculatorsBackEnd::DoublesRounder(double x, int signs_after_dot) {
  /* Умножаем число на 10 в степени желаемого числа знаков после запятой,
   * округляем к ближайшему целому и делим на это же число. */
  int t = 10 ^ signs_after_dot;
  double rounded_x = round(x * t) / t;
  return rounded_x;
}

void UltraCalculatorsBackEnd::RPC_Functions(const std::string& actual_token,
                                            std::stack<std::string>& Stack) {
  std::string ascii_double = Stack.top();
  Stack.pop();

  double x = strtod(ascii_double.c_str(), NULL);
  double result = 0;
  std::string ascii_result = {0};

  int case_code = kFunctionsMap.at(actual_token);

  switch (case_code) {
    case kAcos: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = acos(x);
    } break;
    case kCos: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = cos(x);
    } break;
    case kAsin: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = asin(x);
    } break;
    case kSin: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = sin(x);
    } break;
    case kAtan: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = atan(x);
    } break;
    case kTan: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = tan(x);
    } break;
    case kSqrt: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = sqrt(x);
    } break;
    case kLn: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = log(x);
    } break;
    case kLog: {
      RPC_FunctionsDataChecker(actual_token, x);
      result = log10(x);
    } break;
    default: {
      std::cerr << "DBG. Something went wrong in RPC_Functions. Stop\n";
      std::terminate();
    } break;
  }
  ascii_result = DoubleToStringWithPrecision(result);
  Stack.push(ascii_result);
}

void UltraCalculatorsBackEnd::RPC_Operators(const std::string& actual_token,
                                            std::stack<std::string>& Stack) {
  double x = 0;
  double y = 0;
  double result = 0;

  std::string ascii_x = "";
  std::string ascii_y = "";
  std::string ascii_result = "";

  if (actual_token[0] == '~' || actual_token[0] == '@') {
    // достаем из стека 1 операнд
    ascii_x = Stack.top();
    Stack.pop();
    x = strtod(ascii_x.c_str(), NULL);
  } else {
    // иначе, 2.
    ascii_y = Stack.top();
    Stack.pop();
    y = strtod(ascii_y.c_str(), NULL);
    ascii_x = Stack.top();
    Stack.pop();
    x = strtod(ascii_x.c_str(), NULL);
  }

  int math_operator = actual_token[0];
  switch (math_operator) {
    case '-': {
      result = x - y;
      break;
    }
    case '+': {
      result = x + y;
      break;
    }
    case '/': {
      if (y != 0) {
        result = x / y;
      } else {
        throw std::invalid_argument("Division by zero.");
      }
      break;
    }
    case '*': {
      result = x * y;
      break;
    }
    case 'm': {
      result = fmod(x, y);
      break;
    }
    case '^': {
      result = pow(x, y);
      break;
    }
    case '~': {
      result = -x;
      break;
    }
    case '@': {
      result = x;
      break;
    }

    default: {
      std::cerr << "DBG. Something went wrong in RPC_Operators. Stop\n";
      std::terminate();
    } break;
  }
  ascii_result = DoubleToStringWithPrecision(result);
  Stack.push(ascii_result);
}

std::string UltraCalculatorsBackEnd::ReversePolishCalculator(
    const std::vector<std::string>& postfix_tokens_pack) {
  std::stack<std::string> Stack;

  auto actual_position = postfix_tokens_pack.begin();
  while (actual_position != postfix_tokens_pack.end()) {
    std::string actual_token = *actual_position;
    int case_code = TokenTypeDetector(actual_token);

    switch (case_code) {
      case kNumber: {
        if (actual_position + 1 != postfix_tokens_pack.end()) {
          std::string next_token = *(actual_position + 1);
          if (next_token == "~") {
            std::string t = "-";
            t += actual_token;
            actual_token = t;
            actual_position++;
          }
        }

        Stack.push(actual_token);
      } break;
      case kFunctions: {
        RPC_Functions(actual_token, Stack);
      } break;
      case kBinaryOperators: {
        RPC_Operators(actual_token, Stack);
      } break;
      default: {
        std::cerr << "DBG. Something went wrong in Polish Calculator. Stop.\n";
        std::terminate();
      } break;
    }
    actual_position++;
  }

  std::string ascii_result = Stack.top();
  Stack.pop();
  UltraCalculatorsBackEnd::RPC_CommaToPointConverter(ascii_result);
  UltraCalculatorsBackEnd::RPC_InsignificantZerosTrimmer(ascii_result);
  return ascii_result;
}

void UltraCalculatorsBackEnd::RPC_CommaToPointConverter(
    std::string& math_expression) {
  for (int i = 0; math_expression[i]; i++) {
    if (math_expression[i] == ',') {
      math_expression[i] = '.';
    }
  }
}

void UltraCalculatorsBackEnd::RPC_InsignificantZerosTrimmer(
    std::string& ascii_double) {
  size_t t = 0;
  t = ascii_double.find_last_not_of('0') + 1;
  ascii_double.erase(t, std::string::npos);
  if (ascii_double.back() == '.') {
    ascii_double.pop_back();
  }
}

std::string UltraCalculatorsBackEnd::DoubleToStringWithPrecision(
    double x, int precision) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(precision) << x;
  std::string result = ss.str();
  return result;
}
}  // namespace s21