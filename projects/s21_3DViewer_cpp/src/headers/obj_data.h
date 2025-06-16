#ifndef OBJ_DATA_H
#define OBJ_DATA_H

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

}  // namespace s21

#endif  // OBJ_DATA_H