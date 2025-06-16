#!/usr/bin/env bash

NodeExporterInstall() {

    export VERSION="1.4.0"

    sudo wget https://github.com/prometheus/node_exporter/releases/download/v1.4.0/node_exporter-1.4.0.linux-amd64.tar.gz

    tar -xvf node_exporter-1.4.0.linux-amd64.tar.gz
    rm node_exporter-1.4.0.linux-amd64.tar.gz
    sudo mv "$(dirname "$0")/node_exporter-1.4.0.linux-amd64/node_exporter" /usr/local/bin
    chown -R prometheus:prometheus /usr/local/bin/node_exporter

    sudo tee /etc/systemd/system/node_exporter.service <<EOF
    [Unit]
Description=Prometheus Node Exporter
After=network.target

[Service]
Type=simple
Restart=always
User=prometheus
Group=prometheus
ExecStart=/usr/local/bin/node_exporter

[Install]
WantedBy=multi-user.target
EOF

    sudo systemctl daemon-reload
    sudo systemctl start node_exporter
    sudo systemctl enable node_exporter
    sudo systemctl status node_exporter
}
