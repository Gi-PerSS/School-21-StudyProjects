#!/usr/bin/env bash

clear
# sudo grafana-server -homepath /usr/share/grafana
sudo /bin/systemctl daemon-reload
sudo /bin/systemctl enable grafana-server
sudo systemctl start grafana-server
sudo systemctl status grafana-server

# sudo systemctl restart grafana-server
# sudo systemctl status grafana-server

# sudo service grafana-server restart
# sudo systemctl status grafana-server
