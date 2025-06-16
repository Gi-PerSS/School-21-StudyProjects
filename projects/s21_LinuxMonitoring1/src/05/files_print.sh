#!/usr/bin/env bash

FilesDataPrint() {
    # Всего файлов
    files_total_number=$(find "$1" -type f | wc -l)
    echo ""
    echo "Total number of files = $files_total_number"

    # Разных файлов
    confs_number=$(find "$1" -type f -name "*.conf" | wc -l)
    txts_numbers=$(find "$1" -type f -name "*.txt" | wc -l)
    execs_numbers=$(find "$1" -type f -executable | wc -l)
    logs_numbers=$(find "$1" -type f -name "*.log" | wc -l)
    archs_numbers=$(find "$1" -type f -exec file -zb {} \; | grep -c "archive")
    symblinks_numbers=$(find "$1" -type l | wc -l)

    echo ""
    printf "Number of:  
Configuration files (with the .conf extension) = $confs_number
Text files = $txts_numbers
Executable files = $execs_numbers
Log files (with the extension .log) = $logs_numbers
Archive files = $archs_numbers
Symbolic links = $symblinks_numbers
"

    # Первые 10 файлов из папки, отсортированные по размеру в убывающем порядке.
    # Проверка, существуют ли файлы для печати в достаточном количестве.
    line2print=10
    if (($files_total_number < 10)); then
        line2print=$files_total_number
    fi
    top10files=$(find "$1" -type f -printf '%s\t%p\n' | sort -nr | head -10)
    echo ""
    echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
    for ((i = 1; i <= ${line2print}; i++)); do
        t=$(("$line2print" + 1 - "$i"))
        filename_line=$(echo "$top10files" | tail -n $t | head -1 | cut -f2)
        file_size=$(echo "$top10files" | tail -n $t | head -1 | cut -f1 | numfmt --to=si)
        right_output="" # переменная-холдер для отформатированного постфикса размерности
        SizeFormatter "$file_size"
        filename="${filename_line##*/}" #выделяем имя без пути, чтобы выделить расширение
        extension=${filename##*.}       # выделяем расширение
        echo "$i - $filename_line, $right_output, $extension"
    done

    # Первые 10 исполняемых файлов из папки, отсортированные по размеру в убывающем порядке.
    top10files=$(find "$1" -type f -executable -printf '%s\t%p\n' | sort -nr | head -10)

    # Проверка, существуют ли файлы для печати в достаточном количестве.
    exec_files_number=$(echo "$top10files" | wc -l)
    line2print=10
    if (($exec_files_number < 10)); then
        line2print=$exec_files_number
    fi
    echo ""
    echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file): "
    for ((i = 1; i <= ${line2print}; i++)); do
        t=$(("$line2print" + 1 - "$i"))
        filename_line=$(echo "$top10files" | tail -n $t | head -1 | cut -f2)
        file_size=$(echo "$top10files" | tail -n $t | head -1 | cut -f1 | numfmt --to=si)
        right_output="" # переменная-холдер для отформатированного постфикса размерности
        SizeFormatter "$file_size"
        md5hash=$(md5sum "$filename_line" | cut -d' ' -f 1)
        echo "$i - $filename_line, $right_output, $md5hash"
    done
}
