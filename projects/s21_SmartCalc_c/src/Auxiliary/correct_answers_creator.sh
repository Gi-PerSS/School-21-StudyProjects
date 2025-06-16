#!/usr/bin/env bash

function CorrectFormatFilter() {

    # Вопрос. Каким должно быть регулярное выражение, фильтрующее все строки с единственной точкой внутри? ==> ^([^;]*;){N}$ <== ???

    local answer=$2
    local math_expression=$1

    if [[ ! $answer == "" ]]; then
        if [[ ! $answer =~ ^.*\..*\..*$ ]]; then
            if [[ ! $answer =~ Error ]]; then
                echo "$math_expression=$answer" >>expressions_with_answers.txt
            fi
        fi
    fi

}

function Calculator() {
    local line
    local answer

    while IFS= read -r line; do
        answer=$(echo "$line" | calc -pd)
        CorrectFormatFilter "$line" "$answer"
    done <correct_math_expressions.txt
}

Calculator
