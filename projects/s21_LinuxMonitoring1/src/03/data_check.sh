#!/usr/bin/env bash

# Проверка на корректность поданных данных.
# Значений ровно 4, все они в диапазоне от 1 до 6, все они положительные цифры.

DataCheck() {
    return_value=0

    if [[ $# != 4 ]]; then
        #        echo "number of parameters is $#"
        printf "Скрипт запускается с 4 параметрами. Параметры числовые. От 1 до 6.
Параметр 1 - это фон названий значений (HOSTNAME, TIMEZONE, USER и т.д.)
Параметр 2 - это цвет шрифта названий значений (HOSTNAME, TIMEZONE, USER и т.д.)
Параметр 3 - это фон значений (после знака '=')
Параметр 4 - это цвет шрифта значений (после знака '=')'
Обозначения цветов: (1 - white, 2 - red, 3 - green, 4 - blue, 5 – purple, 6 - black)
Цвета шрифта и фона одного столбца не должны совпадать.
Try again.\n"

        # printf "Wrong number of arguments! %d.\nThere should be four.\n" "$#"
        return_value=1
    else
        for i in $@; do
            if [[ ! $i =~ ^[1-6]$ ]]; then
                printf "The color value should be in the range from 1 to 6. U can try again.\n"
                return_value=1
                break
            fi
        done
    fi

    if [[ $return_value != 1 ]]; then

        if [[ $1 == $2 ]] || [[ $3 == $4 ]]; then
            printf "The font and background color should be different. U can try again.\n"
            return_value=1
        fi

    fi

    return $return_value
}
