
FROM nginx:1.9.5

COPY ./server/fastCGI_materials.c /tmp/ 
COPY ./nginx/nginx.conf /etc/nginx/

RUN \
# Установка spawn-fcgi + gcc + библиотека под fcgi
apt-get update -y --force-yes \
&& apt install spawn-fcgi -y --force-yes --fix-missing \ 
&& apt install build-essential -y --force-yes --fix-missing \
&& apt install libfcgi-dev -y --force-yes --fix-missing \
&& apt install net-tools -y --force-yes  \
&& apt-get install -y --force-yes  procps \
&& rm -rf /var/lib/apt/lists/* \
    # компилируем
&& gcc /tmp/fastCGI_materials.c -lfcgi -o tmp/fastCGI_materials

EXPOSE 80

CMD spawn-fcgi -a 127.0.0.1 -p 8080 /tmp/fastCGI_materials -n & nginx -g 'daemon off;'