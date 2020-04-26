import scats as sc

try:
     s = sc.api()
     s.read_input("Файлы/input")
     print(s.input.N)
     help(sc)
except:
     pass