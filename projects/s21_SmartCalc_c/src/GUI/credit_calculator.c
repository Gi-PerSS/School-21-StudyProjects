#include "../BackEnd/smartcalc_backend_library.h"
#include "./calculator_GUI.h"
GtkWidget *cred_calc_main_window;
GtkWidget *quit_btn;
GtkWidget *calculate_it;
GtkWidget *annuity_button;
GtkWidget *differentiated_button;

GtkWidget *results_txt;
GtkWidget *greetings_txt;
GtkWidget *total_credit_amount_eline;
GtkWidget *loan_time_eline;
GtkWidget *interest_rate_eline;

double CreditAmmountCalculator(double total_credit_amount, long int loan_time,
                               double interest_rate, int is_annuity) {
  char f[DBL_MAX_LENGTH * 3] = {0};

  char answer2output[DBL_MAX_LENGTH + 1] = {0};
  // процентная ставка в месяц
  double interest_rate_per_month = interest_rate / 100 / 12;
  if (is_annuity) {
    char monthly_payment[DBL_MAX_LENGTH + 1] = {0};
    // Определяется размер ежемесячного платежа
    sprintf(f, "%f * (%f + %f/((1 + %f) ^ %ld - 1))", total_credit_amount,
            interest_rate_per_month, interest_rate_per_month,
            interest_rate_per_month, loan_time);
    SmartCalcBackEnd_API(f, monthly_payment);
    strcat(answer2output, "Monthly payment:\t");
    strcat(answer2output, monthly_payment);
    // Общая выплата
    memset(f, 0, DBL_MAX_LENGTH + 1);
    char general_payment[DBL_MAX_LENGTH + 1] = {0};
    sprintf(f, "(%s * %ld)", monthly_payment, loan_time);
    SmartCalcBackEnd_API(f, general_payment);
    strcat(answer2output, "\nGeneral paymen:\t");
    strcat(answer2output, general_payment);
    // Определяется размер переплаты по кредиту
    memset(f, 0, DBL_MAX_LENGTH + 1);
    char overpayment[DBL_MAX_LENGTH + 1] = {0};
    sprintf(f, "(%s - %f)", general_payment, total_credit_amount);
    SmartCalcBackEnd_API(f, overpayment);
    strcat(answer2output, "\nOverpayment:\t\t");
    strcat(answer2output, overpayment);

    gtk_label_set_text(GTK_LABEL(results_txt), answer2output);
    /* Платеж = сумма кредита * процентная ставка в месяц / 1-(1+процентная
     * ставка в месяц)^-количество месяцев
     */
  } else {
    /*
        месячный кусок = Sum/months
        процентный кусок = (Sum - выплаченное) * процент
    */

    // Определяется размер ежемесячного платежа
    double month_bite = total_credit_amount / loan_time;
    double remaining_value = total_credit_amount;
    double percent_bite = 0;
    double general_payment = 0;
    double first_month_payment = 0;
    double last_month_paymen = 0;
    for (int i = 1; i <= (int)loan_time; i++) {
      percent_bite = remaining_value * interest_rate_per_month;
      remaining_value -= month_bite;
      double monthly_payment = month_bite + percent_bite;
      general_payment += monthly_payment;
      if (i == 1) {
        first_month_payment = monthly_payment;
      } else if (i == loan_time) {
        last_month_paymen = monthly_payment;
      }
    }
    double overpayment = general_payment - total_credit_amount;
    if (loan_time > 1) {
      sprintf(answer2output,
              "Monthly payment:\t%.2f ... %.2f\nGeneral "
              "paymen:\t%.2f\nOverpayment:\t\t%.2f",
              first_month_payment, last_month_paymen, general_payment,
              overpayment);
    } else {
      sprintf(
          answer2output,
          "Monthly payment:\t%.2f\nGeneral paymen:\t%.2f\nOverpayment:\t\t%.2f",
          first_month_payment, general_payment, overpayment);
    }
    gtk_label_set_text(GTK_LABEL(greetings_txt), "The results are as follows:");
    gtk_label_set_text(GTK_LABEL(results_txt), answer2output);
  }
  return 0;
}

