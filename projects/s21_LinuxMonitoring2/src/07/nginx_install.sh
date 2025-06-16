#!/usr/bin/env bash

# https://www.digitalocean.com/community/tutorials/how-to-install-nginx-on-ubuntu-20-04

function NginxInstall() {
    sudo apt update
    sudo apt install nginx
}

function NginxConfiguring(){
sudo cp "$(dirname "$0")/nginx_rigth_config_default" "/etc/nginx/sites-available/default"
sudo nginx -t
}

# Далее неудачные варианты настройки
function NginxConfiguring1() {
    sudo tee /etc/nginx/sites-available/default <<EOF
server {
	listen 81 default_server;
	listen [::]:81 default_server;

	root /var/www/html;
	index index.html index.htm index.nginx-debian.html;

	server_name _;

	location / {
		try_files $uri $uri/ =404;
	}

	location /nginx_status {
        	stub_status;
        	allow 127.0.0.1;
        	deny all;
        }
}
EOF
}

function NginxConfiguring2() {
    sudo mv /etc/nginx/sites-available/default /etc/nginx/sites-available/default.BU

    sudo tee /etc/nginx/sites-available/default<<EOF
    map $http_upgrade $connection_upgrade {
     default upgrade;
     '' close;
}

upstream websocket {
    server localhost:9090;
    server localhost:9100;
	server localhost:3000;
}

server {
	listen 80 default_server;
	listen [::]:80 default_server;

	root /var/www/html;

	index index.html index.htm index.nginx-debian.html;

	server_name _;

	location / {
	   proxy_set_header Host $http_host;
	   proxy_pass http://websocket;
#	   proxy_pass http://localhost:3000;
	}

        location /api/live {
           proxy_http_version 1.1;
           proxy_set_header Upgrade $http_upgrade;
           proxy_set_header Connection $connection_upgrade;
           proxy_set_header Host $http_host;
           proxy_pass http://localhost:3000;
	 }

}
EOF
sudo nginx -t

}

function NginxOwnDomainConfiguring() {
    # не удается зайти на созданный домен и прикрутить туда графану, соответственно.

    sudo ufw allow 'Nginx HTTP'

    sudo mkdir -p /var/www/filiusro/html
    sudo chown -R $USER:$USER /var/www/filiusro/html
    sudo chmod -R 755 /var/www/filiusro
    sudo touch /var/www/filiusro/html/index.html

    sudo tee /var/www/filiusro/html/index.html <<EOF
<html>
    <head>
        <title>Welcome to filiusro!</title>
    </head>
    <body>
        <h1>Success!  The filiusro server block is working!</h1>
    </body>
</html>
EOF

    sudo touch /etc/nginx/sites-available/filiusro
    sudo tee /etc/nginx/sites-available/filiusro <<EOF
server {
        listen 80;
        listen [::]:80;

        root /var/www/filiusro/html;
        index index.html index.htm index.nginx-debian.html;

        server_name filiusro www.filiusro;

        location / {
                try_files $uri $uri/ =404;
        }
}
EOF

    sudo ln -s /etc/nginx/sites-available/filiusro /etc/nginx/sites-enabled/
    sudo sed -i '/server_names_hash_bucket_size/s/#//g' /etc/nginx/nginx.conf

    sudo nginx -t
    sudo systemctl restart nginx

}
