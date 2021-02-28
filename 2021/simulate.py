from random import randint, seed, shuffle
from math import gcd
from functools import reduce
import sys

seed(0)

def find_gcd(list):
    x = reduce(gcd, list)
    return x

D, I, S, V, F = [int(x) for x in input().split()]
order = [[] for i in range(I)]
place = [dict() for i in range(I)]

ind = dict()
name = []
In, Out = [], []
W = []
for i in range(S):
	B, E, s, L = input().split()
	b, e = int(B), int(E)
	ind[s] = len(ind)
	name += [s]
	In += [b]
	Out += [e]
	order[e] += [ind[s]]
	W += [int(L)]

streets = dict()
P = []
tickets = [1]*V
rdy = [0]*V
av = [0]*V
cur = [0]*S
maxi = [-1]*S
lastpass = [-1]*S

def get_ticket(v, s):
	global maxi
	maxi[s] += 1
	tickets[v] = maxi[s]
	return maxi[s]

def trav(v, s):
	global cur, tickets, tme
	#print(v, "tries", s)
	if cur[s] == tickets[v] and lastpass[s] < tme and rdy[v] <= tme:
		e = Out[s]
		if s not in place[e]:
			#print(v, "reserves", s)
			T = tme%len(order[e])
			while order[e][T] != None:
				T = (T+1)%len(order[e])
			order[e][T] = s
			place[e][s] = T
		T = tme%len(order[e])
		#print("time is", T, "waiting", place[e][s])
		if order[e][T] == s:
			lastpass[s] = tme
			cur[s] += 1
			return True
		else:
			return False
	else:
		return False

def enter(v, s):
	global tme, rdy, W
	get_ticket(v, s)
	rdy[v] = tme + W[s]

tme = -100000000
for v in range(V):
	k, *ss = input().split()
	P += [[ind[s] for s in ss]]
	enter(v, P[-1][0])
	for s in P[-1]:
		if s not in streets:
			streets[s] = 0
		streets[s] += 1
		
for i in range(I):
	order[i] = [None for s in order[i] if s in streets]

Score = 0
for tme in range(D+1):
	for v in range(V):
		if av[v]<len(P[v]) and trav(v, P[v][av[v]]):
			av[v] += 1
			if av[v] == len(P[v]):
				Score += F + D-tme
			else:
				enter(v, P[v][av[v]])
				#print(v, av[v], len(P[v]))


print(sum([min(len(x), 1) for x in order]))
for s in range(S):
	if s in streets:
		e = Out[s]
		if s not in place[e]:
			T = tme%len(order[e])
			while order[e][T] != None:
				#print(T, file=sys.stderr)
				T = (T+1)%len(order[e])
			order[e][T] = s
			place[e][s] = T

for i in range(I):
	if order[i] != []:
		print(i)
		print(len(order[i]))
		for s in order[i]:
			print(name[s], 1)

print(Score, file=sys.stderr)