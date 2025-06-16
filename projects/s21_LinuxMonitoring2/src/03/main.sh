#!/usr/bin/env bash

. "$(dirname "$0")/data_check.sh"

# Передаем количество аргументов на проверку.
DataCheck "$@"

if [[ $? != 0 ]]; then # dbg
    exit 1
fi

function FilesDeleteByLog() {
    # $1 - путь к лог-файлу
    awk '{print $1}' $1 | xargs rm -f
}

function FilesDeleteByDateTime() {
    cd "$(dirname "$0")/../02/"
    # Date input
    local date
    local ttime

    read -p "Enter filescreation date BEGIN, format: Year-Month-Day: " date
    echo "date - $date"
    read -p "Enter filescreation time BEGIN, format: Hour:Minutes: " ttime
    echo "time - $ttime"
    ttime+=":00"
    local date_begin="$date "
    date_begin+=$ttime

    read -p "Enter filescreation date END, format: Year-Month-Day: " date
    echo "date - $date"
    read -p "Enter filescreation time END, format: Hour:Minutes: " ttime
    echo "time - $ttime"
    ttime+=":00"
    local date_end="$date "
    date_end+=$ttime

    echo "Begin range - $date_begin"
    echo "End of range - $date_end"
    echo "Lets ddddelete it!"
    find -newermt "$date_begin" ! -newermt "$date_end" >t.log
    echo "The list of files to delete has been created. Uncomment the function call manually if you really want to."
    # FilesDeleteByLog t.log
}

function FilesDeleteByNameMask() {
    cd "$(dirname "$0")/../02/"
    find . -type f | grep -E ".*[a-zA-Z]_[0-9]{8}\.[a-zA-Z]{1,3}" >t.log
    FilesDeleteByLog t.log
}

# main()

case $1 in

1)
    log_path="$(dirname "$0")/../02/file_creation.log"
    cd "$(dirname "$0")/../02/"
    if [ -e "./file_creation.log" ]; then
        FilesDeleteByLog "./file_creation.log"
        cd "$(dirname "$0")" || exit
    else
        echo "No log files. Stop."
        exit 1
    fi

    ;;

2)
    FilesDeleteByDateTime
    ;;

3)
    FilesDeleteByNameMask
    ;;

*)
    echo -n "unknown command"
    ;;
esac

# FilesDeleteByDateTime
