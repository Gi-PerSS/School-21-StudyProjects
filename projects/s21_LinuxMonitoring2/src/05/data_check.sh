#!/usr/bin/env bash

# Проверка на корректность поданных данных.
# Аргумент скритпа - число от 1 до 4.

DataCheck() {
    is_trouble=0

    # комментарий внутри функции
    ignored() {
        echo "Function name:  ${FUNCNAME}"
        echo "The number of positional parameter : $#"
        echo "All parameters or arguments passed to the function: '$@'"
        echo
    }

    # Если число переданных аргументов не равно 1 или выходит за рамки диапазона 1-4 отдаем ошибку.
    if [[ $# != 1 ]]; then
        printf "Wrong number of arguments. %d.\nThere should be one.\n" $#
        is_trouble=1
    else
        if (($1 < 1)) || (($1 > 4)); then
            printf "Give me another number, bro! 1-4.\n"
            is_trouble=1
        fi
    fi

    return $is_trouble
}
