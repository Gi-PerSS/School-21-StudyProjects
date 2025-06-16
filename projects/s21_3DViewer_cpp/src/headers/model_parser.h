/**
 * @file model_parser.h
 * @brief Заголовочный файл, содержащий объявления классов для работы с
 * 3D-моделями.
 *
 * Этот файл содержит объявления структуры ObjData и класса ParserModel, которые
 * используются для загрузки, хранения и модификации данных 3D-моделей. Класс
 * ParserModel также реализует паттерн Observer для уведомления наблюдателей об
 * изменениях данных модели.
 */

#ifndef S21_MODEL_PARSER_H_
#define S21_MODEL_PARSER_H_

#include <string>
#include <vector>

namespace s21 {

/**
 * @struct ObjData
 * @brief Структура для хранения данных 3D-модели.
 *
 * Содержит вершины, ребра и их количество для представления 3D-модели.
 */
struct ObjData {
  std::vector<double> vertices;  ///< Вектор вершин модели (x, y, z координаты).
  std::vector<int> edges;  ///< Вектор ребер модели (индексы вершин).
  int vertex_count;  ///< Количество вершин в модели.
  int edge_count;    ///< Количество ребер в модели.

  /**
   * @brief Конструктор по умолчанию.
   *
   * Инициализирует количество вершин и ребер нулями.
   */
  ObjData() : vertex_count(0), edge_count(0) {}
};

/**
 * @class ModelObserver
 * @brief Интерфейс для наблюдателей модели.
 *
 * Определяет метод onModelChanged, который вызывается при изменении данных
 * модели.
 */
class ModelObserver;

/**
 * @class ParserModel
 * @brief Класс для управления данными 3D-модели.
 *
 * Реализует загрузку данных из файла OBJ, выполнение трансформаций
 * (перемещение, поворот, масштабирование) и уведомление наблюдателей об
 * изменениях данных модели.
 */
class ParserModel {
 private:
  ObjData data_;                           ///< Данные модели.
  std::vector<ModelObserver*> observers_;  ///< Список наблюдателей.
  double scale_;  ///< Текущий масштаб модели.
  double move_x_, move_y_, move_z_;  ///< Текущие значения перемещения модели.
  double rotate_x_, rotate_y_, rotate_z_;  ///< Текущие углы поворота модели.

 public:
  /**
   * @brief Конструктор класса ParserModel.
   *
   * Инициализирует начальные значения масштаба, перемещений и поворотов модели.
   */
  ParserModel();

  /**
   * @brief Деструктор класса ParserModel.
   */
  ~ParserModel() = default;

  /**
   * @brief Загружает данные модели из файла OBJ.
   *
   * @param file_path Путь к файлу OBJ.
   * @throws std::runtime_error Если файл не удается открыть или данные
   * некорректны.
   */
  void loadFromFile(const std::string& file_path);

  /**
   * @brief Добавляет наблюдателя для уведомления об изменениях модели.
   *
   * @param observer Указатель на объект, реализующий интерфейс ModelObserver.
   */
  void addObserver(ModelObserver* observer);

  /**
   * @brief Удаляет наблюдателя из списка.
   *
   * @param observer Указатель на объект, реализующий интерфейс ModelObserver.
   */
  void removeObserver(ModelObserver* observer);

  /**
   * @brief Уведомляет всех наблюдателей об изменении данных модели.
   */
  void notifyObservers();

  /**
   * @brief Возвращает текущие данные модели.
   *
   * @return const ObjData& Ссылка на структуру ObjData с данными модели.
   */
  const ObjData& getData() const;

  /**
   * @brief Перемещает модель по оси X.
   *
   * @param value Значение перемещения.
   */
  void moveX(double value);

  /**
   * @brief Перемещает модель по оси Y.
   *
   * @param value Значение перемещения.
   */
  void moveY(double value);

  /**
   * @brief Перемещает модель по оси Z.
   *
   * @param value Значение перемещения.
   */
  void moveZ(double value);

  /**
   * @brief Поворачивает модель вокруг оси X.
   *
   * @param angle Угол поворота в радианах.
   */
  void rotateX(double angle);

  /**
   * @brief Поворачивает модель вокруг оси Y.
   *
   * @param angle Угол поворота в радианах.
   */
  void rotateY(double angle);

  /**
   * @brief Поворачивает модель вокруг оси Z.
   *
   * @param angle Угол поворота в радианах.
   */
  void rotateZ(double angle);

  /**
   * @brief Масштабирует модель.
   *
   * @param ratio Коэффициент масштабирования. Должен быть положительным.
   * @throws std::runtime_error Если коэффициент масштабирования меньше или
   * равен нулю.
   */
  void scale(double ratio);

  /**
   * @brief Возвращает текущий угол поворота модели вокруг оси X.
   *
   * @return double Угол поворота в радианах.
   */
  double getRotateX() const { return rotate_x_; }

  /**
   * @brief Возвращает текущий угол поворота модели вокруг оси Y.
   *
   * @return double Угол поворота в радианах.
   */
  double getRotateY() const { return rotate_y_; }

  /**
   * @brief Возвращает текущий угол поворота модели вокруг оси Z.
   *
   * @return double Угол поворота в радианах.
   */
  double getRotateZ() const { return rotate_z_; }
};

}  // namespace s21

#endif  // S21_MODEL_PARSER_H_