import scats.scats as sc

try:
     s = sc.api()
     s.read_input("input")
     print(s.input.N)
except:
     pass