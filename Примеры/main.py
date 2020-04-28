import scats as sc # Подключение модуля

# Создание экземпляра интерфейса
s = sc.api()

# Считывание входных данных из файла
s.read_input("Файлы/input")

print(s.input.N)