#!/usr/bin/env bash

. "$(dirname "$0")/data_check.sh"

DataCheck "$@"
if [[ $? != 0 ]]; then
    exit 1
fi

declare -A color_values=(
    [1]='37' # White
    [2]='31' # Red
    [3]='32' # Green
    [4]='34' # Blue
    [5]='35' # Purple
    [6]='30' # Black
)

declare -A background_values=(
    [1]='47' # White
    [2]='41' # Red
    [3]='42' # Green
    [4]='44' # Blue
    [5]='45' # Purple
    [6]='40' # Black
)

Color_Off='\033[0m'

# Вызываем сбор данных в переменную
. "$(dirname "$0")/../02/script_body.sh"
InfoCollector "$results_holder"

# Разбираем и раскрашиваем результаты

# echo -e "\e[0;37;45m example\e[0m"
# -e - печатать непечатное; \e - то же, что \033, т.е. начало непечатного; первое число после [ - начертание шрифта, второе цвет, третье цвет фона.

color_prefix1="\e[0;${background_values[$1]};${color_values[$2]}m"
color_prefix2="\e[0;${background_values[$3]};${color_values[$4]}m"
color_postfix="\e[0m"

line=""

IFS=$'\n' # Input Field Separators, разделитель полей устанвливается строго как перевод строки (вместо набора из пробела, таба и перевода строки по умолчанию) Это позволяет считывать из переменной строки с пробелами внутри.

for line in $IC_results_holder; do
    tab1="$(echo "$line" | cut -d= -f 1)"
    tab2="$(echo "$line" | cut -d= -f 2)"
    echo -e "$color_prefix1$tab1$color_postfix=$color_prefix2$tab2$color_postfix"
done

exit 0

<<comment

Написать bash-скрипт. За основу взять скрипт из Part 2 и убрать из него часть, ответственную за сохранение данных в файл.
Скрипт запускается с 4 параметрами. Параметры числовые. От 1 до 6, например:
script03.sh 1 3 4 5
Обозначения цветов: (1 - white, 2 - red, 3 - green, 4 - blue, 5 – purple, 6 - black)
Параметр 1 - это фон названий значений (HOSTNAME, TIMEZONE, USER и т.д.)
Параметр 2 - это цвет шрифта названий значений (HOSTNAME, TIMEZONE, USER и т.д.)
Параметр 3 - это фон значений (после знака '=')
Параметр 4 - это цвет шрифта значений (после знака '=')
Цвета шрифта и фона одного столбца не должны совпадать.
При вводе совпадающих значений должно выводится сообщение, описывающее проблему, и предложение повторно вызвать скрипт.
После вывода сообщения, программа должна корректно завершится.
comment
