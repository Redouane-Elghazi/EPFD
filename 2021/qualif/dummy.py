from random import randint, seed, shuffle
from math import gcd
from functools import reduce

seed(0)

def find_gcd(list):
    x = reduce(gcd, list)
    return x

D, I, S, V, F = [int(x) for x in input().split()]
l = [[] for i in range(I)]

for i in range(S):
	B, E, s, L = input().split()
	e = int(E)
	l[e] += [s]

streets = dict()
for v in range(V):
	k, *ss = input().split()
	for s in ss:
		if s not in streets:
			streets[s] = 0
		streets[s] += 1

for i in range(I):
	l[i] = [s for s in l[i] if s in streets]

print(sum([min(len(x), 1) for x in l]))
for i in range(I):
	if l[i] != []:
		print(i)
		print(len(l[i]))
		l[i].sort(key=lambda s:-streets[s])
		g = find_gcd([streets[s] for s in l[i]])
		m = min([streets[s] for s in l[i]])
		for s in l[i]:
			print(s, max(streets[s]//(22*g), 1))
