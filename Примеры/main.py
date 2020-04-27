import scats as sc # Подключение модуля

try:
     # Создание экземпляра интерфейса
     s = sc.api()

     # Считывание входных данных из файла
     s.read_input("Файлы/input")

except:
     pass