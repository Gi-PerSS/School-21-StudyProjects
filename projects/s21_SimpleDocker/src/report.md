## Part 1. Готовый докер

+ Взять официальный докер образ с nginx и выкачать его при помощи docker pull

![Part 1](Screenshots.p1/1.png)

+ Проверить наличие докер образа через docker images

![Part 1](Screenshots.p1/2.png)

+ Запустить докер образ через docker run -d [image_id|repository]

![Part 1](Screenshots.p1/3.png)

+ Проверить, что образ запустился через docker ps

![Part 1](Screenshots.p1/4.png)

+ Посмотреть информацию о контейнере через docker inspect [container_id|container_name]

![Part 1](Screenshots.p1/5.png)

+ По выводу команды определить и поместить в отчёт 
  + размер контейнера,
![Part 1](Screenshots.p1/6.png)
  +  список замапленных портов и 
![Part 1](Screenshots.p1/7.png)
  + ip контейнера
![Part 1](Screenshots.p1/8.png)

+ Остановить докер образ через docker stop [container_id|container_name]

![Part 1](Screenshots.p1/9.png)

+ Проверить, что образ остановился через docker ps

![Part 1](Screenshots.p1/10.png)

+ Запустить докер с замапленными портами 80 и 443 на локальную машину через команду run

![Part 1](Screenshots.p1/11.png)

+ Проверить, что в браузере по адресу localhost:80 доступна стартовая страница nginx

![Part 1](Screenshots.p1/12.png)

+ Перезапустить докер контейнер через docker restart [container_id|container_name]. 
+ Проверить любым способом, что контейнер запустился

![Part 1](Screenshots.p1/13.png)

## Part 2. Операции с контейнером

+ Прочитать конфигурационный файл nginx.conf внутри докер контейнера через команду exec

![Part 2](Screenshots.p2/1.png)

+ Создать на локальной машине файл nginx.conf

![Part 2](Screenshots.p2/2.png)
(Сложный способ копирования через root, по причине ошибки копирования обычным образом - snap-установка docker-а)

+ Настроить в нем по пути /status отдачу страницы статуса сервера nginx

![Part 2](Screenshots.p2/3.png)

+ Скопировать созданный файл nginx.conf внутрь докер образа через команду docker cp

![Part 2](Screenshots.p2/4.png)

+ Перезапустить nginx внутри докер образа через команду exec

![Part 2](Screenshots.p2/5.png)

+ Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx

![Part 2](Screenshots.p2/6.png)

+ Экспортировать контейнер в файл container.tar через команду export

![Part 2](Screenshots.p2/7.png)

+ Остановить контейнер

![Part 2](Screenshots.p2/8.png)

+ Удалить образ через docker rmi [image_id|repository], не удаляя перед этим контейнеры

![Part 2](Screenshots.p2/9.png)

+ Удалить остановленный контейнер

![Part 2](Screenshots.p2/10.png)

+ Импортировать контейнер обратно через команду import

![Part 2](Screenshots.p2/11.png)

+ Запустить импортированный контейнер

![Part 2](Screenshots.p2/12.png)

+ Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx

![Part 2](Screenshots.p2/15.png)

## Part 3. Мини веб-сервер

+ Написать мини сервер на C и FastCgi, который будет возвращать простейшую страничку с надписью Hello World!

![Part 3](Screenshots.p3/1.png)

+ Запустить написанный мини сервер через spawn-fcgi на порту 8080

![Part 3](Screenshots.p3/2.png)

+ Написать свой nginx.conf, который будет проксировать все запросы с 81 порта на 127.0.0.1:8080

![Part 3](Screenshots.p3/3.png)

+ Проверить, что в браузере по localhost:81 отдается написанная вами страничка

![Part 3](Screenshots.p3/4.png)

+ Положить файл nginx.conf по пути ./nginx/nginx.conf (это понадобится позже)

![Part 3](Screenshots.p3/5.png)

## Part 4. Свой докер

+ Написать свой докер образ, который:

1) собирает исходники мини сервера на FastCgi из Части 3
2) запускает его на 8080 порту
3) копирует внутрь образа написанный ./nginx/nginx.conf
4) запускает nginx.

![Part 4](Screenshots.p4/1.png)

+ Собрать написанный докер образ через docker build при этом указав имя и тег

![Part 4](Screenshots.p4/2.png)

+ Проверить через docker images, что все собралось корректно

![Part 4](Screenshots.p4/3.png)

+ Запустить собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а (см. Часть 2)

![Part 4](Screenshots.p4/4.png)

+ Проверить, что по localhost:80 доступна страничка написанного мини сервера

![Part 4](Screenshots.p4/5.png)

+ Дописать в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx

![Part 4](Screenshots.p4/6.png)

+ Перезапустить докер образ
+ Проверить, что теперь по localhost:80/status отдается страничка со статусом nginx

![Part 4](Screenshots.p4/7.png)

## Part 5. Dockle

+ Просканировать образ из предыдущего задания через dockle [image_id|repository]

![Part 4](Screenshots.p5/1.png)

+ Исправить образ так, чтобы при проверке через dockle не было ошибок и предупреждений

![Part 4](Screenshots.p5/2.png)

## Part 6. Базовый Docker Compose

+ Написать файл docker-compose.yml, с помощью которого:

1) Поднять докер контейнер из Части 5 (он должен работать в локальной сети, т.е. не нужно использовать инструкцию EXPOSE и мапить порты на локальную машину)
2) Поднять докер контейнер с nginx, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера
+ Замапить 8080 порт второго контейнера на 80 порт локальной машины

![Part 6](Screenshots.p6/1.png)

+ Остановить все запущенные контейнеры

![Part 6](Screenshots.p6/2.png)

+ Собрать и запустить проект с помощью команд docker-compose build и docker-compose up

![Part 6](Screenshots.p6/2.1.png)
![Part 6](Screenshots.p6/3.png)

+ Проверить, что в браузере по localhost:80 отдается написанная вами страничка, как и ранее

![Part 6](Screenshots.p6/4.png)