from heapq import *
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
def val(f, L):
	score = 0
	cost = 0
	bins = set()
	for s in ftos[f]:
		b = stob[s]
		if b not in bins:
			bins |= {b}
			### TRY SUM
			cost = sum([cost, D[f] + len(btos[b]) + btog[b]])
	### TRY SOMETHING ELSE 
	score = U[f]*(L-cost)
	return score

def get_max_val(F_set, L):
	res, v = None, -float("inf")
	for f in F_set:
		vf = val(f, L)
		if vf>v:
			v = vf
			res = f
	return res

events = []
for g in range(G):
	heappush(events, (0, g, None))

btog = [0]*B
F_set = set(range(F))
cur_t = 0
while len(F_set) != 0:
	f = get_max_val(F_set, L-cur_t)
	bins = set()
	for s in ftos[f]:
		b = stob[s]
		if b not in bins:
			bins |= {b}
			t, g, rb = heappop(events)
			cur_t = t
			if rb is not None:
				btog[rb] -= 1
			nt = t + D[f] + len(btos[b]) + btog[b]
			heappush(events, (nt, g, b))
			btog[b] += 1
			res[g] += ["impl {} {}".format(itof[f], b)]
	F_set -= {f}

res = [r for r in res if r!=[]]
print(len(res))
for r in res:
	print(min(L, len(r)))
	print("\n".join(r[:L]))