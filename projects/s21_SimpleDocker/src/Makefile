all: fastCGI_materials

fastCGI_materials: fastCGI_materials.c
	gcc fastCGI_materials.c -lfcgi -o fastCGI_materials

clean:
	sudo docker container prune -f
#	@rm -f FastCgi_server_habr
#	@rm -f fastCGI_materials
#	sudo docker rmi t4/nginx_fcgi:v2

t3: fastCGI_materials
	sudo cp ./nginx/nginx.conf /etc/nginx/
	sudo nginx -t
	sudo nginx -s reload
	open "http://127.0.0.1:81"
	sudo spawn-fcgi -a 127.0.0.1 -p 8080 fastCGI_materials -n

t4_clean:
	sudo docker stop t22
	sudo docker container prune -f # <== удалить все остановленные контейнеры
#	sudo docker rm t22
#	sudo docker rmi t4/nginx_fcgi:v1

t4:
#	sudo systemctl stop nginx 
	sudo docker build -t t4/nginx_fcgi:v1 .
	sudo docker run -dit -v `pwd`/nginx:/etc/nginx/ -p 80:81 --name t22 t4/nginx_fcgi:v1

t5:
	# export DOCKER_CONTENT_TRUST=1 && 
	sudo docker build -t t4/nginx_fcgi:v2 -f Dockerfile_part5 . && sudo docker images && sudo dockle -ak NGINX_GPGKEY t4/nginx_fcgi:v2
	sudo docker run -dit -v `pwd`/nginx:/etc/nginx/ -p 80:81 --name t22 t4/nginx_fcgi:v2

t6:
	clear
#	sudo docker stop $(sudo docker ps -a -q)
#	docker-compose up -d
	docker exec -ti src_proxy_p6_1 ping src_server_p5_1


push:
	git checkout develop
	git add .
	git commit -m "up"
	git push

