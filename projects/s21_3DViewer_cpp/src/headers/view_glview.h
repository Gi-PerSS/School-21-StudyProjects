#ifndef S21_VIEW_GLVIEW_H_
#define S21_VIEW_GLVIEW_H_

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPoint>

#include "./command.h"
#include "./model_parser.h"
#include "observer.h"

namespace s21 {

/**
 * @class GLView
 * @brief Класс для отрисовки 3D-моделей с использованием OpenGL.
 *
 * Этот класс наследует QOpenGLWidget и реализует интерфейс ModelObserver.
 * Он отвечает за отрисовку 3D-моделей, обработку событий мыши и колеса,
 * а также применение настроек отображения.
 */
class GLView : public QOpenGLWidget,
               protected QOpenGLFunctions,
               public ModelObserver {
  Q_OBJECT

 private:
  ObjData data_;  ///< Данные модели для отрисовки.
  QColor vertex_color_;  ///< Цвет вершин.
  int vertex_size_;      ///< Размер вершин.
  int vertex_shape_;  ///< Форма вершин (0 - нет, 1 - точки, 2 - квадраты).
  QColor edge_color_;  ///< Цвет ребер.
  int edge_width_;     ///< Толщина ребер.
  int edge_type_;  ///< Тип линий ребер (0 - сплошные, 1 - пунктирные).
  QColor bg_color_;  ///< Цвет фона.
  bool central_projection_;  ///< Режим проекции (true - центральная, false -
                             ///< параллельная).
  QPoint last_pos_;  ///< Последняя позиция курсора для обработки событий мыши.
  ParserModel* model_;  ///< Указатель на модель данных.

 protected:
  /**
   * @brief Инициализирует OpenGL-функции.
   */
  void initializeGL() override;

  /**
   * @brief Обрабатывает изменение размеров виджета.
   *
   * @param w Новая ширина виджета.
   * @param h Новая высота виджета.
   */
  void resizeGL(int w, int h) override;

  /**
   * @brief Отрисовывает содержимое виджета OpenGL.
   */
  void paintGL() override;

  /**
   * @brief Обрабатывает нажатие кнопки мыши.
   *
   * @param event Указатель на объект события мыши.
   */
  void mousePressEvent(QMouseEvent* event) override;

  /**
   * @brief Обрабатывает движение мыши.
   *
   * @param event Указатель на объект события мыши.
   */
  void mouseMoveEvent(QMouseEvent* event) override;

  /**
   * @brief Обрабатывает вращение колеса мыши.
   *
   * @param event Указатель на объект события колеса мыши.
   */
  void wheelEvent(QWheelEvent* event) override;

 public:
  /**
   * @brief Конструктор класса GLView.
   *
   * Инициализирует виджет OpenGL с базовыми настройками отображения.
   *
   * @param parent Указатель на родительский виджет (по умолчанию nullptr).
   */
  explicit GLView(QWidget* parent = nullptr);

  /**
   * @brief Конструктор класса GLView с привязкой к модели.
   *
   * Инициализирует виджет OpenGL и связывает его с моделью данных.
   *
   * @param model Ссылка на объект ParserModel, содержащий данные модели.
   * @param parent Указатель на родительский виджет (по умолчанию nullptr).
   */
  explicit GLView(ParserModel& model, QWidget* parent = nullptr);

  /**
   * @brief Деструктор класса GLView.
   */
  ~GLView() override = default;

  /**
   * @brief Устанавливает модель данных для отрисовки.
   *
   * @param model Ссылка на объект ParserModel, содержащий данные модели.
   */
  void setModel(ParserModel& model);

  /**
   * @brief Устанавливает данные модели для отрисовки.
   *
   * @param data Структура ObjData, содержащая вершины и ребра модели.
   */
  void setData(const ObjData& data);

  /**
   * @brief Применяет настройки отображения.
   *
   * @param vertex_color Цвет вершин.
   * @param vertex_size Размер вершин.
   * @param vertex_shape Форма вершин (0 - нет, 1 - точки, 2 - квадраты).
   * @param edge_color Цвет ребер.
   * @param edge_width Толщина ребер.
   * @param edge_type Тип линий ребер (0 - сплошные, 1 - пунктирные).
   * @param bg_color Цвет фона.
   * @param central_projection Режим проекции (true - центральная, false -
   * параллельная).
   */
  void applySettings(QColor vertex_color, int vertex_size, int vertex_shape,
                     QColor edge_color, int edge_width, int edge_type,
                     QColor bg_color, bool central_projection);

  /**
   * @brief Обновляет состояние анимации.
   *
   * @param angle Угол поворота в градусах.
   */
  void updateAnimation(float angle);

  /**
   * @brief Обрабатывает изменения данных модели.
   *
   * @param data Структура ObjData, содержащая новые данные модели.
   */
  void onModelChanged(const ObjData& data) override;

 signals:
  /**
   * @brief Сигнал для запроса кадра.
   *
   * @param frame Изображение текущего состояния OpenGL-виджета.
   */
  void requestFrame(QImage frame);

  /**
   * @brief Сигнал для уведомления об изменении углов вращения.
   *
   * @param x Угол поворота вокруг оси X (в градусах).
   * @param y Угол поворота вокруг оси Y (в градусах).
   */
  void rotationChanged(float x, float y);
};

}  // namespace s21

#endif  // S21_VIEW_GLVIEW_H_