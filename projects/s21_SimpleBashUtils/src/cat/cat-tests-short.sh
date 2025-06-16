#!/bin/bash
# Полный путь к директории скрипта
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
TEMP_DIR="$SCRIPT_DIR/temp"
mkdir -p "$TEMP_DIR"

# Пути к исполняемым файлам
S21_CAT="$SCRIPT_DIR/../s21_cat" # Путь относительно директории скрипта
SYSTEM_CAT="$(which cat)"        # Полный путь к системному cat

# Проверка наличия билда
if [[ ! -f "$S21_CAT" ]]; then
    echo "Error: s21_cat not found at $S21_CAT"
    echo "Please build the project first"
    exit 1
fi

# Очистка предыдущих результатов
rm -f "$TEMP_DIR"/*_out*

# Массив тестовых флагов
flags=("" "-b" "-e" "-n" "-s" "-t" "-v" "-E" "-T"
    "--number-nonblank" "--number" "--squeeze-blank")

# Функция для сравнения выводов
run_test() {
    local flags=$1
    local input_files=$2

    "$S21_CAT" $flags $input_files >"$TEMP_DIR/s21_out" 2>&1
    "$SYSTEM_CAT" $flags $input_files >"$TEMP_DIR/cat_out" 2>&1

    if ! diff -u "$TEMP_DIR/s21_out" "$TEMP_DIR/cat_out" >"$TEMP_DIR/diff_result"; then
        echo "FAIL: flags [$flags] with files [$input_files]"
        cat "$TEMP_DIR/diff_result"
        return 1
    fi
    return 0
}

# Основной цикл тестирования
failed_tests=0
for flag1 in "${flags[@]}"; do
    # Тестируем одиночные флаги
    if ! run_test "$flag1" "$@"; then
        ((failed_tests++))
    fi

    # Тестируем парные комбинации
    for flag2 in "${flags[@]}"; do
        if [[ "$flag1" != "$flag2" ]]; then
            if ! run_test "$flag1 $flag2" "$@"; then
                ((failed_tests++))
            fi
        fi
    done
done

# Итоговый отчет
if [[ $failed_tests -eq 0 ]]; then
    echo "All tests passed successfully!"
    rm -rf "$TEMP_DIR"
    exit 0
else
    echo "Failed $failed_tests tests"
    echo "Debug files kept in $TEMP_DIR"
    exit 1
fi
