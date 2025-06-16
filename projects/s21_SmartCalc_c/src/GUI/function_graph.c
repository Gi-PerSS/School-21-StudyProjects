#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../BackEnd/smartcalc_backend_library.h"
#include "./calculator_GUI.h"

GtkWidget *value_area_eline;
GtkWidget *definition_area_eline;
GtkWidget *function_formula_eline;
GtkWidget *communucation_field_txt;
GtkWidget *drawing_area;
GtkWidget *function_main_window;
GtkWidget *f_quit_btn;

void FunctionQuit(GtkWidget *widget, GtkWidget *widget_name) {
  (void)widget;
  gtk_widget_destroy(widget_name);
}

void enter_callback(GtkWidget *widget, GtkWidget *entry) {
  (void)widget;
  (void)entry;
  gtk_widget_queue_draw_area(drawing_area, 0, 0, 999, 999);
}

int ValidateFormula(const char *formula) {
  if (!formula || !*formula) {
    gtk_label_set_text(GTK_LABEL(communucation_field_txt),
                       "Error: Empty formula");
    return 0;
  }

  const char *allowed_chars =
      "0123456789.+-*/%^()xXcossintanacosasinatansqrtlnlog ";
  for (const char *p = formula; *p; p++) {
    if (!strchr(allowed_chars, *p)) {
      char error_msg[128];
      snprintf(error_msg, sizeof(error_msg),
               "Error: Invalid character '%c' in formula", *p);
      gtk_label_set_text(GTK_LABEL(communucation_field_txt), error_msg);
      return 0;
    }
  }

  return 1;
}

