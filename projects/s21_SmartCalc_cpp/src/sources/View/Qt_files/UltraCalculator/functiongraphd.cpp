#include "functiongraphd.h"

#include <regex>

#include "../../../Controller/headers/controller.h"
#include "ui_functiongraphd.h"

bool FunctionGraphD::IsCorrectNumber(const std::string& math_expression) {
  if (math_expression.empty()) {
    return false;
  }
  std::regex regex("^[+-]?\\d+(\\.\\d+)?$");
  return regex_match(math_expression, regex);
}

FunctionGraphD::FunctionGraphD(QWidget* parent)
    : QDialog(parent), ui(new Ui::FunctionGraphD) {
  ui->setupUi(this);
}

FunctionGraphD::~FunctionGraphD() { delete ui; }

void FunctionGraphD::on_lineEdit_funct_formula_returnPressed() {
  FunctionGraphD::on_pushButton_clicked();
}

double a = -1;  // Начало интервала Ox
double b = 1;   // Конец интервала Ox
std::string formula = "x^2";

void FunctionGraphD::on_pushButton_clicked() {
  double h = 0.01;
  int N = (b - a) / h + 2;
  QVector<double> x(N), y(N);

  int i = 0;
  for (double X = a; X <= b; X += h) {
    x[i] = X;
    std::string f_with_x_replaced = formula;
    size_t pos = f_with_x_replaced.find("x");
    while (pos != std::string::npos) {
      f_with_x_replaced.replace(pos, 1, std::to_string(X));
      pos = f_with_x_replaced.find("x", pos + 1);
    }

    try {
      std::string ascii_Y =
          s21::MVC_Controller::FromViewToModelTransceiver(f_with_x_replaced);
      y[i] = std::stod(ascii_Y);

      // Проверка на inf и nan
      if (std::isinf(y[i]) || std::isnan(y[i])) {
        y[i] = std::numeric_limits<double>::quiet_NaN();  // скип
      }
    } catch (...) {
      y[i] = std::numeric_limits<double>::quiet_NaN();  // скип
    }
    i++;
  }

  // Отрисовка графика
  ui->widget_2_graph->clearGraphs();
  ui->widget_2_graph->addGraph();
  ui->widget_2_graph->graph(0)->setData(x, y);
  ui->widget_2_graph->xAxis->setLabel("x");
  ui->widget_2_graph->yAxis->setLabel("y");
  ui->widget_2_graph->xAxis->setRange(a, b);

  // Фильтрация nan-значений при расчёте minY/maxY
  double minY = std::numeric_limits<double>::infinity();
  double maxY = -std::numeric_limits<double>::infinity();
  for (int j = 0; j < N; j++) {
    if (!std::isnan(y[j])) {
      if (y[j] < minY) minY = y[j];
      if (y[j] > maxY) maxY = y[j];
    }
  }
  if (minY == std::numeric_limits<double>::infinity()) {
    minY = 0;  // Если все значения nan, устанавливаем диапазон 0..1
    maxY = 1;
  }
  ui->widget_2_graph->yAxis->setRange(minY, maxY);
  ui->widget_2_graph->replot();
}

void FunctionGraphD::on_lineEdit_6_cursorPositionChanged(int arg1, int arg2) {
  QString t = ui->lineEdit_6->text();
  if (IsCorrectNumber(t.toStdString())) {
    a = t.toDouble();
  } else {
    a = 0;
    ui->lineEdit_6->setText("0");
  }
}

void FunctionGraphD::on_lineEdit_value_r_to_cursorPositionChanged(int arg1,
                                                                  int arg2) {
  QString t = ui->lineEdit_value_r_to->text();
  if (IsCorrectNumber(t.toStdString())) {
    b = t.toDouble();
  } else {
    b = 0;
    ui->lineEdit_value_r_to->setText("0");
  }
}

void FunctionGraphD::on_lineEdit_funct_formula_cursorPositionChanged(int arg1,
                                                                     int arg2) {
  QString t = ui->lineEdit_funct_formula->text();
  formula = t.toStdString();
}