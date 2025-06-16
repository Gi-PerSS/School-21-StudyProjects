#include "../headers/backend.h"

namespace s21 {
int UltraCalculatorsBackEnd::PriorityDetector(
    const std::string& math_operator) {
  int priority = 0;
  int m_operator = math_operator[0];

  switch (m_operator) {
    case '~':
    case '^': {
      priority = 3;
      break;
    }
    case '/':
    case 'm':
    case '*': {
      priority = 2;
      break;
    }
    case '+':
    case '-': {
      priority = 1;
      break;
    }
    default:
      break;
  }

  return priority;
}

int UltraCalculatorsBackEnd::TokenTypeDetector(const std::string& token) {
  int token_type = 0;
  const std::string kBinaryOperatorsSet = "/*-+^";
  if (token[0] == '(') {
    token_type = kOpenBracket;
  } else if (token[0] == ')') {
    token_type = kCloseBracket;
  } else if (isalpha(token[0]) && token == "mod") {
    token_type = kBinaryOperators;
  } else if (isalpha(token[0]) && token != "mod") {
    token_type = kFunctions;
  } else if (isdigit(token[0])) {
    token_type = kNumber;
  } else if (token[0] == '-' && isdigit(token[1])) {
    token_type = kNumber;
  } else if (kBinaryOperatorsSet.find(token[0]) != std::string::npos) {
    token_type = kBinaryOperators;
  } else if (token[0] == '~' || token[0] == '@') {
    token_type = kUnaryOperator;
  } else {
    std::cerr << "DBG. Something wrong in TokenTypeDetector. Stop.\n";
    std::cerr << "DBG. Token=" << (int)token[0] << "\n";
    std::terminate();
  }

  return token_type;
}

std::string UltraCalculatorsBackEnd::Peek(std::stack<std::string> Stack) {
  if (!Stack.empty()) {
    return Stack.top();
  } else {
    return "\0";
  }
}

std::vector<std::string> UltraCalculatorsBackEnd::UnarySignsInNumberTokenMover(
    const std::vector<std::string>& infix_tokens_pack) {
  // Перемещаем унарный минус в следующий за ним токен с числом

  std::string token_on_stack = "";
  std::vector<std::string> converted_infix_tokens_pack(
      infix_tokens_pack.size());

  auto ifx_actual_position = infix_tokens_pack.begin();
  auto converted_ifx_actual_position = converted_infix_tokens_pack.begin();
  size_t number_of_deletion = 0;
  while (ifx_actual_position != infix_tokens_pack.end()) {
    if (*ifx_actual_position == "~") {
      std::string t = "-";
      ifx_actual_position++;
      t += *ifx_actual_position;
      *converted_ifx_actual_position = t;
      number_of_deletion++;
    } else {
      *converted_ifx_actual_position = *ifx_actual_position;
    }

    ifx_actual_position++;
    converted_ifx_actual_position++;
  }

  size_t new_size = converted_infix_tokens_pack.size() - number_of_deletion;
  converted_infix_tokens_pack.resize(new_size);

  return converted_infix_tokens_pack;
}

std::vector<std::string> UltraCalculatorsBackEnd::InfixToPostfixTranslator(
    const std::vector<std::string>& src_infix_tokens_pack) {
  // проверяем на существование унарного минуса и перемещаем его в токен с
  // числом если есть
  auto it = std::find(src_infix_tokens_pack.begin(),
                      src_infix_tokens_pack.end(), "~");
  std::vector<std::string> infix_tokens_pack;
  if (it != src_infix_tokens_pack.end() &&
      TokenTypeDetector(*(it + 1)) == kNumber) {
    infix_tokens_pack = UnarySignsInNumberTokenMover(src_infix_tokens_pack);
  } else {
    infix_tokens_pack = src_infix_tokens_pack;
  }

  //  TokensPrinter(infix_tokens_pack, "DBG. Print");
  std::stack<std::string> Stack;
  std::string token_on_stack = "";
  std::vector<std::string> postfix_tokens_pack;
  auto actual_position = infix_tokens_pack.begin();
  while (actual_position != infix_tokens_pack.end()) {
    std::string actual_token = *actual_position;

    int case_code = TokenTypeDetector(actual_token);
    switch (case_code) {
      case kFunctions: {
        if (actual_token != "@") {
          Stack.push(actual_token);
        }
      } break;
      case kNumber: {
        postfix_tokens_pack.push_back(actual_token);
      } break;
      case kBinaryOperators: {
        if (!Stack.empty()) {
          token_on_stack = Stack.top();
          while ((UltraCalculatorsBackEnd::PriorityDetector(token_on_stack) >=
                  UltraCalculatorsBackEnd::PriorityDetector(actual_token)) &&
                 actual_token != "^") {
            token_on_stack = Stack.top();
            Stack.pop();
            postfix_tokens_pack.push_back(token_on_stack);
            token_on_stack = UltraCalculatorsBackEnd::Peek(Stack);
          }
        }
        Stack.push(actual_token);
      } break;
      case kOpenBracket: {
        Stack.push(actual_token);
      } break;
      case kCloseBracket: {
        token_on_stack = Stack.top();
        Stack.pop();
        while (token_on_stack != "(") {
          if (!Stack.empty()) {
            postfix_tokens_pack.push_back(token_on_stack);
            token_on_stack = Stack.top();
            Stack.pop();
          } else {
            std::cerr << "DBG. Problem with brackets. Stop."
                      << "\n";
            std::terminate();
          }
        }
        token_on_stack = Peek(Stack);
        if (token_on_stack != "") {
          int operator_type =
              UltraCalculatorsBackEnd::TokenTypeDetector(token_on_stack);
          if (operator_type == kFunctions && token_on_stack != "~") {
            token_on_stack = Stack.top();
            Stack.pop();
            postfix_tokens_pack.push_back(token_on_stack);
          }
        }

      } break;
      default:
        break;
    }
    actual_position++;
  }
  while (!Stack.empty()) {
    token_on_stack = Stack.top();
    Stack.pop();
    postfix_tokens_pack.push_back(token_on_stack);
  }

  return postfix_tokens_pack;
}
}  // namespace s21