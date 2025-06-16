#include "../headers/backend.h"

namespace s21 {
void UltraCalculatorsBackEnd::StackPrinter(std::stack<std::string> Stack,
                                    const char* dbg_msg) {
  std::cout << dbg_msg << "\n";
  while (!Stack.empty()) {
    std::cout << Stack.top() << " | ";
    Stack.pop();
  }
}  // namespace
   // UltraCalculatorsBackEnd::StackPrinter(std::stack<std::string>Stack,constchar*dbg_msg)

void UltraCalculatorsBackEnd::TokensPrinter(std::vector<std::string> tokens_pack,
                                     const std::string& source_expression) {
  std::cout << source_expression << ", токены:\n";
  for (const auto& token : tokens_pack) {
    std::cout << token << '\n';
  }
  std::cout << "=============\n";
}

void UltraCalculatorsBackEnd::TokensPrinter(std::vector<std::string> tokens_pack) {
  std::cout << "Токены:\n";
  for (const auto& token : tokens_pack) {
    std::cout << token << '\n';
  }
  std::cout << "=============\n";
}
}  // namespace s21
