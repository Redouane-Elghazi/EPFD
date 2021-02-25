from random import randint, seed, shuffle

seed(0)

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

print(sum([min(len(x), 1) for x in l]))
for i in range(I):
	if l[i] != []:
		print(i)
		print(len(l[i]))
		shuffle(l[i])
		for s in l[i]:
			print(s, randint(1,1))
