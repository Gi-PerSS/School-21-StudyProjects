#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <stdexcept>
#include <string>

#include "../../Model/headers/backend.h"

namespace s21 {
class MVC_Controller {
 public:
  static std::string FromViewToModelTransceiver(std::string math_expression);
};
}  // namespace s21

#endif  // CONTROLLER_H
