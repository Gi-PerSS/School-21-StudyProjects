#ifndef OBSERVER_H
#define OBSERVER_H

#include "model_parser.h"

namespace s21 {

/**
 * @class ModelObserver
 * @brief Интерфейс для наблюдателей модели.
 *
 * Определяет метод onModelChanged, который вызывается при изменении данных
 * модели.
 */
class ModelObserver {
 public:
  /**
   * @brief Виртуальный деструктор.
   */
  virtual ~ModelObserver() = default;

  /**
   * @brief Вызывается при изменении данных модели.
   *
   * @param data Структура ObjData с обновленными данными модели.
   */
  virtual void onModelChanged(const ObjData& data) = 0;
};

}  // namespace s21

#endif  // OBSERVER_H