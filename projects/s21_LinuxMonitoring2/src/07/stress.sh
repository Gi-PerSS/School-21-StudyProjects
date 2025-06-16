#!/usr/bin/env bash

# Проверяем установлен ли пакет, если нет, ставим
stress_status="$(which stress)"
must_be_status="/usr/bin/stress"
if [[ $stress_status != $must_be_status ]]; then
    {
        sudo apt install stress
    }
else
    {
        which stress
    }
fi

# stress -c 2 -i 1 -m 1 --vm-bytes 32M -t 10s
stress -c 2 -i 1 -m 1 --vm-bytes 32M -t 120s
