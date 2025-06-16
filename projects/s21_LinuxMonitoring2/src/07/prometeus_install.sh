#!/usr/bin/env bash

function prometheus_install() {
  # Step 1: Create Prometheus system group
  sudo groupadd --system prometheus
  sudo useradd -s /sbin/nologin --system -g prometheus prometheus

  # Step 2: Create data & configs directories for Prometheus
  sudo mkdir /var/lib/prometheus
  for i in rules rules.d files_sd; do sudo mkdir -p /etc/prometheus/${i}; done

  #Step 3: Download Prometheus on Ubuntu
  sudo apt update

  # решаем проблему долгой установки curl
  sudo mandb -t
  sudo rm -rf /var/cache/man
  sudo mandb -c

  sudo apt -y install wget curl vim
  mkdir -p /tmp/prometheus && cd /tmp/prometheus
  curl -s https://api.github.com/repos/prometheus/prometheus/releases/latest | grep browser_download_url | grep linux-amd64 | cut -d '"' -f 4 | wget -qi -

  tar xvf prometheus*.tar.gz
  cd prometheus*/

  sudo mv prometheus promtool /usr/local/bin/
  prometheus --version
  promtool --version

  sudo mv prometheus.yml /etc/prometheus/prometheus.yml
  sudo mv consoles/ console_libraries/ /etc/prometheus/

  # Step 4: Configure Prometheus on Ubuntu 22.04/20.04/18.04
  #   sudo vim /etc/prometheus/prometheus.yml - конфиг по образцу, проверить.
  sudo tee /etc/systemd/system/prometheus.service <<EOF
[Unit]
Description=Prometheus
Documentation=https://prometheus.io/docs/introduction/overview/
Wants=network-online.target
After=network-online.target

[Service]
Type=simple
User=prometheus
Group=prometheus
ExecReload=/bin/kill -HUP \$MAINPID
ExecStart=/usr/local/bin/prometheus \
  --config.file=/etc/prometheus/prometheus.yml \
  --storage.tsdb.path=/var/lib/prometheus \
  --web.console.templates=/etc/prometheus/consoles \
  --web.console.libraries=/etc/prometheus/console_libraries \
  --web.listen-address=0.0.0.0:9090 \
  --web.external-url=

SyslogIdentifier=prometheus
Restart=always

[Install]
WantedBy=multi-user.target
EOF

  for i in rules rules.d files_sd; do sudo chown -R prometheus:prometheus /etc/prometheus/${i}; done
  for i in rules rules.d files_sd; do sudo chmod -R 775 /etc/prometheus/${i}; done
  sudo chown -R prometheus:prometheus /var/lib/prometheus/

  sudo systemctl daemon-reload
  sudo systemctl start prometheus
  sudo systemctl enable prometheus

  systemctl status prometheus

  #     sudo ufw allow 9090/tcp - разрешение для файервола
  xdg-open 127.0.0.1:9090
}
