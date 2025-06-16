#!/usr/bin/env bash

function GrafanaDebInstall() {
    wget https://dl.grafana.com/oss/release/grafana_9.2.4_amd64.deb
    sudo dpkg -i grafana_9.2.4_amd64.deb

    sudo mkdir '/usr/share/grafana'
    sudo /bin/systemctl daemon-reload
    sudo /bin/systemctl enable grafana-server
    sudo systemctl start grafana-server
    rm grafana_9.2.4_amd64.deb
}

function GrafanaSnapInstall() {

    sudo apt-get update
    sudo apt-get upgrade
    sudo snap install grafana

    #    wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
    #   sudo add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"

   sudo tee /etc/systemd/system/grafana-server.service <<EOF
    [Unit]
    Description=Grafana instance
    Documentation=http://docs.grafana.org
    Wants=network-online.target
    After=network-online.target
    After=postgresql.service mariadb.service mysql.service

    [Service]
    EnvironmentFile=/etc/default/grafana-server
    User=grafana
    Group=grafana
    Type=simple
    Restart=on-failure
    WorkingDirectory=/usr/share/grafana
    RuntimeDirectory=grafana
    RuntimeDirectoryMode=0750
    ExecStart=/usr/share/grafana/bin/grafana server \
        --config=${CONF_FILE} \
        --pidfile=${PID_FILE_DIR}/grafana-server.pid \
        --packaging=deb \
        cfg:default.paths.logs=${LOG_DIR} \
        cfg:default.paths.data=${DATA_DIR} \
        cfg:default.paths.plugins=${PLUGINS_DIR} \
        cfg:default.paths.provisioning=${PROVISIONING_CFG_DIR}

    LimitNOFILE=10000
    TimeoutStopSec=20
    CapabilityBoundingSet=
    DeviceAllow=
    LockPersonality=true
    MemoryDenyWriteExecute=false
    NoNewPrivileges=true
    PrivateDevices=true
    PrivateTmp=true
    ProtectClock=true
    ProtectControlGroups=true
    ProtectHome=true
    ProtectHostname=true
    ProtectKernelLogs=true
    ProtectKernelModules=true
    ProtectKernelTunables=true
    ProtectProc=invisible
    ProtectSystem=full
    RemoveIPC=true
    RestrictAddressFamilies=AF_INET AF_INET6 AF_UNIX
    RestrictNamespaces=true
    RestrictRealtime=true
    RestrictSUIDSGID=true
    SystemCallArchitectures=native
    UMask=0027

    [Install]
    WantedBy=multi-user.target
EOF

    sudo /bin/systemctl daemon-reload
    sudo /bin/systemctl enable grafana-server
    sudo systemctl start grafana-server
}

function StackOverflowGrafanaInstall() {
    sudo apt-get install -y gnupg2 curl
    curl https://packages.grafana.com/gpg.key | sudo apt-key add -
    sudo add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
    sudo apt-get update
    sudo apt-get -y install grafana
    sudo systemctl start grafana-server
}

function GrafanaAntonPutraInstall(){
    sudo apt-get install -y apt-transport-https software-properties-common
    wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
    echo "deb https://packages.grafana.com/oss/deb stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list
   sudo apt-get update
   sudo apt-get -y install grafana
}

function GrafanaSourceforgeInstall() {
    # недоделано
    sudo apt install make
    sudo snap install go --classic

    wget "https://master.dl.sourceforge.net/project/grafana.mirror/v9.3.1/9.3.1%20%282022-11-30%29.tar.gz"
    sudo tar -zxvf "9.3.1 (2022-11-30).tar.gz" # grafana-grafana-6329667
    cd "$(dirname "$0")/grafana-grafana-6329667"
    make

}

function GrafanaInstall() {

    wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -

    echo "deb https://packages.grafana.com/oss/deb stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list

    sudo apt-get update
    sudo apt-get -y install grafana

    sudo /bin/systemctl daemon-reload
    sudo /bin/systemctl enable grafana-server
    sudo systemctl start grafana-server

}