gboolean develop_on_draw(GtkWidget *widget, cairo_t *cairo_context,
                         gpointer user_data) {
  (void)user_data;
  int width = gtk_widget_get_allocated_width(widget);
  int height = gtk_widget_get_allocated_height(widget);

  /* Черный фон */
  cairo_set_source_rgb(cairo_context, 0.0, 0.0, 0.0);
  cairo_paint(cairo_context);

  /* Оси координат */
  gdouble line_width = 2;
  cairo_set_line_width(cairo_context, line_width);
  cairo_set_source_rgb(cairo_context, 0.0, 1.0, 0.0);
  gdouble y_center = height / 2.0;
  gdouble x_center = width / 2.0;
  cairo_move_to(cairo_context, 0, y_center);
  cairo_line_to(cairo_context, width, y_center);
  cairo_move_to(cairo_context, x_center, 0);
  cairo_line_to(cairo_context, x_center, height);
  cairo_stroke(cairo_context);

  /* Адаптивная сетка */
  int grid_step = 30;
  line_width = 0.3;
  cairo_set_line_width(cairo_context, line_width);
  cairo_set_source_rgb(cairo_context, 1.0, 1.0, 1.0);
  for (int i = y_center; i < height; i += grid_step) {
    cairo_move_to(cairo_context, 0, i);
    cairo_line_to(cairo_context, width, i);
    cairo_stroke(cairo_context);
  }
  for (int i = y_center; i > 0; i -= grid_step) {
    cairo_move_to(cairo_context, 0, i);
    cairo_line_to(cairo_context, width, i);
    cairo_stroke(cairo_context);
  }
  for (int i = x_center; i < width; i += grid_step) {
    cairo_move_to(cairo_context, i, 0);
    cairo_line_to(cairo_context, i, height);
    cairo_stroke(cairo_context);
  }
  for (int i = x_center; i > 0; i -= grid_step) {
    cairo_move_to(cairo_context, i, 0);
    cairo_line_to(cairo_context, i, height);
    cairo_stroke(cairo_context);
  }

  /* Получаем область определения */
  const gchar *ascii_definition =
      gtk_entry_get_text(GTK_ENTRY(definition_area_eline));
  double definition_area_to = fabs(strtod(ascii_definition, NULL));

  if (definition_area_to <= 0 || definition_area_to > 1e6) {
    gtk_label_set_text(GTK_LABEL(communucation_field_txt),
                       "Error: X-range must be (0 < x <= 1e6)");
    return FALSE;
  }

  /* Получаем и проверяем формулу */
  const char *formula = gtk_entry_get_text(GTK_ENTRY(function_formula_eline));
  if (!ValidateFormula(formula)) {
    return FALSE;
  }

  /* Настройка масштаба */
  double pixels_per_unit_x = width / (2.0 * definition_area_to);
  double pixels_per_unit_y = height / (2.0 * definition_area_to);
  double step = fmax(1.0 / pixels_per_unit_x, 0.001);

  /* Обновляем поле значения */
  char value_text[32];
  snprintf(value_text, sizeof(value_text), "%g", definition_area_to);
  gtk_entry_set_text(GTK_ENTRY(value_area_eline), value_text);

  /* Рисуем график */
  cairo_set_line_width(cairo_context, 2);
  cairo_set_source_rgb(cairo_context, 0.0, 1.0, 0.0);

  double x = -definition_area_to;
  double y = FunctionValueDefiner(x, formula);

  if (isnan(y) || isinf(y)) {
    gtk_label_set_text(GTK_LABEL(communucation_field_txt),
                       "Error: Function undefined at start point");
    return FALSE;
  }

  double screen_x = x_center + x * pixels_per_unit_x;
  double screen_y = y_center - y * pixels_per_unit_y;
  cairo_move_to(cairo_context, screen_x, screen_y);

  while (x <= definition_area_to) {
    y = FunctionValueDefiner(x, formula);

    if (isnan(y) || isinf(y)) {
      cairo_move_to(cairo_context, x_center + (x + step) * pixels_per_unit_x,
                    y_center - FunctionValueDefiner(x + step, formula) *
                                   pixels_per_unit_y);
    } else {
      screen_x = x_center + x * pixels_per_unit_x;
      screen_y = y_center - y * pixels_per_unit_y;

      if (fabs(y) > definition_area_to * 10) {
        char warn_msg[128];
        snprintf(warn_msg, sizeof(warn_msg),
                 "Warning: Y-value %g out of range at X=%g", y, x);
        gtk_label_set_text(GTK_LABEL(communucation_field_txt), warn_msg);
      }

      cairo_line_to(cairo_context, screen_x, screen_y);
    }

    x += step;
  }

  cairo_stroke(cairo_context);

  /* Подписи осей */
  cairo_set_source_rgb(cairo_context, 0.2, 0.2, 0.6);
  cairo_select_font_face(cairo_context, "monospace", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cairo_context, 16);

  char scale_message[128];
  snprintf(scale_message, sizeof(scale_message), "Scale 1:%.2f",
           1.0 / pixels_per_unit_x);
  cairo_move_to(cairo_context, 20, 30);
  cairo_show_text(cairo_context, scale_message);

  cairo_set_source_rgb(cairo_context, 1.0, 1.0, 1.0);
  char temp_text[32];

  cairo_move_to(cairo_context, x_center + 5, y_center + 15);
  cairo_show_text(cairo_context, "0");

  double label_x = x_center + (-definition_area_to) * pixels_per_unit_x;
  cairo_move_to(cairo_context, label_x + 5, y_center + 15);
  snprintf(temp_text, sizeof(temp_text), "%g", -definition_area_to);
  cairo_show_text(cairo_context, temp_text);

  label_x = x_center + definition_area_to * pixels_per_unit_x;
  cairo_move_to(cairo_context, label_x - 40, y_center + 15);
  snprintf(temp_text, sizeof(temp_text), "%g", definition_area_to);
  cairo_show_text(cairo_context, temp_text);

  double label_y = y_center - definition_area_to * pixels_per_unit_y;
  cairo_move_to(cairo_context, x_center + 5, label_y + 5);
  snprintf(temp_text, sizeof(temp_text), "%g", definition_area_to);
  cairo_show_text(cairo_context, temp_text);

  label_y = y_center - (-definition_area_to) * pixels_per_unit_y;
  cairo_move_to(cairo_context, x_center + 5, label_y - 5);
  snprintf(temp_text, sizeof(temp_text), "%g", -definition_area_to);
  cairo_show_text(cairo_context, temp_text);

  return FALSE;
}

