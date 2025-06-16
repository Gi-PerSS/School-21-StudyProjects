#include "../headers/backend.h"

namespace s21 {
void UltraCalculatorsBackEnd::SpacesTrimmer(std::string& math_expression) {
  // Удаление пробелов. Перемещаем все пробелы в конец строки и удаляем его
  auto t = remove_if(math_expression.begin(), math_expression.end(), ::isspace);
  math_expression.erase(t, math_expression.end());
}  // namespace
   // UltraCalculatorsBackEnd::SpacesTrimmer(std::string&math_expression)

void UltraCalculatorsBackEnd::StringToLowerCase(std::string& string) {
  for (size_t i = 0; i < string.length(); i++) {
    string[i] = tolower(string[i]);
  }
}

std::string UltraCalculatorsBackEnd::FunctionsCallManager(
    std::string& math_expression) {
  UltraCalculatorsBackEnd::RPC_CommaToPointConverter(math_expression);
  UltraCalculatorsBackEnd::StringToLowerCase(math_expression);
  UltraCalculatorsBackEnd::SpacesTrimmer(math_expression);
  UltraCalculatorsBackEnd::ExponentialTranslator(math_expression);
  UltraCalculatorsBackEnd::MathExpressionChecker(math_expression);

  std::vector<std::string> tokens_temp;
  tokens_temp = TokenBreaker(math_expression);
  tokens_temp = InfixToPostfixTranslator(tokens_temp);
  std::string answer = "";
  answer = ReversePolishCalculator(tokens_temp);

  return answer;
}

void UltraCalculatorsBackEnd::ExponentialTranslator(
    std::string& math_expression) {
  UltraCalculatorsBackEnd::DotCorrectnessChecker(math_expression);
  // шаблон для поиска числа в экспоненциальной записи
  std::regex e_notation_pattern("[\\d\\.]+[eE][+-]\\d+");
  std::smatch match;
  while (std::regex_search(math_expression, match, e_notation_pattern)) {
    // извлекаем найденное число из строки
    std::string matched_e_number = match.str();
    // преобразуем найденное число в тип double
    double number = std::stod(matched_e_number);

    // Заменяем число на обычную запись, константа - максимальное значение
    // мантиссы, 10 - для дополнительных символов (точки, знака и т.д.)
    char buffer[DBL_MAX_10_EXP + 10];
    std::sprintf(buffer, "%.7f", number);
    math_expression.replace(match.position(), match.length(), buffer);
  }
}

std::string UltraCalculatorsBackEnd::UltraCalculatorsAPI(
    std::string& math_expression) {
  setlocale(LC_NUMERIC, "C");
  std::string answer = "";

  try {
    answer = FunctionsCallManager(math_expression);
  } catch (const std::invalid_argument& e) {
    //  std::cerr << e.what() << "\n";
    throw;  // проброс исключения дальше по стеку вызовов
  }
  return answer;
}
}  // namespace s21
