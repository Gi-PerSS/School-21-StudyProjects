#ifndef S21_VIEW_SETTINGS_H_
#define S21_VIEW_SETTINGS_H_

#include <QDialog>
#include <QDir>
#include <QSettings>

namespace Ui {
class Settings;
}

namespace s21 {

/**
 * @class Settings
 * @brief Класс для управления настройками отображения.
 *
 * Этот класс представляет диалоговое окно, которое позволяет пользователю
 * настраивать параметры отображения, такие как цвета, размеры и типы элементов
 * модели, а также сохранять эти настройки в конфигурационный файл.
 */
class Settings : public QDialog {
  Q_OBJECT

 private:
  Ui::Settings* ui;  ///< Указатель на объект пользовательского интерфейса.
  QString config_file_;  ///< Путь к файлу конфигурации.
  QSettings* settings_;  ///< Объект для работы с настройками.

 public:
  /**
   * @brief Конструктор класса Settings.
   *
   * Инициализирует диалоговое окно настроек и загружает сохраненные настройки
   * из файла.
   *
   * @param parent Указатель на родительский виджет (по умолчанию nullptr).
   */
  explicit Settings(QWidget* parent = nullptr);

  /**
   * @brief Деструктор класса Settings.
   *
   * Освобождает ресурсы и сохраняет текущие настройки в файл.
   */
  ~Settings() override;

  /**
   * @brief Возвращает текущий цвет вершин.
   *
   * @return QColor Цвет вершин.
   */
  QColor getVertexColor() const;

  /**
   * @brief Возвращает текущий размер вершин.
   *
   * @return int Размер вершин.
   */
  int getVertexSize() const;

  /**
   * @brief Возвращает текущую форму вершин.
   *
   * @return int Форма вершин (0 - нет, 1 - точки, 2 - квадраты).
   */
  int getVertexShape() const;

  /**
   * @brief Возвращает текущий цвет ребер.
   *
   * @return QColor Цвет ребер.
   */
  QColor getEdgeColor() const;

  /**
   * @brief Возвращает текущую толщину ребер.
   *
   * @return int Толщина ребер.
   */
  int getEdgeWidth() const;

  /**
   * @brief Возвращает текущий тип линий ребер.
   *
   * @return int Тип линий (0 - сплошные, 1 - пунктирные).
   */
  int getEdgeType() const;

  /**
   * @brief Возвращает текущий цвет фона.
   *
   * @return QColor Цвет фона.
   */
  QColor getBgColor() const;

  /**
   * @brief Проверяет, включен ли режим центральной проекции.
   *
   * @return bool true, если включен режим центральной проекции, иначе false.
   */
  bool isCentralProjection() const;

 private:
  /**
   * @brief Загружает настройки из конфигурационного файла.
   */
  void loadSettings();

  /**
   * @brief Сохраняет текущие настройки в конфигурационный файл.
   */
  void saveSettings();

  /**
   * @brief Сбрасывает настройки до значений по умолчанию.
   */
  void setDefaultSettings();

 private slots:
  /**
   * @brief Применяет текущие настройки и закрывает диалог.
   */
  void applySettings();

  /**
   * @brief Уменьшает значение размера вершин.
   */
  void onVertexSizeDecrClicked();

  /**
   * @brief Увеличивает значение размера вершин.
   */
  void onVertexSizeIncrClicked();

  /**
   * @brief Уменьшает значение толщины ребер.
   */
  void onEdgeWidthDecrClicked();

  /**
   * @brief Увеличивает значение толщины ребер.
   */
  void onEdgeWidthIncrClicked();

  /**
   * @brief Закрывает диалог без сохранения изменений.
   */
  void onSetCancelClicked();

  /**
   * @brief Сбрасывает настройки до значений по умолчанию и применяет их.
   */
  void onSetDefaultClicked();

 signals:
  /**
   * @brief Сигнал для применения настроек.
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
  void onSetApplyClicked(QColor vertex_color, int vertex_size, int vertex_shape,
                         QColor edge_color, int edge_width, int edge_type,
                         QColor bg_color, bool central_projection);
};

}  // namespace s21

#endif  // S21_VIEW_SETTINGS_H_