# Проверка на корректность поданных данных.

DataCheck() {
    is_trouble=0

    # Если число переданных аргументов не равно 0 отдаем ошибку.
    if [[ $# != 0 ]]; then
        printf "Wrong number of arguments. %d.\nThere should no argument.\n" $#
        is_trouble=1
    fi

    return $is_trouble
}
