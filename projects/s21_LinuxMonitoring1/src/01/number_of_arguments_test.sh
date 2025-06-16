#!/usr/bin/env bash

# Проверка на корректность поданных данных.
DataCheck() {
    if [[ $1 != 1 ]]; then
        printf "Wrong number of arguments! %d.\nThere should be one.\n" "$1"
        exit 1
    fi
}
