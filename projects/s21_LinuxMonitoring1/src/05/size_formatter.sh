#!/usr/bin/env bash

SizeFormatter() {
    # Функция форматирует строку с данными о размерах директорий под требование задания: из К делается KB, M => MB, etc.
    local number="$(echo "$1" | grep -oE "[0-9]*\.*[0-9]*")"
    local postfix="$(echo "$1" | grep -oE "[a-zA-Z]*")"
    right_output="$number $postfix"B
    return 0
}

# SizeFormatter "$(echo "3997" | numfmt --to=si)"
