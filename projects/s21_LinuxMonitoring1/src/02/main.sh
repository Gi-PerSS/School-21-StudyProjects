#!/usr/bin/env bash

# Передаем количество аргументов на проверку.
. "$(dirname "$0")/number_of_arguments_test.sh"
DataCheck $#

# Вызываем сбор данных в переменную
. "$(dirname "$0")/script_body.sh"

InfoCollector "$results_holder"
echo "$IC_results_holder"

# Предлагаем записать в файл и пишем если да
. "$(dirname "$0")/is_save_data_2file.sh"
Is_Save_Data_2File
if [[ "$is_save" == 1 ]]; then
    echo "$IC_results_holder" >"$(dirname "$0")/$(LC_ALL=en_US.UTF-8 date +"%d_%b_%Y_%H_%M_%S").status"
fi
