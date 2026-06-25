# Лабораторная работа №1

## Часть 1: UNIX
- Созданы папки /usr/local/folder_max и /usr/local/folder_min
- Созданы группы group_max и group_min
- Созданы пользователи user_max_1 и user_min_1
- Настроены права: folder_max (770) для group_max, folder_min (777) для всех
- user_max_1 успешно пишет в обе папки
- user_min_1 не имеет доступа к folder_max (Permission denied)

## Часть 2: Docker
- Собран образ my_unix_lab с nano
- Скрипт внутри контейнера отрабатывает корректно
- Список пользователей: только стандартные (root, nobody, ubuntu)

## Часть 3: Git
- Создан репозиторий, ветки dev/stg/prd
- Написан скрипт promote.sh для переноса dev → stg
