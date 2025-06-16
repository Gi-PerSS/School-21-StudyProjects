#!/usr/bin/env bash

DataCheck() {
    is_trouble=0

    if [[ $# != 1 ]]; then
        printf "Wrong number of arguments! %d.\nThere should be 1.\n" "$#"
        is_trouble=1
    else
        if ! [[ $1 =~ [1-3]{1} ]]; then
            printf "Wrong number! There should be 1-3.\n"
            is_trouble=1
        fi
    fi

    return $is_trouble
}
