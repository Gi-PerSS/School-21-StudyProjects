#!/usr/bin/env bash

# Проверка на корректность поданных данных.
DataCheck() {
    if [[ $1 != 0 ]]; then
        printf "Wrong number of arguments! %d.\nThere should be no arguments!\n" "$1"
        exit 1
    fi
}
