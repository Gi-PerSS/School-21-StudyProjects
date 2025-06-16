#!/usr/bin/env bash

Top5FolderSort() {

    # Общее число папок данного пути, исключая корневую.
    folders_total_number=$(($(find "$1" -type d | wc -l) - 1))

    echo "Total number of folders (including all nested ones) = $folders_total_number"

    # Первые 5 каталогов из папки, отсортированные по размеру в убывающем порядке
    # Проверка, существуют ли вложенные каталоги для печати в достаточном количестве.
    line2print=5
    if [ $folders_total_number -lt 5 ]; then
        line2print="$folders_total_number"
    fi

    top5folders=$(du -h "$1" | sort | tail "-$line2print")
    echo ""
    echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
    for ((i = 1; i <= "$line2print"; i++)); do
        path_line=$(echo "$top5folders" | grep -oE "\.{0,2}\/.*" | tail -n "$i" | head -1)
        directory_size=$(echo "$top5folders" | tail -n "$i" | head -1 | cut -f 1)
        right_output=""
        SizeFormatter "$directory_size"
        echo "$i - $path_line/, $right_output"
    done
}

# Top5FolderSort "$1"
