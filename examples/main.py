# -*- coding: utf-8 -*-

try:
     import scats as sc # Подключение модуля

     # Создание экземпляра интерфейса
     s = sc.api()

     # Считывание входных данных из файла
     s.read_input("files/input")

except:
     pass