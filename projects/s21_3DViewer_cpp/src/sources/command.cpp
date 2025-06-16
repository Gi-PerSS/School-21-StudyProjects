/**
 * @file command.cpp
 * @brief Реализация методов классов команд для выполнения трансформаций над
 * моделью.
 *
 * Этот файл содержит реализацию методов классов, которые наследуются от
 * абстрактного класса Command. Каждый класс представляет конкретную команду
 * (например, поворот или перемещение модели). Все команды работают с объектом
 * ParserModel, изменяя его состояние.
 */

#include "../headers/command.h"

#include <iostream>

namespace s21 {

/**
 * @brief Выполняет команду поворота модели вокруг оси X.
 *
 * Метод вызывает метод rotateX объекта ParserModel, передавая угол поворота.
 *
 * @param model Ссылка на объект ParserModel, над которым выполняется команда.
 */
void RotateXCommand::execute(ParserModel& model) {
  // std::cout << "Executing RotateXCommand with angle: " << angle_ <<
  // std::endl;
  model.rotateX(angle_);
}

/**
 * @brief Выполняет команду поворота модели вокруг оси Y.
 *
 * Метод вызывает метод rotateY объекта ParserModel, передавая угол поворота.
 *
 * @param model Ссылка на объект ParserModel, над которым выполняется команда.
 */
void RotateYCommand::execute(ParserModel& model) {
  // std::cout << "Executing RotateYCommand with angle: " << angle_ <<
  // std::endl;
  model.rotateY(angle_);
}

/**
 * @brief Выполняет команду поворота модели вокруг оси Z.
 *
 * Метод вызывает метод rotateZ объекта ParserModel, передавая угол поворота.
 *
 * @param model Ссылка на объект ParserModel, над которым выполняется команда.
 */
void RotateZCommand::execute(ParserModel& model) {
  // std::cout << "Executing RotateZCommand with angle: " << angle_ <<
  // std::endl;
  model.rotateZ(angle_);
}

/**
 * @brief Выполняет команду перемещения модели по оси X.
 *
 * Метод вызывает метод moveX объекта ParserModel, передавая значение
 * перемещения.
 *
 * @param model Ссылка на объект ParserModel, над которым выполняется команда.
 */
void MoveXCommand::execute(ParserModel& model) {
  // std::cout << "Executing MoveXCommand with value: " << value_ << std::endl;
  model.moveX(value_);
}

/**
 * @brief Выполняет команду перемещения модели по оси Y.
 *
 * Метод вызывает метод moveY объекта ParserModel, передавая значение
 * перемещения.
 *
 * @param model Ссылка на объект ParserModel, над которым выполняется команда.
 */
void MoveYCommand::execute(ParserModel& model) {
  // std::cout << "Executing MoveYCommand with value: " << value_ << std::endl;
  model.moveY(value_);
}

/**
 * @brief Выполняет команду перемещения модели по оси Z.
 *
 * Метод вызывает метод moveZ объекта ParserModel, передавая значение
 * перемещения.
 *
 * @param model Ссылка на объект ParserModel, над которым выполняется команда.
 */
void MoveZCommand::execute(ParserModel& model) {
  // std::cout << "Executing MoveZCommand with value: " << value_ << std::endl;
  model.moveZ(value_);
}

/**
 * @brief Выполняет команду масштабирования модели.
 *
 * Метод вызывает метод scale объекта ParserModel, передавая коэффициент
 * масштабирования.
 *
 * @param model Ссылка на объект ParserModel, над которым выполняется команда.
 */
void ScaleCommand::execute(ParserModel& model) {
  // std::cout << "Executing ScaleCommand with ratio: " << ratio_ << std::endl;
  model.scale(ratio_);
}

}  // namespace s21