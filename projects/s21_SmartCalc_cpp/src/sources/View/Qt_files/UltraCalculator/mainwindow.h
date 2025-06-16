#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  std::string math_expression = "0";
  std::string x = "";
  std::string greeting = "Hello and Welcome!";
  void xResultToMathExpression(std::string &x, std::string &math_expression);
  void MathExpressionAccumulator(std::string text_to_add);

 private slots:

  void on_pushButton_0_clicked();
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();

  void on_pushButton_e_clicked();
  void on_pushButton_mod_clicked();

  void on_pushButton_sin_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_atan_clicked();

  void on_pushButton_sqrt_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_ln_clicked();

  void on_pushButton_L_bracket_clicked();
  void on_pushButton_R_bracket_clicked();
  void on_pushButton_divide_clicked();
  void on_pushButton_mult_clicked();
  void on_pushButton_minus_clicked();
  void on_pushButton_plus_clicked();
  void on_pushButton_pow_clicked();
  void on_pushButton_equal_clicked();

  void on_pushButton_quit_clicked();

  void on_pushButton_backspace_clicked();
  void on_pushButton_Clear_clicked();
  void on_pushButton_data_to_x_clicked();
  void on_pushButton_x_insert_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_function_clicked();
};
#endif  // MAINWINDOW_H
