/**
 * @file presenter_mainviewer.cpp
 * @brief Реализация класса MainViewer, представляющего главное окно приложения.
 *
 * Этот файл содержит реализацию методов класса MainViewer, который управляет
 * основным интерфейсом приложения, включая загрузку моделей, выполнение
 * трансформаций, настройку отображения и создание анимаций.
 */

#include "../headers/presenter_mainviewer.h"

#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QtDebug>
#include <cmath>
#include <iostream>
#include <memory>

#include "../headers/command.h"
#include "ui_mainviewer.h"

namespace s21 {

/**
 * @brief Конструктор класса MainViewer.
 *
 * Инициализирует главное окно приложения, настраивает соединения сигналов и
 * слотов, инициализирует OpenGL-виджет и диалог настроек.
 *
 * @param parent Указатель на родительский виджет (по умолчанию nullptr).
 */
MainViewer::MainViewer(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainViewer),
      gl_widget_(nullptr),
      settings_dialog_(nullptr),
      animation_timer_(new QTimer(this)),
      gif_(new QGifImage),
      current_command_index_(0) {
  ui->setupUi(this);
  gl_widget_ = ui->glWindow;
  gl_widget_->setModel(model_);
  settings_dialog_ = new Settings(this);
  gif_->setDefaultDelay(100);

  // Основные соединения
  connect(ui->load_file, &QPushButton::clicked, this, &MainViewer::loadFile);
  connect(ui->translate, &QPushButton::clicked, this, &MainViewer::onTranslate);
  connect(ui->rotate, &QPushButton::clicked, this, &MainViewer::onRotate);
  connect(ui->scale, &QPushButton::clicked, this, &MainViewer::onScale);
  connect(ui->settings, &QPushButton::clicked, this, &MainViewer::openSettings);
  connect(ui->gif, &QPushButton::clicked, this, &MainViewer::startAnimation);
  connect(ui->screenshot, &QPushButton::clicked, this,
          &MainViewer::saveScreenshot);
  connect(animation_timer_, &QTimer::timeout, this,
          &MainViewer::updateAnimation);
  connect(gl_widget_, &GLView::requestFrame, this, &MainViewer::captureFrame);
  connect(gl_widget_, &GLView::rotationChanged, this,
          &MainViewer::updateRotationUI);

  // Соединения слайдеров и спинбоксов
  connect(ui->slider_move_x, &QSlider::valueChanged, ui->spin_move_x,
          &QSpinBox::setValue);
  connect(ui->slider_move_y, &QSlider::valueChanged, ui->spin_move_y,
          &QSpinBox::setValue);
  connect(ui->slider_move_z, &QSlider::valueChanged, ui->spin_move_z,
          &QSpinBox::setValue);
  connect(ui->slider_rotation_x, &QSlider::valueChanged, ui->spin_rotation_x,
          &QSpinBox::setValue);
  connect(ui->slider_rotation_y, &QSlider::valueChanged, ui->spin_rotation_y,
          &QSpinBox::setValue);
  connect(ui->slider_rotation_z, &QSlider::valueChanged, ui->spin_rotation_z,
          &QSpinBox::setValue);
  connect(ui->slider_scale, &QSlider::valueChanged, ui->spin_scale,
          &QSpinBox::setValue);
  connect(ui->spin_move_x, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->slider_move_x, &QSlider::setValue);
  connect(ui->spin_move_y, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->slider_move_y, &QSlider::setValue);
  connect(ui->spin_move_z, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->slider_move_z, &QSlider::setValue);
  connect(ui->spin_rotation_x, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->slider_rotation_x, &QSlider::setValue);
  connect(ui->spin_rotation_y, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->slider_rotation_y, &QSlider::setValue);
  connect(ui->spin_rotation_z, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->slider_rotation_z, &QSlider::setValue);
  connect(ui->spin_scale, QOverload<int>::of(&QSpinBox::valueChanged),
          ui->slider_scale, &QSlider::setValue);

  // Соединение для настроек
  connect(settings_dialog_, &Settings::onSetApplyClicked, this,
          [this](QColor vertex_color, int vertex_size, int vertex_shape,
                 QColor edge_color, int edge_width, int edge_type,
                 QColor bg_color, bool central_projection) {
            gl_widget_->applySettings(vertex_color, vertex_size, vertex_shape,
                                      edge_color, edge_width, edge_type,
                                      bg_color, central_projection);
          });
}

/**
 * @brief Деструктор класса MainViewer.
 *
 * Освобождает ресурсы, удаляет наблюдателя из модели и очищает память.
 */
MainViewer::~MainViewer() {
  model_.removeObserver(gl_widget_);
  delete gif_;
  delete animation_timer_;
  delete settings_dialog_;
  delete ui;
}

/**
 * @brief Загружает модель из файла OBJ.
 *
 * Открывает диалог выбора файла, загружает данные модели и обновляет интерфейс.
 */
void MainViewer::loadFile() {
  QString filePath = QFileDialog::getOpenFileName(this, "Open .obj File", "",
                                                  "OBJ Files (*.obj)");
  if (!filePath.isEmpty()) {
    try {
      model_.loadFromFile(filePath.toStdString());
      ui->label_file->setText(QFileInfo(filePath).fileName());
      ui->count_vertices->setText(
          QString::number(model_.getData().vertex_count));
      ui->count_edges->setText(QString::number(model_.getData().edge_count));
      ui->spin_move_x->setValue(0);
      ui->spin_move_y->setValue(0);
      ui->spin_move_z->setValue(0);
      ui->spin_rotation_x->setValue(0);
      ui->spin_rotation_y->setValue(0);
      ui->spin_rotation_z->setValue(0);
      ui->spin_scale->setValue(1);
    } catch (const std::exception& e) {
      QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
  }
}

/**
 * @brief Обновляет интерфейс вращения модели.
 *
 * @param x Угол поворота вокруг оси X (в градусах).
 * @param y Угол поворота вокруг оси Y (в градусах).
 */
void MainViewer::updateRotationUI(float x, float y) {
  ui->spin_rotation_x->setValue(static_cast<int>(x));
  ui->spin_rotation_y->setValue(static_cast<int>(y));
}

/**
 * @brief Выполняет перемещение модели.
 *
 * Создает команды перемещения и выполняет их над моделью.
 */
void MainViewer::onTranslate() {
  // std::cout << "Translate button clicked!" << std::endl;
  float x = ui->spin_move_x->value();
  float y = ui->spin_move_y->value();
  float z = ui->spin_move_z->value();
  // std::cout << "Translate values: x=" << x << ", y=" << y << ", z=" << z
  //           << std::endl;
  std::unique_ptr<Command> cmdX = std::unique_ptr<Command>(new MoveXCommand(x));
  std::unique_ptr<Command> cmdY = std::unique_ptr<Command>(new MoveYCommand(y));
  std::unique_ptr<Command> cmdZ = std::unique_ptr<Command>(new MoveZCommand(z));
  cmdX->execute(model_);
  cmdY->execute(model_);
  cmdZ->execute(model_);
}

/**
 * @brief Выполняет поворот модели.
 *
 * Создает команды поворота и выполняет их над моделью.
 */
void MainViewer::onRotate() {
  // std::cout << "Rotate button clicked!" << std::endl;
  float x = ui->spin_rotation_x->value() * M_PI / 180.0;
  float y = ui->spin_rotation_y->value() * M_PI / 180.0;
  float z = ui->spin_rotation_z->value() * M_PI / 180.0;
  // std::cout << "Rotate values: x=" << x << ", y=" << y << ", z=" << z
  //           << std::endl;
  float delta_x = x - model_.getRotateX();
  float delta_y = y - model_.getRotateY();
  float delta_z = z - model_.getRotateZ();
  std::unique_ptr<Command> cmdX =
      std::unique_ptr<Command>(new RotateXCommand(delta_x));
  std::unique_ptr<Command> cmdY =
      std::unique_ptr<Command>(new RotateYCommand(delta_y));
  std::unique_ptr<Command> cmdZ =
      std::unique_ptr<Command>(new RotateZCommand(delta_z));
  cmdX->execute(model_);
  cmdY->execute(model_);
  cmdZ->execute(model_);
  updateRotationUI(model_.getRotateX() * 180.0 / M_PI,
                   model_.getRotateY() * 180.0 / M_PI);
}

/**
 * @brief Выполняет масштабирование модели.
 *
 * Создает команду масштабирования и выполняет её над моделью.
 */
void MainViewer::onScale() {
  // std::cout << "Scale button clicked!" << std::endl;
  float ratio = ui->spin_scale->value();
  // std::cout << "Scale value: " << ratio << std::endl;
  if (ratio <= 0) {
    QMessageBox::warning(this, "Warning", "Scale must be positive");
    return;
  }
  try {
    std::unique_ptr<Command> cmd =
        std::unique_ptr<Command>(new ScaleCommand(ratio));
    cmd->execute(model_);
  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
  }
}

/**
 * @brief Открывает диалог настроек.
 */
void MainViewer::openSettings() { settings_dialog_->exec(); }

/**
 * @brief Начинает анимацию вращения модели.
 */
void MainViewer::startAnimation() {
  QString filePath =
      QFileDialog::getSaveFileName(this, "Save GIF", "", "GIF Files (*.gif)");
  if (filePath.isEmpty()) {
    return;
  }
  gif_file_path_ = filePath;
  animation_commands_.clear();
  gif_frames_.clear();
  current_command_index_ = 0;
  float current_y = model_.getRotateY();
  if (current_y != 0.0) {
    std::unique_ptr<Command> resetY =
        std::unique_ptr<Command>(new RotateYCommand(-current_y));
    resetY->execute(model_);
  }
  for (float angle = 0; angle < 360.0f; angle += 5.0f) {
    animation_commands_.push_back(
        std::unique_ptr<Command>(new RotateYCommand(angle * M_PI / 180.0)));
  }
  animation_timer_->start(100);
}

/**
 * @brief Сохраняет скриншот текущего состояния OpenGL-виджета.
 */
void MainViewer::saveScreenshot() {
  QImage image = gl_widget_->grabFramebuffer();
  QString filePath = QFileDialog::getSaveFileName(this, "Save Screenshot", "",
                                                  "Images (*.png *.jpg *.bmp)");
  if (!filePath.isEmpty()) {
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix().isEmpty()) {
      filePath += ".png";
    }
    QImageWriter writer(filePath);
    if (!writer.write(image)) {
      QMessageBox::critical(this, "Error", "Failed to save screenshot");
    }
  }
}

/**
 * @brief Сохраняет анимацию в формате GIF.
 */
void MainViewer::saveGif() {
  if (!gif_file_path_.isEmpty()) {
    for (const QImage& frame : gif_frames_) {
      gif_->addFrame(frame);
    }
    if (!gif_->save(gif_file_path_)) {
      QMessageBox::critical(this, "Error", "Failed to save GIF");
    } else {
      QMessageBox::information(this, "Success",
                               "GIF saved successfully to " + gif_file_path_);
    }
    gif_frames_.clear();
    gif_file_path_.clear();
  }
}

/**
 * @brief Обновляет состояние анимации.
 */
void MainViewer::updateAnimation() {
  if (current_command_index_ < animation_commands_.size()) {
    animation_commands_[current_command_index_]->execute(model_);
    current_command_index_++;
    updateRotationUI(model_.getRotateX() * 180.0 / M_PI,
                     model_.getRotateY() * 180.0 / M_PI);
  } else {
    animation_timer_->stop();
    saveGif();
  }
}

/**
 * @brief Захватывает кадр для анимации.
 *
 * @param frame Изображение текущего состояния OpenGL-виджета.
 */
void MainViewer::captureFrame(QImage frame) {
  if (animation_timer_->isActive()) {
    gif_frames_.push_back(frame);
  }
}

}  // namespace s21