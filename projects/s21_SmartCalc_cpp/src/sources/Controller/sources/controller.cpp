#include "../headers/controller.h"

// Это файл-прокладка типа контроллер.
namespace s21 {
std::string MVC_Controller::FromViewToModelTransceiver(
    std::string math_expression) {
  std::string result;
  try {
    result = UltraCalculatorsBackEnd::UltraCalculatorsAPI(math_expression);
    return result;
  } catch (const std::invalid_argument& e) {
    throw;  // проброс исключения дальше по стеку вызовов
    result = "0";
    return result;
  }
}
}  // namespace s21