static void CreditCalcButtonClickManager(GtkWidget *widget,
                                         GtkWidget *widget_name) {
  (void)widget;
  /*
  Функция собирает данные из полей ввода, вычисляет выражение и выводит ответ.
  */

  static double total_credit_amount = 0;
  static long int loan_time = 0;
  static double interest_rate = 0;

  int is_annuity = 0;
  is_annuity = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(annuity_button));

  // нажатие на интер в строке ввода переводит фокус на след. поле
  if (widget_name == quit_btn) {
    gtk_widget_destroy(cred_calc_main_window);
  } else if (widget_name == total_credit_amount_eline) {
    gtk_widget_grab_focus(loan_time_eline);
  } else if (widget_name == loan_time_eline) {
    gtk_widget_grab_focus(interest_rate_eline);
  } else if (widget_name == interest_rate_eline) {
    gtk_widget_grab_focus(calculate_it);
  } else if (widget_name == calculate_it) {
    // извлекаем данные из полей ввода
    const gchar *p_ascii_total_credit_amount =
        gtk_entry_get_text(GTK_ENTRY(total_credit_amount_eline));

    char ascii_total_credit_amount[DBL_MAX_LENGTH * 3 + 1] = {0};
    SmartCalcBackEnd_API((char *)p_ascii_total_credit_amount,
                         ascii_total_credit_amount);
    const gchar *p_ascii_loan_time =
        gtk_entry_get_text(GTK_ENTRY(loan_time_eline));
    char ascii_loan_time[DBL_MAX_LENGTH * 3 + 1] = {0};
    SmartCalcBackEnd_API((char *)p_ascii_loan_time, ascii_loan_time);
    const gchar *p_ascii_interest_rate =
        gtk_entry_get_text(GTK_ENTRY(interest_rate_eline));
    char ascii_interest_rate[DBL_MAX_LENGTH * 3 + 1] = {0};
    SmartCalcBackEnd_API((char *)p_ascii_interest_rate, ascii_interest_rate);
    // и переводим в числовой вид
    total_credit_amount = strtod(ascii_total_credit_amount, NULL);
    loan_time = strtod(ascii_loan_time, NULL);
    interest_rate = strtod(ascii_interest_rate, NULL);

    if (total_credit_amount > 0 && loan_time > 0 && interest_rate >= 0) {
      CreditAmmountCalculator(total_credit_amount, loan_time, interest_rate,
                              is_annuity);
    } else {
      gtk_label_set_text(GTK_LABEL(results_txt),
                         "Something wrong. You can try again!");
    }
  }
}

