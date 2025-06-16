#include <ctype.h>

#include "../headers/backend.h"
namespace s21 {

// std::string StringJoiner(const std::vector<std::string>& strings,
//                          const std::string& delimiter = "") {
//   std::ostringstream result;

//   for (size_t i = 0; i < strings.size(); ++i) {
//     if (i > 0) {
//       result << delimiter;
//     }
//     result << strings[i];
//   }

//   return result.str();
// }

const char* UltraCalculatorsBackEnd::TB_NumbersHandler(
    const char* actual_position_in_line,
    std::vector<std::string>& result_tokens) {
  std::string t = "";
  while ((isdigit(*actual_position_in_line)) ||
         *actual_position_in_line == '.') {
    t += *actual_position_in_line;
    actual_position_in_line++;
  }
  actual_position_in_line = actual_position_in_line - 1;
  result_tokens.push_back(t);

  return actual_position_in_line;
}

bool UltraCalculatorsBackEnd::UnarySignsDetector(
    const std::string& math_expression, const char* actual_position_in_line) {
  bool is_unary = 0;
  const std::string kUnaryMarkers = "/*-+^(";

  char previous_character = *(actual_position_in_line - 1);
  if (actual_position_in_line == math_expression.c_str() ||
      kUnaryMarkers.find(previous_character) != std::string::npos) {
    is_unary = 1;
  }

  return is_unary;
}

void UltraCalculatorsBackEnd::TB_OneCharacterTokensHandler(
    const std::string& math_expression, const char* actual_position_in_line,
    std::vector<std::string>& result_tokens) {
  char actual_character = *actual_position_in_line;
  // Проверка на унарные плюс-минус

  if (actual_character != '-' && actual_character != '+') {
    // все кроме плюса и минуса пушим в токены сразу
    std::string t(1, actual_character);
    result_tokens.push_back(t);
  } else {
    bool is_unary =
        UnarySignsDetector(math_expression, actual_position_in_line);

    if (!is_unary) {
      // Если знак не унарный, пушим не разбирая
      std::string t(1, actual_character);
      result_tokens.push_back(t);
    } else {
      // унарное маркируем
      if (actual_character == '-') {
        // идентификатор унарного минуса
        result_tokens.push_back("~");
      } else {
        // идентификатор унарного плюса
        result_tokens.push_back("@");
      }
    }
  }
}

const char* UltraCalculatorsBackEnd::TB_FunctionsHandler(
    const char* actual_position_in_line,
    std::vector<std::string>& result_tokens) {
  std::string t = "";
  while (isalpha(*actual_position_in_line)) {
    t += *actual_position_in_line;
    actual_position_in_line++;
  }
  actual_position_in_line = actual_position_in_line - 1;
  result_tokens.push_back(t);

  return actual_position_in_line;
}

std::vector<std::string> UltraCalculatorsBackEnd::TokenBreaker(
    const std::string math_expression) {
  // Предполагается, что строка поступающая на вход проверена и некорректные
  // символы невозможны.

  std::vector<std::string> result_tokens;
  const std::string kOneCharacterTokens = "/*-+^()";
  const char* actual_position_in_line = math_expression.c_str();

  while (*actual_position_in_line) {
    char actual_character = *actual_position_in_line;

    if (isdigit(actual_character)) {
      /* Числа */
      actual_position_in_line =
          TB_NumbersHandler(actual_position_in_line, result_tokens);
    } else if (kOneCharacterTokens.find(actual_character) !=
               std::string::npos) {
      /* Односимвольные токены */
      /* константа npos означает неудачу в поиске. */
      TB_OneCharacterTokensHandler(math_expression, actual_position_in_line,
                                   result_tokens);
    } else if (isalpha(actual_character)) {
      /* Функции */
      actual_position_in_line =
          TB_FunctionsHandler(actual_position_in_line, result_tokens);
    }
    actual_position_in_line++;
  }
  return result_tokens;
}
}  // namespace s21