void FunctionGraphCreator(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  function_main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_resizable(GTK_WINDOW(function_main_window), TRUE);
  gtk_window_set_default_size(GTK_WINDOW(function_main_window), WIDTH, HEIGHT);
  gtk_window_set_title(GTK_WINDOW(function_main_window), "Graph drawing");
  g_signal_connect(G_OBJECT(function_main_window), "destroy", gtk_main_quit,
                   NULL);

  GtkWidget *vertical_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  drawing_area = gtk_drawing_area_new();
  gtk_box_pack_start(GTK_BOX(vertical_main_box), drawing_area, TRUE, TRUE, 5);
  g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(develop_on_draw),
                   NULL);

  GtkWidget *entry_lines_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *definition_value_area_box =
      gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  GtkWidget *definition_area_txt =
      gtk_label_new("The function definition (modulo, max 1e+06):");
  definition_area_eline = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(definition_area_eline), 1);
  gtk_entry_set_text(GTK_ENTRY(definition_area_eline), "10");
  g_signal_connect(G_OBJECT(definition_area_eline), "activate",
                   G_CALLBACK(enter_callback), (gpointer)definition_area_eline);

  GtkWidget *value_area_txt =
      gtk_label_new("The function value (modulo, auto):");
  value_area_eline = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(value_area_eline), 1);
  gtk_editable_set_editable(GTK_EDITABLE(value_area_eline), FALSE);
  gtk_entry_set_text(GTK_ENTRY(value_area_eline), "10");

  gtk_box_pack_start(GTK_BOX(definition_value_area_box), definition_area_txt,
                     FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(definition_value_area_box), definition_area_eline,
                     FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(definition_value_area_box), value_area_txt, FALSE,
                     TRUE, 5);
  gtk_box_pack_start(GTK_BOX(definition_value_area_box), value_area_eline,
                     FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(entry_lines_box), definition_value_area_box, TRUE,
                     TRUE, 5);

  GtkWidget *rigth_side_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  GtkWidget *function_formula_txt =
      gtk_label_new("Type the function formula here:");
  function_formula_eline = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(function_formula_eline), 1);
  gtk_entry_set_text(GTK_ENTRY(function_formula_eline), "sin(x)");
  g_signal_connect(G_OBJECT(function_formula_eline), "activate",
                   G_CALLBACK(enter_callback),
                   (gpointer)function_formula_eline);

  communucation_field_txt = gtk_label_new("\n\nHello and Welcome!");

  f_quit_btn = gtk_button_new_with_label("Quit");
  g_signal_connect(f_quit_btn, "clicked", G_CALLBACK(FunctionQuit),
                   (gpointer)function_main_window);

  gtk_box_pack_start(GTK_BOX(rigth_side_box), function_formula_txt, FALSE,
                     FALSE, 5);
  gtk_box_pack_start(GTK_BOX(rigth_side_box), function_formula_eline, FALSE,
                     FALSE, 5);
  gtk_box_pack_start(GTK_BOX(rigth_side_box), communucation_field_txt, FALSE,
                     FALSE, 5);
  gtk_box_pack_start(GTK_BOX(rigth_side_box), f_quit_btn, FALSE, FALSE, 5);
  gtk_widget_grab_focus(f_quit_btn);

  gtk_box_pack_start(GTK_BOX(entry_lines_box), rigth_side_box, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vertical_main_box), entry_lines_box, FALSE, FALSE,
                     5);

  gtk_container_add(GTK_CONTAINER(function_main_window), vertical_main_box);
  gtk_widget_show_all(function_main_window);
  gtk_main();
}