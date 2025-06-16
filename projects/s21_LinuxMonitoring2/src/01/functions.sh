#!/usr/bin/env bash

# Функция отдает длину переменной, поступившей на вход.
function StrLen() {
    r=$(echo $1 | wc -c)
    let r=r-1
    echo "$r"
}

# $1 - строка символов, $2 - индекс символа для извлечения
function CharByIndex() {
    r=$(printf '%s\n' "$1" | cut -c $2)
    echo "$r"
}

max_name_length=0 # инициализируется из функции JobExecutor
# $1 - индекс буквы с которой продолжается формирование имени файла в рекурсивной итерации
# $2 - имя файла без расширения
# $3 - путь до имени файла
# $4 - режим работы функции: folders || files
# files_for_create - оставшееся число файлов для создания
files_for_create=0
function RFilenamesGenerator() {
    local letter_index=$1
    local filename=$2
    while (($(StrLen $filename) != $max_name_length && $files_for_create != 0)); do

        local actual_letter=$(CharByIndex "$letters_for_filenames" "$letter_index")

        filename=$filename$actual_letter
        if (($letter_index < $filenameletters_line_length)); then
            {
                local new_invokation_filename=$filename
                RFilenamesGenerator $letter_index $new_invokation_filename $3 $4
                letter_index=$(($1 + 1))
            }
        else
            { # проверяем есть ли место, если да, то создаем файлы
                local free_space_left=$(df -h . | awk '{print $4}' | grep -Eo [0-9].* | numfmt --from=si)

                if (($free_space_left > $free_space_limit)); then
                    {
                        if [[ $4 == "files" ]]; then
                            if (($(StrLen $filename) >= $files_min_name_length)); then
                                # local full_path="$3$filename.$file_extension"_"$(date '+%d%m%Y')"
                                local full_path=$3
                                full_path+=$filename
                                full_path+="_"
                                full_path+=$(date '+%d%m%Y')
                                full_path+="."
                                full_path+=$file_extension

                                if grep $full_path "$(dirname "$0")/file_creation.log"; then
                                    # echo "This name already exists"
                                    continue
                                else
                                    fallocate -l "$size_of_files$sizefix" "$full_path"
                                    files_for_create=$(($files_for_create - 1))

                                    local txt_to_log=$full_path
                                    txt_to_log+=" "
                                    txt_to_log+=$(date +%D)
                                    txt_to_log+=" "
                                    txt_to_log+=$size_of_files
                                    txt_to_log+=$sizefix
                                    echo "$txt_to_log" | tee -a "$(dirname "$0")/file_creation.log"
                                fi
                            fi
                        else
                            # создаем папки
                            local full_path="$3$filename"
                            if grep $full_path "$(dirname "$0")/folder_creation.log"; then
                                # echo "This name already exists"
                                continue
                            else
                                mkdir $full_path
                                files_for_create=$(($files_for_create - 1))
                                echo "$full_path" | tee -a "$(dirname "$0")/folder_creation.log"
                            fi
                        fi
                    }
                else
                    {
                        echo "Free space less than 1G"
                        exit
                    }
                fi
            }
        fi
    done
}

# $1 - количество вложенных папок

function FoldernamesGenerator() {
    # В задании ничего не сказано об уникальности имен вложенных папок, поэтому они будут называться одинаково и уходить вглубь, но не в ширину.

    # Делаем длину имени 4 если меньше
    local foldername=$letters_for_folders
    local last_index=$(StrLen $letters_for_folders)

    while (($(StrLen $foldername) < $fldr_min_name_length)); do
        foldername=$foldername$(CharByIndex $letters_for_folders $last_index)
    done

    local fullname=$path
    for ((i = 0; i < $1; i++)); do
        fullname="$fullname$foldername/"
        mkdir "$fullname"                                                               # папки должны создаваться здесь для корректной работы fallocate
        max_name_length=$((5 + filenameletters_line_length * 2 + $files_in_folder / 3)) # 245
        files_for_create=$files_in_folder
        RFilenamesGenerator 1 "" $fullname "files"
    done
}

function JobExecutor() {
    # Но можно сделать и в ширину, а не в глубину.

    # Создаем набор папок и логируем их
    local t=$(StrLen $letters_for_folders)
    max_name_length=$((5 + t * 3 + $nested_folders / 3))
    echo "Folders creation is starting ====>"
    files_for_create=$nested_folders # для создания папок
    RFilenamesGenerator 1 "" $path "folders"

    # Парсим лог и для каждой созданной папки запускаем создание файлов
    # Сложность конструкции нужна для гарантированной обработки последней строки файла, если там нет перевода строки
    max_name_length=$((filenameletters_line_length * 2 + files_in_folder / 3)) # 245
    while IFS='' read -r folder_path || [ -n "${folder_path}" ]; do
        echo "processing folder_path: ${folder_path} ====> "
        files_for_create=$files_in_folder
        touch "$(dirname "$0")/file_creation.log"
        RFilenamesGenerator 1 "" "$folder_path/" "files"
        echo "=====================" >>"$(dirname "$0")/general_file_creation.log"
        cat "$(dirname "$0")/file_creation.log" >>"$(dirname "$0")/general_file_creation.log"
        rm file_creation.log
    done <"$(dirname "$0")/folder_creation.log"
}

function Clean() {
    clear
    rm -f "$(dirname "$0")/folder_creation.log"
    rm -f "$(dirname "$0")/file_creation.log"
    rm -rf "$(dirname "$0")/tmp_for_testing"
    rm -rf "$(dirname "$0")/file_creation.log"
    mkdir "$(dirname "$0")/tmp_for_testing"
}
