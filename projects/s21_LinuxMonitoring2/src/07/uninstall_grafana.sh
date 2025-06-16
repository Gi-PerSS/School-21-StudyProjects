#!/usr/bin/env bash

sudo snap remove grafana
sudo apt-get purge grafana
sudo apt-get remove grafana
sudo apt-get remove --auto-remove grafana
sudo rm -rf /etc/grafana/
