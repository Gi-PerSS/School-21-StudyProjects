#!/usr/bin/env bash

# выход из папки и обратный заход нужен для того, чтобы была возможность вызывать функцию, при включении этого файла через точку в другой скрипт. Иначе, подставяется неправильный путь.
. "$(dirname "$0")/../02/prefix_mask2normal.sh"

# нужно, чтобы printf принимал число с разделителем разрядов в виде точки, а не запятой.
export LC_NUMERIC="en_US.UTF-8"

IC_results_holder="" # глобальная перменная для сохранения результатов работы функции InfoCollector
function InfoCollector() {
    n=$'\n'
    IC_results_holder=$(echo "HOSTNAME = $(hostname)")$n
    IC_results_holder+="TIMEZONE = "$(timedatectl | grep "Time zone" | cut -d: -f2 | xargs)$n
    IC_results_holder+="USER = "$(whoami)$n
    IC_results_holder+="OS = "$(grep PRETTY_NAME /etc/os-release | cut -d= -f2)$n
    IC_results_holder+="DATE = "$(LC_ALL=en_US.UTF-8 date +"%d %b %Y %T")$n
    IC_results_holder+="UPTIME = "$(uptime -p)$n
    IC_results_holder+="UPTIME_SEC = "$(cut -d' ' -f1 /proc/uptime)$n

    # Не самый лучший способ, но самый быстрый в моменте. Алгоритм: из списка интерфейсов выбираем строки со словом inet, исключаем оттуда loopback, выделяем все ip адреса, отдаем первый из списка (второй широковещательный brd)
    IC_results_holder+="IP = "$(ip addr | grep -w inet | grep -v "inet 127." | grep -o '[0-9]\+[.][0-9]\+[.][0-9]\+[.][0-9]\+' | head -n1)$n

    # Выделяем ip/mask
    t=$(ip addr | grep -w inet | grep -v "inet 127." | grep -o '[0-9]\+[.][0-9]\+[.][0-9]\+[.][0-9]\+\/[0-9]\+' | head -n1)
    t=$(echo "$t" | cut -d'/' -f 2)
    output_mask=
    prefix_mask2normal "$t"
    IC_results_holder+="MASK = "$(echo $output_mask)$n

    #    IC_results_holder+="MASK = "$(ifconfig | grep -w inet | grep -v "inet 127." | grep -o 'netmask [0-9]\+[.][0-9]\+[.][0-9]\+[.][0-9]\+' | grep -o '[0-9]\+[.][0-9]\+[.][0-9]\+[.][0-9]\+' | head -n1)$n

    IC_results_holder+="GATEWAY = "$(ip r | grep "default via " | grep -o '[0-9]\+[.][0-9]\+[.][0-9]\+[.][0-9]\+' | head -1)$n

    # Переменная MB для вычислений, может принимать значение 1000 или 1024, в зависимости от предпочтений запускающего скрипт.
    MB=1000
    RAM_total=$(grep MemTotal /proc/meminfo | echo "scale=3; $(grep -oE "[0-9]{1,}")/$MB/$MB" | bc | xargs printf "%.3f")
    RAM_free=$(grep MemFree /proc/meminfo | echo "scale=3; $(grep -oE "[0-9]{1,}")/$MB/$MB" | bc | xargs printf "%.3f")
    RAM_used_memory_size=$(vmstat -s | grep "used memory" | echo "scale=3; $(grep -Eo [0-9]+)/$MB/$MB" | bc | xargs printf "%.3f")

    #    RAM_used_memory_size=$(echo "scale=3; $RAM_total - $RAM_free" | bc | xargs printf "%.3f")

    IC_results_holder+="RAM_TOTAL = "$RAM_total" GB"$n
    IC_results_holder+="RAM_USED = $RAM_used_memory_size GB"$n
    IC_results_holder+="RAM_FREE = $RAM_free GB"$n

    #Размер раздела по команде df отдается в виде 1024-байтовых блоков, умножаем на 1024 и делим на 1 000 000 (Или на 1 073 741 824).

    root_volume_size=$(echo "scale=2; $(df -kP | grep \/$ | tr -s ' ' | cut -d' ' -f 2)*1024/$MB/$MB" | bc | xargs printf "%.2f")
    IC_results_holder+="SPACE_ROOT = "$root_volume_size" MB"$n

    root_used=$(echo "scale=2; $(df -kP | grep \/$ | tr -s ' ' | cut -d' ' -f 3)*1024/$MB/$MB" | bc | xargs printf "%.2f")
    IC_results_holder+="SPACE_ROOT_USED = "$root_used" MB"$n

    root_available=$(echo "scale=2; $(df -kP | grep \/$ | tr -s ' ' | cut -d' ' -f 4)*1024/$MB/$MB" | bc | xargs printf "%.2f")
    IC_results_holder+="SPACE_ROOT_FREE = "$root_available" MB"
}
