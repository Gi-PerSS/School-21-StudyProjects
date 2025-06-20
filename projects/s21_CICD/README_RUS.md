# Basic CI/CD

Простой CI/CD пайплайн для проекта *SimpleBashUtils*, включающий сборку, тестирование и развертывание утилит *s21_cat* и *s21_grep*.

## Возможности
- Настройка GitLab Runner на виртуальной машине Ubuntu Server 20.04 LTS.
- Этапы CI:
  - Сборка: Компиляция *SimpleBashUtils* через Makefile, сохранение артефактов на 30 дней.
  - Тест стиля: Запуск *clang-format*, завершение пайплайна при нарушении стиля, вывод результатов.
  - Интеграционные тесты: Автоматический запуск при успешной сборке и тесте стиля, завершение пайплайна при провале, вывод результатов.
- Этап CD:
  - Деплой: Ручной перенос артефактов в `/usr/local/bin` на вторую виртуальную машину Ubuntu через SSH/SCP, завершение пайплайна при ошибках.
- Дополнительно: Уведомления в Telegram через бота с информацией об успешности этапов CI/CD.

## Технические детали
- Настройка в файле `.gitlab-ci.yml`.
- Использование bash-скриптов для деплоя.
- Сохранение дампов образов виртуальных машин (не в Git).

[English version of README](README.md)