from random import *

n = 400
print(n)
t = [[0 for i in range(n)] for j in range(n)]
for i in range(n):
	for j in range(i):
		t[i][j] = randint(0,100000)
		t[j][i] = t[i][j]
for i in range(n):
	print(" ".join(map(str, t[i])))