from IO_hashcode import read_input, print_output
from tools import find_contributors_yield, learning
import scoring
from random import shuffle
import sys
from GfGmatching import BpM

def attribold(p, i, res, used, o):
	if i == len(p2S[p]):
		return True
	j = o[i]
	for cont in find_contributors_yield(p2S[p], c2S, j, mentor=False, start=lastcont):
		print('\t'*i+str(cont)+'   ', end='\r', file=sys.stderr)
		if cont not in used:
			res[j] = cont
			used|={cont}
			if attrib(p, i+1, res, used, o):
				return True
			used-={cont}
	for cont in find_contributors_yield(p2S[p], c2S, j, mentor=True, start=lastcont):
		break
		print('\t'*i+str(cont)+'   ', end='\r', file=sys.stderr)
		if cont not in used:
			res[j] = cont
			used|={cont}
			if attrib(p, i+1, res, used, o):
				return True
			used-={cont}
	return False

def attrib(p, res):
	S = len(p2S[p])
	tab = [[1 if c2S[c].get(p2S[p][s][0], 0) >= p2S[p][s][1] else 0 for s in range(S)] for c in range(C)]
	g = BpM(tab)
	result = g.maxBPM()
	for s in range(S):
		if result[s] == -1:
			return False
		res[s] = result[s]
	return True

contributors, c2S, projects, p2D, p2W, p2B, p2S = read_input()

C = len(contributors)
P = len(projects)

bestS = dict()
for p in range(P):
	for p, v in p2S[p]:
		bestS[p] = 0
for c in range(C):
	for s in c2S[c]:
		if s in bestS:
			bestS[s] = max(c2S[c][s], bestS[s])

last = 0
cur = 0
done = [False] * P
done_projects = []
p2c = []
lastcont = 0
while True:
	print("{}/{} -- project {} ({} skills)           ".format(len(done_projects), P, cur, len(p2S[cur])), end='\r', file=sys.stderr)
	if not(done[cur]):
		res = [0 for i in range(len(p2S[cur]))]
		poss = True
		for s, v in p2S[cur]:
			if bestS[s]<v:
				poss = False
		nb = {s:len([c for c in range(C) if s in c2S[c] and c2S[c][s]>=v]) for s,v in p2S[cur]}
		o = [i for i in range(len(p2S[cur]))]
		o.sort(key=lambda i:nb[p2S[cur][i][0]])
		#if poss and attribold(cur, 0, res, set(), o):
		if poss and attrib(cur, res):
			done[cur] = True
			last = cur
			lastcont = (res[-1]+1)%C
			done_projects += [cur]
			p2c += [res]
			learning(p2S[cur], res, c2S, bestS)
	cur = (cur+1)%P
	if last == cur:
		break

print("", file=sys.stderr)
print_output(projects, contributors, done_projects, p2c)