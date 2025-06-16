#!/usr/bin/env bash

clear

. "$(dirname "$0")/data_check.sh"

# Передаем количество аргументов на проверку.
DataCheck "$@" # "$@" - все аргументы скрипта ушли в функцию

if [[ $? != 0 ]]; then # $? - код возврата последней исполненной команды.
    exit 1
fi

# Проверяем установлен ли пакет, если нет, ставим
is_goaccess_installed=$(which goaccess)
if [[ -z ${is_goaccess_installed} ]]; then
    {
        sudo apt-get update
        sudo apt full-upgrade
        sudo apt-get install goaccess
    }
fi

goaccess -m --enable-panel=REQUESTS "$(dirname "$0")/../04/nginx_logfile_1.log" "$(dirname "$0")/../04/nginx_logfile_2.log" "$(dirname "$0")/../04/nginx_logfile_3.log" "$(dirname "$0")/../04/nginx_logfile_4.log" "$(dirname "$0")/../04/nginx_logfile_4.log"

goaccess "$(dirname "$0")/../04/nginx_logfile_1.log" "$(dirname "$0")/../04/nginx_logfile_2.log" "$(dirname "$0")/../04/nginx_logfile_3.log" "$(dirname "$0")/../04/nginx_logfile_4.log" "$(dirname "$0")/../04/nginx_logfile_4.log" -a -o report.html

# goaccess "$(dirname "$0")/../04/nginx_logfile_1.log" "$(dirname "$0")/../04/nginx_logfile_2.log" "$(dirname "$0")/../04/nginx_logfile_3.log" "$(dirname "$0")/../04/nginx_logfile_4.log" "$(dirname "$0")/../04/nginx_logfile_4.log" -o /var/www/html/report.html --log-format=COMBINED --real-time-html
