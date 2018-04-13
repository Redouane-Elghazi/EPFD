from random import shuffle
from time import time

timer = time()
n = int(input())
t = []
for i in range(n):
	t += [list(map(int, input().split()))]
L = 0
res = []
order = list(range(n))
shuffle(order)
for i in range(n):
	res += [str(order[i]+1)]
	L += t[order[i]][order[(i+1)%n]]
res += [str(order[0]+1)]
while time()-timer < 0.9:
	Lt = 0
	rest = []
	shuffle(order)
	for i in range(n):
		rest += [str(order[i]+1)]
		Lt += t[order[i]][order[(i+1)%n]]
	rest += [str(order[0]+1)]
	if Lt < L:
		L = Lt
		res = rest
print(L)
print(" ".join(res))