#!/usr/bin/env bash

script_time_start=$SECONDS
script_start=$(date +%T)

. "$(dirname "$0")/data_check.sh"

# Передаем количество аргументов на проверку.
DataCheck "$@"

if [[ $? != 0 ]]; then # dbg
    exit 1
fi

. "$(dirname "$0")/../01/functions.sh"

free_space_limit=$(echo 1G | numfmt --from=si) # $(echo 1G |numfmt --from=si) | $(echo 333M | numfmt --from=si)
path=""
nested_folders=1
letters_for_folders=$1
files_in_folder=0
letters_for_filenames=$(echo "$2" | cut -d"." -f1)
file_extension=$(echo "abc.zx" | cut -d"." -f2)
size_of_files=$(echo "$3" | grep -Eo "^[0-9]{1,3}") #3
sizefix="M"
fldr_min_name_length=5
files_min_name_length=5

# Генерирует случайный путь из имеющихся в системе, исключая пути с bin в названии.
function RandomPathGenerator() {

    local f="$(dirname "$0")/to_trashing.txt"
    if ! [ -e "$f" ]; then
        echo "file creating"
        sudo find / -type d | grep bin -v >$f
    fi
    local folders_in_system=$(cat "$f" | wc -l)
    local number_of_line=$(echo "-i 0-$folders_in_system -n 1" | xargs shuf)
    echo $(sed -n "${number_of_line}p" "$f")

    # echo ./tmp_for_testing
}

function RandomNumberForFiles() {
    local number_of_files=$(shuf -i 1-100 -n 1)
    echo $number_of_files
}

function CleanIn01() {
    clear
    rm -f "$(dirname "$0")/../01/folder_creation.log"
    rm -f "$(dirname "$0")/../01/file_creation.log"
    rm -rf "$(dirname "$0")/../01/tmp_for_testing"
    rm -rf "$(dirname "$0")/../01/file_creation.log"
    rm -rf "$(dirname "$0")/../01/general_file_creation.log"
}

function Trashing() {

    free_space_left=$(df -h . | awk '{print $4}' | grep -Eo [0-9].* | numfmt --from=si)
    filenameletters_line_length=$(StrLen $letters_for_filenames)
    echo "free space left - $(numfmt --to=si $free_space_left)"
    echo "trashing is starting... wait, pls"
    while (($free_space_left > $free_space_limit)); do
        {
            echo "Free space left - $free_space_left"
            files_in_folder=$(RandomNumberForFiles)
            path="$(RandomPathGenerator)"
            path+='/trash/'
            echo $path
            mkdir $path
            max_name_length=$((5 + $(StrLen $letters_for_filenames) * 2 + $files_in_folder / 3)) # 245
            files_for_create=$files_in_folder
            #    echo "DBG. max_name_length - $max_name_length, files_for_create - $files_for_create, letters_for_filenames - $letters_for_filenames"

            RFilenamesGenerator 1 "" $path "files"
        }
    done
}

# main()
CleanIn01
Trashing

script_end=$(date +%T)
echo "Script start time - $script_start, script end time - $script_end"
script_time_end=$SECONDS
echo "Scripts execution time is $((script_time_end - script_time_start)) s"

: <<'comment'
== Задание ==
Написать bash-скрипт. Скрипт запускается с 6 параметрами. Пример запуска скрипта: 
main.sh /opt/test 4 az 5 az.az 3kb
Параметр 1 - это абсолютный путь. 
Параметр 2 - количество вложенных папок. 
Параметр 3 - список букв английского алфавита, используемый в названии папок (не более 7 знаков). 
Параметр 4 - количество файлов в каждой созданной папке. 
Параметр 5 - список букв английского алфавита, используемый в имени файла и расширении (не более 7 знаков для имени, не более 3 знаков для расширения). 
Параметр 6 - размер файлов (в килобайтах, но не более 100).
Имена папок и файлов должны состоять только из букв, указанных в параметрах, и использовать каждую из них хотя бы 1 раз.
Длина этой части имени должна быть от 4 знаков, плюс дата запуска скрипта в формате DD.MM.YY, отделённая нижним подчёркиванием, например: 
./aaaz_021121/, ./aaazzzz_021121
При этом, если для имени папок или файлов были заданы символы az, то в названии файлов или папок не может быть обратной записи: 
./zaaa_021121/, т.е. порядок указанных символов в параметре должен сохраняться.
При запуске скрипта в указанном в параметре 1 месте, должны быть созданы папки и файлы в них с соответствующими именами и размером.
Скрипт должен остановить работу, если в файловой системе (в разделе /) останется 1 Гб свободного места.
Записать лог файл с данными по всем созданным папкам и файлам (полный путь, дата создания, размер для файлов).
comment
