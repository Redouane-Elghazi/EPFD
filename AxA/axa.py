import json
from random import randint,seed,shuffle
seed(4948948561615)
testcase = 2
M = "morningOptions"
E = "eveningOptions"
D = "domain"
infn = "ctstfr0244_input_" + str(testcase) + ".json"
outfn = "case" + str(testcase) + ".json"

with open(infn, "r") as f:
	IN = json.load(f)
W = IN["workers"]
quotas = IN["quotas"]
td = dict()
P = {w: [None, None] for w in W}
workers = [(w,E) for w in list(W.keys())] + [(w,M) for w in list(W.keys())]
workers.sort(key=lambda x:len(W[x[0]][x[1]]))
for w, d in workers:
	if d == M:
		P[w][0] = min(range(len(W[w][M])), key=lambda m:sum(td[t]*(td[t]+1) for t in W[w][M][m] if t in td))
		m = P[w][0]
		for t in W[w][M][m]:
			if t not in td:
				td[t] = 0
			td[t] += 1
	else:
		P[w][1] = min(range(len(W[w][E])), key=lambda e:sum(td[t]*(td[t]+1) for t in W[w][E][e] if t in td))
		e = P[w][1]
		for t in W[w][E][e]:
			if t not in td:
				td[t] = 0
			td[t] += 1
#res = {w:(min(range(len(W[w][M])), key=lambda m:sum(td[t]*(td[t]-1) for t in W[w][M][m])), min(range(len(W[w][E])), key=lambda e:sum(td[t]*(td[t]-1) for t in W[w][E][e]))) for w in W}

T = dict()
Q = dict()
for w in P:
	if W[w][D] not in Q:
		Q[W[w][D]] = 0
	for t in W[w][M][P[w][0]]:
		if t not in T:
			T[t] = 0
	for t in W[w][E][P[w][1]]:
		if t not in T:
			T[t] = 0
	
res = dict()
while True:
	print(len(res),"/",sum(quotas[q] for q in quotas), end='\r')
	need = []
	for w in W:
		if w not in res:
			if Q[W[w][D]]<quotas[W[w][D]]:
				S = 0
				for t in W[w][M][P[w][0]]:
					S += T[t]*(T[t]+1)
				for t in W[w][E][P[w][1]]:
					S += T[t]*(T[t]+1)
				need += [(S, w)]
	if need == []:
		break
	S, w = min(need)
	Q[W[w][D]] += 1
	for t in W[w][M][P[w][0]]:
		T[t] += 1
	for t in W[w][E][P[w][1]]:
		T[t] += 1
	res[w] = P[w]
td = dict()
P = {w: [None, None] for w in W}
workers = [(w,E) for w in list(res.keys())] + [(w,M) for w in list(res.keys())]
workers.sort(key=lambda x:len(W[x[0]][x[1]]))
for w, d in workers:
	if d == M:
		P[w][0] = min(range(len(W[w][M])), key=lambda m:sum(td[t] for t in W[w][M][m] if t in td))
		m = P[w][0]
		for t in W[w][M][m]:
			if t not in td:
				td[t] = 0
			td[t] += 1
	else:
		P[w][1] = min(range(len(W[w][E])), key=lambda e:sum(td[t] for t in W[w][E][e] if t in td))
		e = P[w][1]
		for t in W[w][E][e]:
			if t not in td:
				td[t] = 0
			td[t] += 1
T=dict()
for w in res:
	for t in W[w][M][P[w][0]]:
		if t not in T:
			T[t] = 0
		T[t] += 1
	for t in W[w][E][P[w][1]]:
		if t not in T:
			T[t] = 0
		T[t] += 1
print("")
print(sum(T[i]*(T[i]-1) for i in T))
OUT = [{"name":	w, "morningOptionIndex": P[w][0], "eveningOptionIndex": P[w][1]} for w in res]
with open(outfn, 'w') as f:
	json.dump(OUT, f)
