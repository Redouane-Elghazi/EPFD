from random import *
from time import time

seed(0)

timer = time()
n = int(input())
t = []
for i in range(n):
	t += [list(map(int, input().split()))]

def solve():
	succ = [-1]*n
	alive = {(u,u) for u in range(n)}
	pote = [u for u in range(n)]
	L = 0
	for _ in range(n-1):
		mini = (float('inf'),-1,-1)
		u,v = sample(alive, 1)[0]
		for w,x in alive:
			if u!=w:
				for i in u,v:
					for j in w,x:
						if mini>(t[i][j], min(i,j), max(i,j)):
							mini = (t[i][j], min(i,j), max(i,j))
		u, v = mini[1], mini[2]
		if succ[u] == -1:
			succ[u] = v
		else:
			succ[u] = (succ[u], v)
		if succ[v] == -1:
			succ[v] = u
		else:
			succ[v] = (succ[v], u)
		alive.remove((min(pote[u], u), max(pote[u], u)))
		alive.remove((min(pote[v], v), max(pote[v], v)))
		alive.add((min(pote[u],pote[v]),max(pote[u],pote[v])))
		u2 = pote[u]
		v2 = pote[v]
		pote[u2] = v2
		pote[v2] = u2
		L += t[u][v]
	for u,v in alive:
		succ[u] = (succ[u], v)
		succ[v] = (succ[v], u)
		L += t[u][v]
	res = ["1"]
	p = -1
	u = 0
	for _ in range(n):
		suiv = succ[u][0]
		if suiv == p:
			suiv = succ[u][1]
		res += [str(suiv+1)]
		p = u
		u = suiv
	return (L, res)
	
L = float('inf')
d = 0
while time()-timer+d < 0.95:
	d = time()
	Lt,rest = solve()
	d = time()-d
	if Lt < L:
		L,res = Lt,rest
print(L)
print(" ".join(res))