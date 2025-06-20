#!/usr/bin/env bash

function GrafanaDebInstall() {
    wget https://dl.grafana.com/oss/release/grafana_9.2.4_amd64.deb
    sudo dpkg -i grafana_9.2.4_amd64.deb

    sudo mkdir '/usr/share/grafana'
    sudo /bin/systemctl daemon-reload
    sudo /bin/systemctl enable grafana-server
    sudo systemctl start grafana-server
    rm grafana_9.2.4_amd64.deb
    sudo systemctl status grafana-server
}

function GrafanaSnapInstall() {
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
    sudo systemctl status grafana-server
}

function GrafanaUninstall()
{
    sudo snap remove grafana
    sudo apt-get purge grafana
    sudo apt-get remove grafana
    sudo apt-get remove --auto-remove grafana
    sudo rm -Rf /etc/grafana/
}

function GrafanaStart(){
    sudo /bin/systemctl daemon-reload
    sudo /bin/systemctl enable grafana-server
    sudo systemctl start grafana-server
    sudo systemctl status grafana-server
}