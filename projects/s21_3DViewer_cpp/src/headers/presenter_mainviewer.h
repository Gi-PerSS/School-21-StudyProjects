#ifndef S21_PRESENTER_MAINVIEWER_H_
#define S21_PRESENTER_MAINVIEWER_H_

#include <QImage>
#include <QMainWindow>
#include <QTimer>
#include <memory>
#include <vector>

#include "../headers/command.h"
#include "../headers/model_parser.h"
#include "../headers/observer.h"
#include "../headers/view_glview.h"
#include "../headers/view_settings.h"
#include "QtGifImage-master/src/gifimage/qgifimage.h"

namespace Ui {
class MainViewer;  // Предварительное объявление для UI
}

namespace s21 {

/**
 * @class MainViewer
 * @brief Главный класс приложения, управляющий интерфейсом и логикой работы с
 * 3D-моделями.
 *
 * Этот класс отвечает за загрузку моделей, выполнение трансформаций
 * (перемещение, поворот, масштабирование), настройку отображения, создание
 * анимаций и сохранение скриншотов или GIF-анимаций.
 */
class MainViewer : public QMainWindow {
  Q_OBJECT

 private:
  Ui::MainViewer* ui;  ///< Указатель на объект пользовательского интерфейса.
  ParserModel model_;  ///< Модель данных для работы с 3D-объектами.
  GLView* gl_widget_;  ///< Виджет OpenGL для отрисовки модели.
  Settings* settings_dialog_;  ///< Диалоговое окно настроек.
  QTimer* animation_timer_;  ///< Таймер для управления анимацией.
  QGifImage* gif_;  ///< Объект для создания GIF-анимаций.
  std::vector<QImage> gif_frames_;  ///< Вектор кадров для GIF-анимации.
  std::vector<std::unique_ptr<Command>>
      animation_commands_;  ///< Команды для анимации.
  size_t current_command_index_;  ///< Индекс текущей команды анимации.
  QString gif_file_path_;  ///< Путь для сохранения GIF-файла.

 public:
  /**
   * @brief Конструктор класса MainViewer.
   *
   * Инициализирует главное окно приложения, настраивает соединения сигналов и
   * слотов, инициализирует OpenGL-виджет и диалог настроек.
   *
   * @param parent Указатель на родительский виджет (по умолчанию nullptr).
   */
  explicit MainViewer(QWidget* parent = nullptr);

  /**
   * @brief Деструктор класса MainViewer.
   *
   * Освобождает ресурсы, удаляет наблюдателя из модели и очищает память.
   */
  ~MainViewer() override;

 private slots:
  /**
   * @brief Загружает модель из файла OBJ.
   */
  void loadFile();

  /**
   * @brief Выполняет перемещение модели.
   */
  void onTranslate();

  /**
   * @brief Выполняет поворот модели.
   */
  void onRotate();

  /**
   * @brief Выполняет масштабирование модели.
   */
  void onScale();

  /**
   * @brief Открывает диалог настроек.
   */
  void openSettings();

  /**
   * @brief Начинает анимацию вращения модели.
   */
  void startAnimation();

  /**
   * @brief Сохраняет скриншот текущего состояния OpenGL-виджета.
   */
  void saveScreenshot();

  /**
   * @brief Сохраняет анимацию в формате GIF.
   */
  void saveGif();

  /**
   * @brief Обновляет состояние анимации.
   */
  void updateAnimation();

  /**
   * @brief Захватывает кадр для анимации.
   *
   * @param frame Изображение текущего состояния OpenGL-виджета.
   */
  void captureFrame(QImage frame);

  /**
   * @brief Обновляет интерфейс вращения модели.
   *
   * @param x Угол поворота вокруг оси X (в градусах).
   * @param y Угол поворота вокруг оси Y (в градусах).
   */
  void updateRotationUI(float x, float y);
};

}  // namespace s21

#endif  // S21_PRESENTER_MAINVIEWER_H_