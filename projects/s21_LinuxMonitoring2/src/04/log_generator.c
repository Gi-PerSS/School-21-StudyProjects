#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* В комментариях в вашем скрипте/программе указать, что означает каждый из
   использованных кодов ответа.

Response codes (200, 201, 400, 401, 403, 404, 500, 501, 502, 503)
- 200 OK — успешный запрос. Если клиентом были запрошены какие-либо данные, то
они находятся в заголовке и/или теле сообщения. Появился в HTTP/1.0.

- 201 Created — в результате успешного выполнения запроса был создан новый
ресурс. Сервер может указать адреса (их может быть несколько) созданного ресурса
в теле ответа, при этом предпочтительный адрес указывается в заголовке Location.
Серверу рекомендуется указывать в теле ответа характеристики созданного ресурса
и его адреса, формат тела ответа определяется заголовком Content-Type. При
обработке запроса новый ресурс должен быть создан до отправки ответа клиенту,
иначе следует использовать ответ с кодом 202. Появился в HTTP/1.0.

- 400 Bad Request — сервер обнаружил в запросе клиента синтаксическую ошибку.
Появился в HTTP/1.0.

- 401 Unauthorized — для доступа к запрашиваемому ресурсу требуется
аутентификация. В заголовке ответ должен содержать поле WWW-Authenticate с
перечнем условий аутентификации. Иными словами, для доступа к запрашиваемому
ресурсу клиент должен представиться, послав запрос, включив при этом в заголовок
сообщения поле Authorization с требуемыми для аутентификации данными. Если
запрос уже включает данные для авторизации, ответ 401 означает, что в
авторизации с ними отказано.

- 403 Forbidden[19] — сервер понял запрос, но он отказывается его выполнять
из-за ограничений в доступе для клиента к указанному ресурсу. Иными словами,
клиент не уполномочен совершать операции с запрошенным ресурсом. Если для
доступа к ресурсу требуется аутентификация средствами HTTP, то сервер вернёт
ответ

- 404 Not Found[20] — самая распространённая ошибка при пользовании Интернетом,
основная причина — ошибка в написании адреса Web-страницы. Сервер понял запрос,
но не нашёл соответствующего ресурса по указанному URL. Если серверу известно,
что по этому адресу был документ, то ему желательно использовать код 410. Ответ
404 может использоваться вместо 403, если требуется тщательно скрыть от
посторонних глаз определённые ресурсы. Появился в HTTP/1.0.

- 500 Internal Server Error[23] — любая внутренняя ошибка сервера, которая не
входит в рамки остальных ошибок класса. Появился в HTTP/1.0.

- 501 Not Implemented — сервер не поддерживает возможностей, необходимых для
обработки запроса. Типичный ответ для случаев, когда сервер не понимает
указанный в запросе метод. Если же метод серверу известен, но он не применим к
данному ресурсу, то нужно вернуть ответ 405. Появился в HTTP/1.0.

- 502 Bad Gateway — сервер, выступая в роли шлюза или прокси-сервера, получил
недействительное ответное сообщение от вышестоящего сервера. Появился в
HTTP/1.0.

- 503 Service Unavailable — сервер временно не имеет возможности обрабатывать
запросы по техническим причинам (обслуживание, перегрузка и прочее). В поле
Retry-After заголовка сервер может указать время, через которое клиенту
рекомендуется повторить запрос. Хотя во время перегрузки очевидным кажется сразу
разрывать соединение, эффективней может оказаться установка большого значения
поля Retry-After для уменьшения частоты избыточных запросов. Появился в
HTTP/1.0.

 Отсюда:
   https://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BA%D0%BE%D0%B4%D0%BE%D0%B2_%D1%81%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D1%8F_HTTP#%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5_%D0%BA%D0%BE%D0%B4%D0%BE%D0%B2


*/

void AgentsGenerator(char* agent) {
  /*Agent request URL Agents (Mozilla, Google Chrome, Opera, Safari,
Internet Explorer, Microsoft Edge, Crawler and bot, Library and net tool)*/

  char agents[8][111] = {
      "Mozilla",         "Google Chrome",       "Opera",
      "Safari",          "Internet Explorer",   "Microsoft Edge",
      "Crawler and bot", "Library and net tool"};

  int actual = rand() % 8;
  strcpy(agent, agents[actual]);
}

void MethodsGenerator(char* method) {
  // methods (GET, POST, PUT, PATCH, DELETE)
  char methods[5][7] = {"GET", "POST", "PUT", "PATCH", "DELETE"};
  int actual = rand() % 5;
  strcpy(method, methods[actual]);
}

