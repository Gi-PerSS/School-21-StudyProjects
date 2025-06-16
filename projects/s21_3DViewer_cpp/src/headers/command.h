/**
 * @file command.h
 * @brief Заголовочный файл, содержащий объявления классов команд для выполнения
 * трансформаций над моделью.
 *
 * Этот файл содержит объявления абстрактного класса Command и его потомков,
 * которые реализуют паттерн Command. Каждый класс-команда инкапсулирует
 * конкретное действие (например, перемещение, поворот или масштабирование
 * модели).
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "../headers/model_parser.h"

namespace s21 {

/**
 * @class Command
 * @brief Абстрактный базовый класс для всех команд.
 *
 * Класс Command определяет интерфейс для выполнения команд над моделью. Все
 * конкретные команды наследуются от него.
 */
class Command {
 public:
  /**
   * @brief Виртуальный деструктор.
   */
  virtual ~Command() {}

  /**
   * @brief Выполняет команду над моделью.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  virtual void execute(ParserModel& model) = 0;
};

/**
 * @class RotateXCommand
 * @brief Команда для поворота модели вокруг оси X.
 */
class RotateXCommand : public Command {
 public:
  /**
   * @brief Конструктор класса RotateXCommand.
   *
   * @param angle Угол поворота в радианах.
   */
  RotateXCommand(double angle) : angle_(angle) {}

  /**
   * @brief Выполняет поворот модели вокруг оси X.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  void execute(ParserModel& model) override;

 private:
  double angle_;  ///< Угол поворота в радианах.
};

/**
 * @class RotateYCommand
 * @brief Команда для поворота модели вокруг оси Y.
 */
class RotateYCommand : public Command {
 public:
  /**
   * @brief Конструктор класса RotateYCommand.
   *
   * @param angle Угол поворота в радианах.
   */
  RotateYCommand(double angle) : angle_(angle) {}

  /**
   * @brief Выполняет поворот модели вокруг оси Y.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  void execute(ParserModel& model) override;

 private:
  double angle_;  ///< Угол поворота в радианах.
};

/**
 * @class RotateZCommand
 * @brief Команда для поворота модели вокруг оси Z.
 */
class RotateZCommand : public Command {
 public:
  /**
   * @brief Конструктор класса RotateZCommand.
   *
   * @param angle Угол поворота в радианах.
   */
  RotateZCommand(double angle) : angle_(angle) {}

  /**
   * @brief Выполняет поворот модели вокруг оси Z.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  void execute(ParserModel& model) override;

 private:
  double angle_;  ///< Угол поворота в радианах.
};

/**
 * @class MoveXCommand
 * @brief Команда для перемещения модели по оси X.
 */
class MoveXCommand : public Command {
 public:
  /**
   * @brief Конструктор класса MoveXCommand.
   *
   * @param value Значение перемещения.
   */
  MoveXCommand(double value) : value_(value) {}

  /**
   * @brief Выполняет перемещение модели по оси X.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  void execute(ParserModel& model) override;

 private:
  double value_;  ///< Значение перемещения.
};

/**
 * @class MoveYCommand
 * @brief Команда для перемещения модели по оси Y.
 */
class MoveYCommand : public Command {
 public:
  /**
   * @brief Конструктор класса MoveYCommand.
   *
   * @param value Значение перемещения.
   */
  MoveYCommand(double value) : value_(value) {}

  /**
   * @brief Выполняет перемещение модели по оси Y.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  void execute(ParserModel& model) override;

 private:
  double value_;  ///< Значение перемещения.
};

/**
 * @class MoveZCommand
 * @brief Команда для перемещения модели по оси Z.
 */
class MoveZCommand : public Command {
 public:
  /**
   * @brief Конструктор класса MoveZCommand.
   *
   * @param value Значение перемещения.
   */
  MoveZCommand(double value) : value_(value) {}

  /**
   * @brief Выполняет перемещение модели по оси Z.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  void execute(ParserModel& model) override;

 private:
  double value_;  ///< Значение перемещения.
};

/**
 * @class ScaleCommand
 * @brief Команда для масштабирования модели.
 */
class ScaleCommand : public Command {
 public:
  /**
   * @brief Конструктор класса ScaleCommand.
   *
   * @param ratio Коэффициент масштабирования.
   */
  ScaleCommand(double ratio) : ratio_(ratio) {}

  /**
   * @brief Выполняет масштабирование модели.
   *
   * @param model Ссылка на объект ParserModel, над которым выполняется команда.
   */
  void execute(ParserModel& model) override;

 private:
  double ratio_;  ///< Коэффициент масштабирования.
};

}  // namespace s21

#endif  // COMMAND_H_