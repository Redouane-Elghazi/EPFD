from IO_hashcode import read_input, print_output
from tools import find_contributors_yield, learning
import scoring
from random import shuffle

def attrib(p, i, res, used):
	if i == len(p2S[p]):
		return True
	for cont in find_contributors_yield(p2S[p], c2S, i, start=lastcont):
		if cont not in used:
			res += [cont]
			used|={cont}
			if attrib(p, i+1, res, used):
				return True
			res.pop(-1)
			used-={cont}
	return False

contributors, c2S, projects, p2D, p2W, p2B, p2S = read_input()

C = len(contributors)
P = len(projects)

last = -1
cur = 0
done = [False] * P
done_projects = []
p2c = []
lastcont = 0
while True:
	if not(done[cur]):
		res = []
		if attrib(cur, 0, res, set()):
			done[cur] = True
			last = cur
			lastcont = (res[-1]+1)%C
			done_projects += [cur]
			p2c += [res]
			#learning(p2S, res, c2S)
	cur = (cur+1)%P
	if last == cur:
		break

print_output(projects, contributors, done_projects, p2c)