#!/bin/bash

# Вывод названия скрипта
printf "\nЗапущен скрипт для проверки модуля.\n"

# Определение начального числа ошибок
ERROR_COUNT=0

# Определение функции для проверки команд
function check_if_succeeded {

    # Вывод информации о запущенной программе
    printf "\nПроверяется команда $@.\n\n"

    # Выполнение указанной команды
    $@

    local status=$?

    if [ $status -ne 0 ]; then
        printf "\n[!] Ошибка при выполнении команды $1.\n"
        ERROR_COUNT=$((ERROR_COUNT+1))
    fi

    return $status

}

# Проверка на удачную установку с PyPI
printf "\nУстановка пакета с PyPI.\n"
check_if_succeeded "make install-pypi"

# Проверка пропуска примера
printf "\nПропуск примера.\n"
check_if_succeeded "make example"

# Проверка числа ошибок
if [ "$ERROR_COUNT" -gt 0 ]; then

     printf "\nЧисло ошибок: $ERROR_COUNT\n\n"
     exit 1

else

     printf "Всё в порядке.\n"

fi