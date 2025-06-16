#!/usr/bin/env bash

#Вывод времени исполнения скрипта
start=$(date +%s000)

. "$(dirname "$0")/data_check.sh"
. "$(dirname "$0")/size_formatter.sh"
. "$(dirname "$0")/top5_folder_sort.sh"
. "$(dirname "$0")/files_print.sh"

DataCheck "$@"
if [[ ! $? == 0 ]]; then
    echo "Need rigth path! Give it to me!"
    exit 1
fi

Top5FolderSort "$1"
FilesDataPrint "$1"

#Вывод времени исполнения скрипта
end=$(date +%s000)
runtime=$(echo "scale=3; ($end - $start)/1000" | bc | xargs printf "%.1f")
echo ""
echo "Script execution time (in seconds) = $runtime"
