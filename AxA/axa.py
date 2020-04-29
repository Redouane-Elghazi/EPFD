import json
from random import randint,seed
seed(4568181913454)
testcase = 6
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
res = dict()
for w in W:
	res[w] = (min(range(len(W[w][M])), key=lambda m:sum(td[t]*(td[t]) if t in td else 0 for t in W[w][M][m])), min(range(len(W[w][E])), key=lambda e:sum(td[t]*(td[t]) if t in td else 0 for t in W[w][E][e])))
	m,e = res[w]
	for t in W[w][M][m]:
		if t not in td:
			td[t] = 0
		td[t] += 1
	for t in W[w][E][e]:
		if t not in td:
			td[t] = 0
		td[t] += 1
#res = {w:(min(range(len(W[w][M])), key=lambda m:sum(td[t]*(td[t]-1) for t in W[w][M][m])), min(range(len(W[w][E])), key=lambda e:sum(td[t]*(td[t]-1) for t in W[w][E][e]))) for w in W}

T = dict()
Q = dict()
for w in res:
	if W[w][D] not in Q:
		Q[W[w][D]] = 0
	Q[W[w][D]] += 1
	for t in W[w][M][res[w][0]]:
		if t not in T:
			T[t] = 0
		T[t] += 1
	for t in W[w][E][res[w][1]]:
		if t not in T:
			T[t] = 0
		T[t] += 1
	
while True:
	print(len(res), end='\r')
	rid = []
	for w in res:
		if Q[W[w][D]]>quotas[W[w][D]]:
			S = 0
			for t in W[w][M][res[w][0]]:
				S += T[t]
			for t in W[w][E][res[w][1]]:
				S += T[t]
			rid += [(S, w)]
	if rid == []:
		break
	S, w = max(rid)
	Q[W[w][D]] -= 1
	for t in W[w][M][res[w][0]]:
		T[t] -= 1
	for t in W[w][E][res[w][1]]:
		T[t] -= 1
	del res[w]
	
print("")
print(sum(T[i]*(T[i]-1) for i in T))
OUT = [{"name":	w, "morningOptionIndex": res[w][0], "eveningOptionIndex": res[w][1]} for w in res]
with open(outfn, 'w') as f:
	json.dump(OUT, f)