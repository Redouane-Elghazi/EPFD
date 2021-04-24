from heapq import *
import random
import sys
L, G, S, B, F, N = [int(x) for x in input().split()]

stoi = dict()
itos = []
btos = [[] for _ in range(B)]
stob = []
for s in range(S):
	service, b = input().split()
	b = int(b)
	
	stob += [b]
	stoi[service] = s
	itos += [service]
	btos[b] += [s]

ftoi = dict()
itof = []
ftos = [[] for _ in range(F)]
D = []
U = []
for f in range(F):
	feature, M, d, u = input().split()
	M = int(M)
	d = int(d)
	u = int(u)
	servs = input().split()
	
	ftoi[feature] = f
	itof += [feature]
	for s in servs:
		ftos[f] += [stoi[s]]
	ftos[f].sort(key=lambda s:-len(btos[stob[s]]))
	D += [d]
	U += [u]

res = [[] for _ in range(G)]
events = []
cur_t = 0
for g in range(G):
	heappush(events, (0, g, None))

Bin = B
for i in range(Bin):
	res[i] += ["new"]
	B += 1
	btos += [[]]
for i in range(Bin, G):
	res[i] += ["wait {}".format(N)]

nt = [0]*G
for i in range(Bin):
	for k in range(len(btos[i])//2):
		if nt[i] + max(len(btos[i]), len(btos[i+Bin])) > int(sys.argv[1]):
			break
		nt[i] += max(len(btos[i]), len(btos[i+Bin]))
		s = random.choice(btos[i])
		btos[i].pop(btos[i].index(s))
		btos[i+Bin] += [s]
		stob[s] = i+Bin
		res[i] += ["move {} {}".format(itos[s], i+Bin)]
	cur_t = max(cur_t, nt[i])
for i in range(G):
	if cur_t-nt[i]>0:
		res[i] += ["wait {}".format(cur_t-nt[i])]

SF = []
for f in range(F):
	score = 0
	cost = 0
	bins = set()
	for s in ftos[f]:
		b = stob[s]
		if b not in bins:
			bins |= {b}
			### TRY SUM
			cost = sum([cost, len(btos[b])])
	cost += D[f]
	### TRY SOMETHING ELSE 
	score = U[f]/cost
	SF += [(score, f)]

SF.sort(reverse=True)

events = []
for g in range(G):
	heappush(events, (cur_t, g, None))

btog = [0]*B
for score, f in SF:
	bins = set()
	for s in ftos[f]:
		b = stob[s]
		if b not in bins:
			bins |= {b}
			t, g, rb = heappop(events)
			if rb is not None:
				btog[rb] -= 1
			nt = t + D[f] + len(btos[b]) + btog[b]
			heappush(events, (nt, g, b))
			btog[b] += 1
			res[g] += ["impl {} {}".format(itof[f], b)]

res = [r for r in res if r!=[]]
print(len(res))
for r in res:
	print(min(L, len(r)))
	print("\n".join(r[:L]))