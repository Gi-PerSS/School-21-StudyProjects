#!/usr/bin/env bash

clear

. "$(dirname "$0")/data_check.sh"

# Передаем количество аргументов на проверку.
DataCheck "$@" # "$@" - все аргументы скрипта ушли в функцию

if [[ $? != 0 ]]; then # $? - код возврата последней исполненной команды.
    exit 1
fi

# Проверяем установлен ли пакет, если нет, ставим
prometheus_status=$(which prometheus)
must_be_status="/usr/local/bin/prometheus"

if [[ $prometheus_status != $must_be_status ]]; then
    {
        . "$(dirname "$0")/prometheus_install.sh"
        prometheus_install
    }
else
    {
        clear
        sudo systemctl start prometheus
        sudo systemctl status prometheus
    }
fi

# Проверяем установлен ли пакет, если нет, ставим и настраиваем
nginx_status="$(dpkg -s nginx | grep Status:)"
must_be_status="Status: install ok installed"

if [[ $nginx_status != $must_be_status ]]; then
    {
        . "$(dirname "$0")/nginx_install.sh"
        NginxInstall
        NginxConfiguring
    }
else
    {
        clear
        . "$(dirname "$0")/nginx_install.sh"
        NginxConfiguring
        sudo systemctl start nginx
        systemctl status nginx
    }
fi

# Проверяем установлен ли пакет, если нет, ставим
node_exporter_status="$(which node_exporter)"
must_be_status="/usr/local/bin/node_exporter"
if [[ $node_exporter_status != $must_be_status ]]; then
    {
        . "$(dirname "$0")/node_exporter_install.sh"
        NodeExporterInstall
    }
else
    {
        clear
        sudo systemctl start node_exporter
        sudo systemctl status node_exporter
    }
fi

# Проверяем установлен ли пакет, если нет, ставим
grafana_status="$(snap list | grep grafana -o)"
must_be_status="grafana"

if [[ $grafana_status != $must_be_status ]]; then
    {
        # для установки пакета есть три варианта, непонятно какой из них сработал, т.к. сервер запустился после исполнения всех трех вариантов и последующей перезагрузки.
        . "$(dirname "$0")/grafana_install.sh"
        # GrafanaSourceforgeInstall
        # GrafanaInstall
         GrafanaDebInstall
         GrafanaSnapInstall
         sudo reboot
        # StackOverflowGrafanaInstall
        # GrafanaAntonPutraInstall

    }
else
    {
        clear
    #    sudo grafana-server -homepath /usr/share/grafana
        sudo /bin/systemctl daemon-reload
    #    sudo /bin/systemctl enable grafana-server
        sudo systemctl start grafana-server
        sudo systemctl status grafana-server
    }
fi