int ResponseCodeGenerator(void) {
  // Response codes (200, 201, 400, 401, 403, 404, 500, 501, 502, 503)
  int codes[10] = {200, 201, 400, 401, 403, 404, 500, 501, 502, 503};
  int actual_code = rand() % 10;
  return codes[actual_code];
}

void IpRandomGenerator(char* ip_string) {
  //  the full IP addressing range goes from 0.0.0.0 to 255.255.255.255.
  // IP (any correct one, i.e.no ip such as 999.111.777.777)
  int ip[4] = {0};
  for (int i = 0; i <= 3; i++) {
    ip[i] = rand() % 256;
  }
  sprintf(ip_string, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}

int HowManyEntryForDay(void) {
  // A random number between 100 and 1000 entries should be generated per day.
  int r = 100 + rand() % (1000 - 100 + 1);
  return r;
}

void TimeStampGenerator(time_t epochtime_day_begin, char* timestamp) {
  const time_t seconds_in_day = 86400;

  // получаем случайную секунду в диапазоне дня
  time_t epoch_time = epochtime_day_begin +
                      rand() % (epochtime_day_begin -
                                (epochtime_day_begin + seconds_in_day) + 1);

  char time_zones[34][6] = {
      "-1200", "-1100", "-1000", "-0900", "-0800", "-0700", "-0600",
      "-0500", "-0430", "-0400", "-0330", "-0300", "-0200", "-0100",
      "+0000", "+0100", "+0200", "+0300", "+0330", "+0400", "+0430",
      "+0500", "+0530", "+0545", "+0600", "+0630", "+0700", "+0800",
      "+0900", "+0930", "+1000", "+1100", "+1200", "+1300"};

  /* CONVERT TO struct tm */
  struct tm* converted_time;
  converted_time = localtime(&epoch_time);

  /* DISPLAY TIME */
  // must be in format: [06/Nov/2014:19:12:14 +0600]

  char timestamp_wo_tz[33];
  strftime(timestamp_wo_tz, 33, "%d/%b/%Y:%H:%M:%S", converted_time);

  char tz[6] = "";
  int random_tz = rand() % 34;
  strcpy(tz, time_zones[random_tz]);
  sprintf(timestamp, "[%s %s]", timestamp_wo_tz, tz);
  //  printf("DBG. Timestamp is %s\n", timestamp);
}

time_t RandomDayBeginInEpochTime(void) {
  time_t r = 0;
  time_t epoch_time_now = time(NULL);

  /*
   Получение случайного дня в году и перевод этого значения в unix epoch time.
   Диапазон лет: 2005 - 2021.

  "В общем случае если нам нужно получить числа из отрезка [A;B], то необходимо
    воспользоваться следующей конструкцией: A + rand()%(B-A+1).""
  */

  int year, month, day;
  year = 2005 + rand() % (2021 - 2005 + 1);
  month = rand() % (12 + 1);
  day = rand() % 29;

  struct tm start = {
      .tm_year = year - 1900, .tm_mday = day, .tm_mon = month - 1};
  r = mktime(&start);
  return r;
}

void HttpRequestGenerator(char* url_holder) {
  char vocabulary[35][22] = {
      "asctime",     "returns",  "a",          "pointer",  "to",
      "static",      "data",     "and",        "is",       "not",
      "thread-safe", "POSIX",    "marks",      "this",     "function",
      "obsolete",    "and",      "recommends", "strftime", "instead",
      "the",         "C",        "standard",   "also",     "recommends",
      "strftime",    "instead",  "asctime",    "and",      "asctime_s",
      "because",     "strftime", "more",       "flexible", "locale-sensitive"};

  char output[111] = "";

  MethodsGenerator(output);
  strcat(output, " ");
  for (int i = 0; i != 3; i++) {
    int random = rand() % 35;
    strcat(output, "/");
    strcat(output, vocabulary[random]);
  }
  strcat(output, ".html HTTP/1.1");
  strcpy(url_holder, output);
}

void LogGenerator(void) {
  /* Алгоритм
  - в цикле, считающем дни, формируем структуру tm, куда помещаем случайно
  сгенерированную дату  в диапазое от 2005 до 2021 года.
  - в цикле, считающем дневные посещения, переводим эту дату в epoch time и
  генерируем случайные числа, лежащее в диапазоне длины дня, через константу,
  определяющую число секунд в дне.
  - для каждого сгенерированного числа формируем свою временную метку, которую
  заносим в файл.
  */

  int number_logs_files = 5;
  // Write a bash script or a C program that generates 5 nginx log files.
  for (int i = number_logs_files; i > 0; i--) {
    // Создаем файл и открываем его для записи
    char filename[22] = "";
    sprintf(filename, "nginx_logfile_%d.log", i);
    FILE* log_file = fopen(filename, "a");

    // получаем начало дня для текущего лог-файла
    time_t epochtime_day_begin = RandomDayBeginInEpochTime();

    // 100 and 1000 entries should be generated per day.
    int number_of_entries = HowManyEntryForDay();
    for (int i = 0; i < number_of_entries; i++) {
      // Формируем записи лога и пишем их в файл.

      // Empty fields
      char RFC_1413_identity[2] = "-";
      char username[2] = "-";
      char URL_came_from[2] = "-";
      // ip
      char ip[22] = "";
      IpRandomGenerator(ip);

      // datestamp
      char timestamp[111] = "";
      TimeStampGenerator(epochtime_day_begin, timestamp);
      // HTTP request
      char url[111] = "";
      HttpRequestGenerator(url);
      // Response code
      int response_code = ResponseCodeGenerator();
      // Number of bytes transferred in requested object
      int bytes_transferred = (rand() % 5555) + 11;

      // agents
      char agent[111] = "";
      AgentsGenerator(agent);

      /*Пример:
      66.249.65.3 - - [06/Nov/2014:19:11:24 +0600]
      "GET /?q=%E0%A6%AB%E0%A6%BE%E0%A7%9F%E0%A6%BE%E0%A6%B0 HTTP/1.1" 200 4223
      "-" "Mozilla/5.0 (compatible; Googlebot/2.1;
      +http://www.google.com/bot.html)"


      контроль:
      79.113.128.0 - - [07/Apr/2056:11:58:32 -0330] "PUT
      /strftime/because/data.html HTTP/1.1" 502 5551 - Safari
      */

      fprintf(log_file, "%s %s %s %s \"%s\" %d %d %s %s\n", ip,
              RFC_1413_identity, username, timestamp, url, response_code,
              bytes_transferred, URL_came_from, agent);
    }

    fclose(log_file);
  }
}

int main() { LogGenerator(); }

/*
== Task ==
Write a bash script or a C program that generates 5 nginx log files in combined
format.

Each log should contain information for 1 day.

A random number between
100 and 1000 entries should be generated per day. For each entry there should be
randomly generated the following:

IP (any correct one, i.e. no ip such as 999.111.777.777)
Response codes (200, 201, 400, 401, 403, 404, 500, 501, 502, 503)

methods (GET, POST, PUT, PATCH, DELETE)

Dates (within a specified log day, should be in ascending order, т.е. от ранних
к позднейшим)

Agent request URL

Agents (Mozilla, Google Chrome, Opera, Safari,
Internet Explorer, Microsoft Edge, Crawler and bot, Library and net tool)

Specify in the comments of your script/program what each of the response codes
used means.
================

The format is defined by this expression:
"%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-agent}i\""

This consists of the following space-separated fields:

- Hostname or IP address of accesser of site.
- RFC 1413 identity of client. This is noted as unreliable, and is usually blank
(represented by a hyphen (-) in the file).
- Username of user accessing document. Will be a hyphen for public web-sites
that have no user access controls.
- Timestamp string surrounded by square brackets, e.g. [12/Dec/2012:12:12:12
-0500].
- HTTP request surrounded by double quotes, e.g., "GET /stuff.html HTTP/1.1".
- HTTP status code.
- Number of bytes transferred in requested object.
- URL where user came from to get to your site (surrounded by double quotes).
- User agent string sent by client (surrounded by double quotes). Can be used to
identify what browser was used.

=============
Examples:

66.249.65.159 - - [06/Nov/2014:19:10:38 +0600] "GET
/news/53f8d72920ba2744fe873ebc.html HTTP/1.1" 404 177 "-" "Mozilla/5.0 (iPhone;
CPU iPhone OS 6_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko)
Version/6.0 Mobile/10A5376e Safari/8536.25 (compatible; Googlebot/2.1;
+http://www.google.com/bot.html)"

66.249.65.3 - - [06/Nov/2014:19:11:24 +0600]
"GET /?q=%E0%A6%AB%E0%A6%BE%E0%A7%9F%E0%A6%BE%E0%A6%B0 HTTP/1.1" 200 4223 "-"
"Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)"

66.249.65.62 - - [06/Nov/2014:19:12:14 +0600] "GET
/?q=%E0%A6%A6%E0%A7%8B%E0%A7%9F%E0%A6%BE HTTP/1.1" 200 4356 "-" "Mozilla/5.0
(compatible; Googlebot/2.1; +http://www.google.com/bot.html)"

For example, the timestamp
     Sun, 31 Mar 1996 15:53:10 +0200
indicates that the creator's local time is 15:53:10, that the creator's time
zone is +0200 (two hours east of UTC)


*/