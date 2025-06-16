#!/usr/bin/env bash

. "$(dirname "$0")/number_of_arguments_test.sh"
. "$(dirname "$0")/is_number_test.sh"

# Передаем количество аргументов на проверку.
DataCheck $#

# Проверяем на число
IsNumber "$1"
if [[ $? == 1 ]]; then
    echo "Given argument is $1. Value is a number! U must give me a string!!"
    exit 1
else
    echo "$1"
fi
