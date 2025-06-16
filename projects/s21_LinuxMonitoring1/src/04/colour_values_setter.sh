#!/usr/bin/env bash

function ColourValuesSetter() {

    # Если один или несколько параметров не заданы в конфигурационном файле, то цвет должен подставляться из цветовой схемы, заданной по умолчанию. (Выбор на усмотрение разработчика).

    # Цветовая схема по умолчанию
    colour_values=(6 1 6 1)

    is_default_colors=no

    # Читаем конфигурационный файл, как скрипт, где задаются значения переменных. ВНИМАНИЕ. При неправильном оформлении происходит ошибка "command not found"
    . "$(dirname "$0")/colours.conf"

    # Убираем цвета одинаковые с фоном.
    if [[ $column1_background == $column1_font_color ]] || [[ $column2_background == $column2_font_color ]]; then
        is_default_colors=yes
    fi

    # Заполняем массив новой цветовой схемы
    t_colour_values=("$column1_background" "$column1_font_color" "$column2_background" "$column2_font_color")

    # Проверяем переменные на корректность значений
    for ((i = 0; i < 4; i++)); do
        if [[ ! ${t_colour_values[$i]} =~ ^[1-6]$ ]]; then
            is_default_colors=yes
        fi
    done

    # Заполняем массив цветовой схемы
    if [[ $is_default_colors == "no" ]]; then

        for ((i = 0; i < 4; i++)); do
            if [[ ${t_colour_values[$i]} =~ ^[1-6]$ ]]; then
                colour_values["$i"]=${t_colour_values[$i]}
            fi
        done

    fi
}
