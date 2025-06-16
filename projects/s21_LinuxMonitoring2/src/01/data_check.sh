#!/usr/bin/env bash

# Вводные. Имена файлов в Linux могут быть длиной до 255 байт. Полная длина пути к файлу (включая имя файла) не должна превышать 4096 байт.

DataCheck() {
    is_trouble=0

    if [[ $# != 6 ]]; then
        printf "Wrong number of arguments! %d. There should be 6.\n" "$#"
        is_trouble=1
    fi

    if [ ! -d "$1" ]; then
        is_trouble=1
        echo "Something is wrong with directory name. May be it doesnt exist."
    fi

    # Пример /^[a-z]{0,10}$/
    if [[ ! $3 =~ ^[a-zA-Z]{1,7}$ ]]; then
        is_trouble=1
        echo "Something is wrong with the letters for the file names."
    fi

    if [[ ! $5 =~ ^[a-zA-Z]{1,7}\.[a-zA-Z]{1,3}$ ]]; then
        echo "Something is wrong with the letters for the file names."
    fi

    local t=$(echo "$5" | cut -d"." -f1)
    if [[ $t =~ \(.\).*\1 || $3 =~ \(.\).*\1 ]]; then
        is_trouble=1
        echo "No duplicates characters in line!"
    fi

    local t=$(echo "$6" | grep -Eo "^[0-9]{1,3}[k,K]{1}[b,B]{0,1}$")
    if [ -z "$t" ]; then
        is_trouble=1
        echo "Filesize must be less than 100Kb. Right format for example is 1Kb"
    else
        t=$(echo "$t" | grep -Eo "^[0-9]{1,3}")

        if (($t > 100)); then
            echo "Filesize must be less than 100Kb."
            is_trouble=1
        fi
    fi

    return $is_trouble
}