void CreditCalculator(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  cred_calc_main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  // устанавливаем размер окна
  gtk_window_set_default_size(GTK_WINDOW(cred_calc_main_window), 650, 333);
  gtk_container_set_border_width(GTK_CONTAINER(cred_calc_main_window), 10);
  gtk_window_set_title(GTK_WINDOW(cred_calc_main_window),
                       "Credit ULTRA-calculator");
  g_signal_connect(G_OBJECT(cred_calc_main_window), "destroy", gtk_main_quit,
                   NULL);
  // Для равного распределения ширины окна между коробками группируем их.
  GtkSizeGroup *boxes_group = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);

  GtkWidget *vertical_left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
  GtkWidget *vertical_rigth_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *horizontal_main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  gtk_size_group_add_widget(boxes_group, vertical_left_box);
  gtk_size_group_add_widget(boxes_group, vertical_rigth_box);

  // Создаем поле ответа
  greetings_txt = gtk_label_new("Hello and Welcome!");
  results_txt = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(vertical_rigth_box), greetings_txt, FALSE, TRUE,
                     5);
  gtk_box_pack_start(GTK_BOX(vertical_rigth_box), results_txt, FALSE, TRUE, 5);
  // Создаем строку ввода для значения размера кредита
  GtkWidget *total_credit_amount_txt =
      gtk_label_new("\nEnter the total credit amount here:");
  gtk_label_set_xalign(GTK_LABEL(total_credit_amount_txt), 0);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), total_credit_amount_txt, FALSE,
                     TRUE, 5);
  total_credit_amount_eline = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(total_credit_amount_eline), "0");
  gtk_entry_set_alignment(GTK_ENTRY(total_credit_amount_eline), 1);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), total_credit_amount_eline,
                     FALSE, FALSE, 5);
  g_signal_connect(G_OBJECT(total_credit_amount_eline), "activate",
                   G_CALLBACK(CreditCalcButtonClickManager),
                   (gpointer)total_credit_amount_eline);

  // время, на которое выдается займ
  GtkWidget *loan_time_txt = gtk_label_new("The loan time (in months):");
  gtk_label_set_xalign(GTK_LABEL(loan_time_txt), 0);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), loan_time_txt, FALSE, TRUE, 5);
  loan_time_eline = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(loan_time_eline), "0");
  gtk_entry_set_alignment(GTK_ENTRY(loan_time_eline), 1);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), loan_time_eline, FALSE, FALSE,
                     5);
  g_signal_connect(G_OBJECT(loan_time_eline), "activate",
                   G_CALLBACK(CreditCalcButtonClickManager),
                   (gpointer)loan_time_eline);

  // процентная ставка
  GtkWidget *interest_rate_txt = gtk_label_new("The interest rate:");
  gtk_label_set_xalign(GTK_LABEL(interest_rate_txt), 0);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), interest_rate_txt, FALSE, TRUE,
                     5);
  interest_rate_eline = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(interest_rate_eline), "0");
  gtk_entry_set_alignment(GTK_ENTRY(interest_rate_eline), 1);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), interest_rate_eline, FALSE,
                     FALSE, 5);
  g_signal_connect(G_OBJECT(interest_rate_eline), "activate",
                   G_CALLBACK(CreditCalcButtonClickManager),
                   (gpointer)interest_rate_eline);
  // чек-бокс для типа кредита annuity, differentiated
  annuity_button = gtk_radio_button_new_with_label(NULL, "annuity credit");
  gtk_box_pack_start(GTK_BOX(vertical_left_box), annuity_button, TRUE, TRUE, 0);
  GSList *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(annuity_button));
  differentiated_button =
      gtk_radio_button_new_with_label(group, "differentiated credit");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(differentiated_button), TRUE);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), differentiated_button, TRUE,
                     TRUE, 0);
  // Кнопка посчитать
  calculate_it = gtk_button_new_with_label("Calculate it!");
  g_signal_connect(G_OBJECT(calculate_it), "clicked",
                   G_CALLBACK(CreditCalcButtonClickManager),
                   (gpointer)calculate_it);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), calculate_it, FALSE, FALSE, 5);

  //  кнопка выхода.
  quit_btn = gtk_button_new_with_label("Quit");
  g_signal_connect(quit_btn, "clicked",
                   G_CALLBACK(CreditCalcButtonClickManager),
                   (gpointer)quit_btn);
  gtk_box_pack_start(GTK_BOX(vertical_left_box), quit_btn, FALSE, FALSE, 5);
  gtk_widget_grab_focus(quit_btn);
  // коробку кладем в окно

  // Упаковываем коробки с сепаратором между ними
  gtk_box_pack_start(GTK_BOX(horizontal_main_box), vertical_left_box, TRUE,
                     TRUE, 5);
  gtk_box_pack_start(GTK_BOX(horizontal_main_box), separator, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(horizontal_main_box), vertical_rigth_box, TRUE,
                     TRUE, 5);
  gtk_container_add(GTK_CONTAINER(cred_calc_main_window), horizontal_main_box);

  gtk_widget_show_all(cred_calc_main_window);
  gtk_main();
}