#ifndef FUNCTIONGRAPHD_H
#define FUNCTIONGRAPHD_H

#include <QDialog>

namespace Ui {
class FunctionGraphD;
}

class FunctionGraphD : public QDialog {
  Q_OBJECT

 public:
  explicit FunctionGraphD(QWidget *parent = nullptr);
  ~FunctionGraphD();

 private:
  Ui::FunctionGraphD *ui;

 private slots:
  //  void on_lineEdit_funct_formula_returnPressed();
  void on_pushButton_clicked();
  // void on_lineEdit_6_returnPressed();
  // void on_lineEdit_value_r_to_returnPressed();
  bool IsCorrectNumber(const std::string &math_expression);
  void on_lineEdit_6_cursorPositionChanged(int arg1, int arg2);
  void on_lineEdit_value_r_to_cursorPositionChanged(int arg1, int arg2);
  void on_lineEdit_funct_formula_cursorPositionChanged(int arg1, int arg2);
  void on_lineEdit_funct_formula_returnPressed();
};

#endif  // FUNCTIONGRAPHD_H
