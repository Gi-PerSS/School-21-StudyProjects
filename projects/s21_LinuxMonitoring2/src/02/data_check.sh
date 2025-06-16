#!/usr/bin/env bash

# Вводные. Имена файлов в Linux могут быть длиной до 255 байт. Полная длина пути к файлу (включая имя файла) не должна превышать 4096 байт.

DataCheck() {
    is_trouble=0

    if [[ $# != 3 ]]; then
        printf "Wrong number of arguments! %d. There should be 6.\n" "$#"
        is_trouble=1
    fi

    # folder name
    if [[ ! $1 =~ ^[a-zA-Z]{1,7}$ ]]; then
        is_trouble=1
        echo "Something is wrong with the letters for the file names."
    fi

    # filename
    if [[ ! $2 =~ ^[a-zA-Z]{1,7}\.[a-zA-Z]{1,3}$ ]]; then
        echo "Something is wrong with the letters for the file names."
    fi

    local t=$(echo "$2" | cut -d"." -f1)
    if [[ $t =~ \(.\).*\1 || $3 =~ \(.\).*\1 ]]; then
        is_trouble=1
        echo "No duplicates characters in line!"
    fi

    local t=$(echo "$3" | grep -Eo "^[0-9]{1,3}[m,M]{1}[b,B]{0,1}$")
    if [ -z "$t" ]; then
        is_trouble=1
        echo "Filesize must be less than 100Mb. Right format for example is 1Mb"
    else
        t=$(echo "$t" | grep -Eo "^[0-9]{1,3}")

        if (($t > 100)); then
            echo "Filesize must be less than 100Mb."
            is_trouble=1
        fi
    fi

    return $is_trouble
}
