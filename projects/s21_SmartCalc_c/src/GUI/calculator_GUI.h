#ifndef SRC_GUI_CALCULATOR_GUI_H
#define SRC_GUI_CALCULATOR_GUI_H
#include <cairo.h>
#include <gtk/gtk.h>
#include <locale.h>

#include "../BackEnd/smartcalc_backend_library.h"
#define WIDTH 640
#define HEIGHT 640
void DBG_printer(char *text_to_print);
gint delete_event(GtkWidget *window, GdkEvent *event, gpointer data);
void Backspacing(char *math_expression);
int ExpressionLengthChecker(char *math_expression);

// static void ButtonClickManager(GtkWidget *button_widget,
//                                gpointer g_button_name);
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void FunctionGraphCreator();
double XYCoordsToScreenCoordsTranslator(double x_or_y_absolute_coord,
                                        double x_or_y_axis_length,
                                        int is_y_coords);
void CreditCalculator();
double CreditAmmountCalculator(double total_credit_amount, long int loan_time,
                               double interest_rate, int is_annuity);
// static void CreditCalcButtonClickManager(GtkWidget *widget,
//                                          GtkWidget *widget_name);

#endif