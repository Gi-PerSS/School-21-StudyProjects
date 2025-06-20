# Linux Monitoring v1.0

Набор Bash-скриптов для мониторинга системы и файловой системы на Ubuntu Server 20.04 LTS.

## Возможности
- **Скрипт 1**: Принимает текстовый параметр, выводит его, выдает ошибку, если параметр — число.
- **Скрипт 2**: Выводит информацию о системе (имя хоста, часовой пояс, пользователь, ОС, дата, время работы, IP, память, диск) с опцией сохранения в файл с временной меткой.
- **Скрипт 3**: Дополняет Скрипт 2 цветным выводом (4 параметра для цвета фона/шрифта, 1-6: белый, красный, зеленый, синий, фиолетовый, черный).
- **Скрипт 4**: Расширяет Скрипт 3, читает цвета из конфиг-файла, использует значения по умолчанию, если не указаны, показывает цветовую схему.
- **Скрипт 5**: Анализирует директорию (путь как параметр), выводит количество папок/файлов, топ-5 папок по размеру, топ-10 файлов по размеру, топ-10 исполняемых файлов с MD5-хешами, время выполнения.

## Технические детали
- Скрипты в папках `src/0x`, главный скрипт — `main.sh`.
- Разбиты на несколько файлов, с проверкой ввода.
- Запускаются на виртуальной машине Ubuntu Server 20.04 LTS.
- Проверка цветов предотвращает совпадение фона и шрифта.

[English version of README](README.md)