#include "./calculator_GUI.h"

GtkWidget *input_output_field;
GtkWidget *DBG_field;

void DBG_printer(char *text_to_print) {
  gtk_label_set_text(GTK_LABEL(DBG_field), text_to_print);
}

static const char last_buttons_labels[][33] = {
    "(",         ")",     "-> x",           "x ->",      "=",
    "Backspace", "Clear", "Function graph", "CreditCalc"};

gint delete_event(GtkWidget *window, GdkEvent *event, gpointer data) {
  (void)window;
  (void)event;
  (void)data;
  gtk_main_quit();
  return FALSE;
}

void Backspacing(char *math_expression) {
  if (*math_expression != '\0') {
    char *last_char_in_line = NULL;
    last_char_in_line = (char *)strchr(math_expression, '\0') - 1;
    if (last_char_in_line) {
      *last_char_in_line = '\0';
    } else {
      exit(1);
    }
  }
}

int ExpressionLengthChecker(char *math_expression) {
  int has_max_length_reached = 0;
  int math_expression_length = strlen(math_expression);
  if (math_expression_length >= EXPRESSIONS_STRING_LENGTH) {
    has_max_length_reached = 1;
  }
  return has_max_length_reached;
}

static void ButtonClickManager(GtkWidget *button_widget,
                               gpointer g_button_name) {
  (void)button_widget;
  char button_name[33] = {0};
  strcpy(button_name, (char *)g_button_name);
  static int is_need_to_clear_the_input_field = 0;
  static char math_expression[EXPRESSIONS_STRING_LENGTH + 1] = {0};
  char result[DBL_MAX_LENGTH + 1] = {0};
  static char the_x[EXPRESSIONS_STRING_LENGTH + 1] = {0};

  if (!strcmp("Clear", button_name)) {
    memset(math_expression, 0, strlen(math_expression));
    memset(the_x, 0, strlen(math_expression));
    gtk_entry_set_text(GTK_ENTRY(input_output_field), "0");
    is_need_to_clear_the_input_field = 0;
  } else if (!strcmp("=", button_name)) {
    memset(errors_in_actual_expression, 0, ERROR_MESSAGES_LENGTH_MAX);
    SmartCalcBackEnd_API(math_expression, result);
    if (*errors_in_actual_expression) {
      DBG_printer(errors_in_actual_expression);
    } else {
      DBG_printer(math_expression);
    }
    memset(math_expression, 0, EXPRESSIONS_STRING_LENGTH);
    strcpy(math_expression, result);
    gtk_entry_set_text(GTK_ENTRY(input_output_field), result);
    is_need_to_clear_the_input_field = 0;
  } else if (!strcmp("-> x", button_name)) {
    strcpy(the_x, math_expression);
    memset(math_expression, 0, strlen(math_expression));
    char t[DBL_MAX_LENGTH + 1] = {0};
    sprintf(t, "X=%s.", the_x);
    DBG_printer(t);
    gtk_entry_set_text(GTK_ENTRY(input_output_field), "");
    is_need_to_clear_the_input_field = 1;
  } else if (!strcmp("x ->", button_name)) {
    strcat(math_expression, the_x);
    gtk_entry_set_text(GTK_ENTRY(input_output_field), math_expression);
    is_need_to_clear_the_input_field = 0;
  } else if (!strcmp("Backspace", button_name)) {
    Backspacing(math_expression);
    gtk_entry_set_text(GTK_ENTRY(input_output_field), math_expression);
  } else if (!strcmp("Function graph", button_name)) {
    FunctionGraphCreator();
  } else if (!strcmp("CreditCalc", button_name)) {
    CreditCalculator();
  } else {
    int has_max_length_reached = ExpressionLengthChecker(math_expression);
    if (!has_max_length_reached) {
      if (is_need_to_clear_the_input_field) {
        memset(math_expression, 0, EXPRESSIONS_STRING_LENGTH);
      }
      strcat(math_expression, button_name);
      gtk_entry_set_text(GTK_ENTRY(input_output_field), math_expression);
      is_need_to_clear_the_input_field = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  // для корректной работы strtod в бэкэнде
  setlocale(LC_NUMERIC, "C");
  // Инициализируем переменные
  gtk_init(&argc, &argv);

  // Создаем главное окно
  GtkWidget *calculator_main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  /* Цепляем к закрытию окна завершение программы. */
  g_signal_connect(G_OBJECT(calculator_main_window), "delete_event",
                   G_CALLBACK(delete_event), NULL);

  // устанавливаем размер окна
  gtk_window_set_default_size(GTK_WINDOW(calculator_main_window), 300, 333);

  // его заголовок
  gtk_window_set_title(GTK_WINDOW(calculator_main_window), "ULTRA-Calculator");

  // ширина бордюра между краями окна и внутренними его элементами (т.к. это
  // окно верхнего уровня, иначе значение относилось бы к внешнему краю виджета)
  gtk_container_set_border_width(GTK_CONTAINER(calculator_main_window), 10);

  // Главная вертикальная коробка для горизонтальных блоков кнопок
  GtkWidget *vertical_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *entry_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *buttons_1st_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *buttons_2st_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *buttons_3d_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *buttons_4th_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *buttons_5th_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *buttons_6th_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *buttons_last_line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  // Создаем поле вывода для дебаггинга и общения с пользователем
  DBG_field = gtk_label_new("Hello and Welcome!");
  gtk_box_pack_start(GTK_BOX(vertical_main_box), DBG_field, FALSE, FALSE, 5);
  // Создаем окно ввода-вывода строки

  input_output_field = gtk_entry_new();
  // Устанавливаем максимальную длину строки для ввода
  gtk_entry_set_max_length(GTK_ENTRY(input_output_field), DBL_MAX_LENGTH);
  // запрещаем пользователю редактировать текст в окне ввода (ручной ввод не
  // предусмотрен).
  gtk_editable_set_editable(GTK_EDITABLE(input_output_field), FALSE);
  // устанавливаем направление текста в окне справа налево
  //  gtk_widget_set_direction(input_output_field, GTK_TEXT_DIR_RTL);
  gtk_entry_set_alignment(GTK_ENTRY(input_output_field), 1);
  // пишем 0 в поле для ввода
  gtk_entry_set_text(GTK_ENTRY(input_output_field), "0");
  gtk_box_pack_start(GTK_BOX(entry_line), input_output_field, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vertical_main_box), entry_line, FALSE, FALSE, 5);

  // Создаем кнопки для функций
  for (int i = 0; i < NUMBER_OF_POSSIBLE_FUNCTION; i++) {
    GtkWidget *actual_button = gtk_button_new_with_label(possible_functions[i]);
    g_signal_connect(G_OBJECT(actual_button), "clicked",
                     G_CALLBACK(ButtonClickManager),
                     (gpointer)possible_functions[i]);
    if (i < 5) {
      gtk_box_pack_start(GTK_BOX(buttons_1st_line), actual_button, TRUE, TRUE,
                         0);
    } else {
      gtk_box_pack_start(GTK_BOX(buttons_2st_line), actual_button, TRUE, TRUE,
                         0);
    }
  }
  gtk_box_pack_start(GTK_BOX(vertical_main_box), buttons_1st_line, FALSE, FALSE,
                     5);
  gtk_box_pack_start(GTK_BOX(vertical_main_box), buttons_2st_line, FALSE, FALSE,
                     5);
  // для операторов
  char operator[][6] = { ".", "+", "-", "*", "/", "^" };
  for (int i = 0; i < (NUMBER_OF_POSSIBLE_OPERATORS); i++) {
    GtkWidget *actual_button = gtk_button_new_with_label(operator[i]);
    g_signal_connect(G_OBJECT(actual_button), "clicked",
                     G_CALLBACK(ButtonClickManager), (gpointer) operator[i]);
    gtk_box_pack_start(GTK_BOX(buttons_3d_line), actual_button, TRUE, TRUE, 0);
  }
  gtk_box_pack_start(GTK_BOX(vertical_main_box), buttons_3d_line, FALSE, FALSE,
                     5);

  // для цифр
  char digit[][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (int i = 0; i < 10; i++) {
    GtkWidget *actual_button = gtk_button_new_with_label(digit[i]);
    g_signal_connect(G_OBJECT(actual_button), "clicked",
                     G_CALLBACK(ButtonClickManager), (gpointer)digit[i]);
    gtk_box_pack_start(GTK_BOX(buttons_4th_line), actual_button, TRUE, TRUE, 0);
  }
  gtk_box_pack_start(GTK_BOX(vertical_main_box), buttons_4th_line, FALSE, FALSE,
                     5);

  // для знака равно, переменной х и "очистить"
  //  "(", ")", "-> x", "x ->", "=", "Backspace", "Clear", "Function graph"

  for (int i = 0; i < 9; i++) {
    GtkWidget *actual_button =
        gtk_button_new_with_label(last_buttons_labels[i]);

    g_signal_connect(G_OBJECT(actual_button), "clicked",
                     G_CALLBACK(ButtonClickManager),
                     (gpointer)last_buttons_labels[i]);

    if (i < 5) {
      gtk_box_pack_start(GTK_BOX(buttons_5th_line), actual_button, TRUE, TRUE,
                         0);
    } else {
      gtk_box_pack_start(GTK_BOX(buttons_6th_line), actual_button, TRUE, TRUE,
                         0);
    }
  }
  gtk_box_pack_start(GTK_BOX(vertical_main_box), buttons_5th_line, FALSE, FALSE,
                     5);
  gtk_box_pack_start(GTK_BOX(vertical_main_box), buttons_6th_line, FALSE, FALSE,
                     6);
  //  кнопка выхода.
  GtkWidget *quit_btn = gtk_button_new_with_label("Quit");
  g_signal_connect(quit_btn, "clicked", G_CALLBACK(delete_event), NULL);

  gtk_box_pack_start(GTK_BOX(buttons_last_line), quit_btn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vertical_main_box), buttons_last_line, FALSE,
                     FALSE, 5);
  gtk_container_add(GTK_CONTAINER(calculator_main_window), vertical_main_box);
  gtk_widget_grab_focus(quit_btn);
  gtk_widget_show_all(calculator_main_window);

  gtk_main();
  exit(0);
}
