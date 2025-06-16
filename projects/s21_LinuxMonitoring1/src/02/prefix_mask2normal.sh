#!/usr/bin/env bash

prefix_mask2normal() {
    # Функция сохраняет результаты работы в переменную output_mask
    output_mask=
    binary_number=
    for ((i = 1; i <= $1; i++)); do
        binary_number+=1
        t=$(expr $i % 8)

        if (($t == 0)); then
            binary_number+='.'
        fi
    done

    for ((i = $(($1 + 1)); i <= 32; i++)); do
        binary_number+=0
        t=$(expr $i % 8)

        if (($t == 0)) && ((i != 32)); then
            binary_number+='.'
        fi
    done

    for ((i = 1; i <= 4; i++)); do
        actual_octet=$(echo "$binary_number" | cut -d"." -f "$i")

        t=$(echo "ibase=2; $actual_octet" | bc)
        output_mask+="$t"
        output_mask+='.'
    done

    # удаление последнего символа
    output_mask=${output_mask%?}

    #    echo $binary_number
    #    echo $output_mask
    return 0
}
