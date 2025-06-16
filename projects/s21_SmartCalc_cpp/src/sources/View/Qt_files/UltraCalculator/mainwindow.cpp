#include "mainwindow.h"

#include <string.h>

#include <iostream>
#include <stdexcept>

#include "../../../Controller/headers/controller.h"
#include "../../../Model/headers/backend.h"
#include "functiongraphd.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

/*API

  // Резервная функция обработки икса, как части выражения. Будет использована,
как основа при написании окна графика функции.

void MainWindow::xResultToMathExpression(std::string &x,
                                         std::string &math_expression) {

  std::string x_result = UltraCalculatorsBackEnd::UltraCalculatorsAPI(x);
  size_t position_in_line = 0;
  position_in_line = math_expression.find('x', position_in_line);
  while (position_in_line != std::string::npos) {
    math_expression.replace(position_in_line, 1, x_result);
    position_in_line += x_result.length();
    position_in_line = math_expression.find('x', position_in_line);
  }
}
*/

void MainWindow::MathExpressionAccumulator(const std::string text_to_add) {
  if (math_expression != "0") {
    math_expression += text_to_add;
  } else {
    math_expression = text_to_add;
  }

  ui->input_field->setText(QString::fromStdString(math_expression));
}

void MainWindow::on_pushButton_0_clicked() { MathExpressionAccumulator("0"); }

void MainWindow::on_pushButton_1_clicked() { MathExpressionAccumulator("1"); }

void MainWindow::on_pushButton_2_clicked() { MathExpressionAccumulator("2"); }

void MainWindow::on_pushButton_3_clicked() { MathExpressionAccumulator("3"); }

void MainWindow::on_pushButton_4_clicked() { MathExpressionAccumulator("4"); }

void MainWindow::on_pushButton_5_clicked() { MathExpressionAccumulator("5"); }

void MainWindow::on_pushButton_6_clicked() { MathExpressionAccumulator("6"); }

void MainWindow::on_pushButton_7_clicked() { MathExpressionAccumulator("7"); }

void MainWindow::on_pushButton_8_clicked() { MathExpressionAccumulator("8"); }
void MainWindow::on_pushButton_9_clicked() { MathExpressionAccumulator("9"); }

void MainWindow::on_pushButton_sin_clicked() {
  MathExpressionAccumulator("sin(");
}

void MainWindow::on_pushButton_cos_clicked() {
  MathExpressionAccumulator("cos(");
}

void MainWindow::on_pushButton_tan_clicked() {
  MathExpressionAccumulator("tan(");
}

void MainWindow::on_pushButton_log_clicked() {
  MathExpressionAccumulator("log(");
}

void MainWindow::on_pushButton_sqrt_clicked() {
  MathExpressionAccumulator("sqrt(");
}

void MainWindow::on_pushButton_ln_clicked() {
  MathExpressionAccumulator("ln(");
}

void MainWindow::on_pushButton_asin_clicked() {
  MathExpressionAccumulator("asin(");
}

void MainWindow::on_pushButton_acos_clicked() {
  MathExpressionAccumulator("acos(");
}

void MainWindow::on_pushButton_atan_clicked() {
  MathExpressionAccumulator("atan(");
}

void MainWindow::on_pushButton_quit_clicked() { MainWindow::close(); }

void MainWindow::on_pushButton_L_bracket_clicked() {
  MathExpressionAccumulator("(");
}

void MainWindow::on_pushButton_R_bracket_clicked() {
  MathExpressionAccumulator(")");
}

void MainWindow::on_pushButton_divide_clicked() {
  MathExpressionAccumulator(" / ");
}

void MainWindow::on_pushButton_mult_clicked() {
  MathExpressionAccumulator(" * ");
}

void MainWindow::on_pushButton_minus_clicked() {
  MathExpressionAccumulator(" - ");
}

void MainWindow::on_pushButton_plus_clicked() {
  MathExpressionAccumulator(" + ");
}

void MainWindow::on_pushButton_pow_clicked() {
  MathExpressionAccumulator(" ^ ");
}

void MainWindow::on_pushButton_equal_clicked() {
  try {
    std::string result =
        s21::MVC_Controller::FromViewToModelTransceiver(math_expression);
    ui->communication_field->setText(QString::fromStdString(math_expression));
    ui->input_field->setText(QString::fromStdString(result));
    math_expression = result;
  } catch (const std::invalid_argument &e) {
    ui->communication_field->setText(QString::fromStdString(e.what()));
    return;
  }
}

void MainWindow::on_pushButton_backspace_clicked() {
  math_expression.erase(std::prev(math_expression.end()));
  if (math_expression.empty()) {
    math_expression = "0";
  }
  ui->input_field->setText(QString::fromStdString(math_expression));
}

void MainWindow::on_pushButton_Clear_clicked() {
  x = "";
  math_expression = "0";
  ui->input_field->setText(QString::fromStdString(math_expression));
  ui->communication_field->setText(QString::fromStdString(greeting));
}

void MainWindow::on_pushButton_data_to_x_clicked() {
  x = math_expression;
  math_expression = "0";
  ui->input_field->setText(QString::fromStdString(math_expression));
  std::string t = "x = ";
  t += x;
  ui->communication_field->setText(QString::fromStdString(t));
}

void MainWindow::on_pushButton_x_insert_clicked() {
  if (x != "") {
    std::string t = s21::MVC_Controller::FromViewToModelTransceiver(x);
    MathExpressionAccumulator(t);
  } else {
    return;
  }
}

void MainWindow::on_pushButton_dot_clicked() { MathExpressionAccumulator("."); }

void MainWindow::on_pushButton_mod_clicked() {
  MathExpressionAccumulator(" mod ");
}

void MainWindow::on_pushButton_e_clicked() { MathExpressionAccumulator("e"); }

void MainWindow::on_pushButton_function_clicked() {
  FunctionGraphD FunctionGraphWindow;
  FunctionGraphWindow.setModal(true);
  FunctionGraphWindow.exec();
}
