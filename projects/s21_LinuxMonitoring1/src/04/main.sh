#!/usr/bin/env bash
# Передаем количество аргументов на проверку.
. "$(dirname "$0")/number_of_arguments_test.sh"
DataCheck $#

# Устанавливаем цветовую схему в массив colour_value
. "$(dirname "$0")/colour_values_setter.sh"
ColourValuesSetter

# Вызываем печать. Массив должен передаваться отдельными значениями, иначе принимающий скрипт воспринимает строку как один аргумент.
bash "$(dirname "$0")/../03/main.sh" "${colour_values[0]}" "${colour_values[1]}" "${colour_values[2]}" "${colour_values[3]}"

# Печать цветов и их кодов
declare -A colour_codes=(
    [1]=White
    [2]=Red
    [3]=Green
    [4]=Blue
    [5]=Purple
    [6]=Black
)

# Выбор варианта легенды, по умолчанию или нет.
# Переменные для облегчения восприятия кода ниже.
cv0="${colour_values[0]}"
cv1="${colour_values[1]}"
cv2="${colour_values[2]}"
cv3="${colour_values[3]}"

if [[ $is_default_colors == "no" ]]; then
    printf "
Column 1 background = "${colour_values[0]}" ("${colour_codes[$cv0]}")
Column 1 font color = "${colour_values[1]}" ("${colour_codes[$cv1]}")
Column 2 background = "${colour_values[2]}" ("${colour_codes[$cv2]}")
Column 2 font color = "${colour_values[3]}" ("${colour_codes[$cv3]}")
"
else
    printf "
Column 1 background = "default" ("${colour_codes[$cv0]}")
Column 1 font color = "default" ("${colour_codes[$cv1]}")
Column 2 background = "default" ("${colour_codes[$cv2]}")
Column 2 font color = "default" ("${colour_codes[$cv3]}")
"
fi
