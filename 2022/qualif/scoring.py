def verif(contributors, c2S, projects, p2D, p2W, p2B, p2S, p_order, p2C_order):
	for p, C in zip(p_order, p2C_order):
		for i in range(len(C)):
			s, l = p2S[p][i]
			if c2S[C[i]].get(s, 0) < l-1:
				return False
			if c2S[C[i]].get(s, 0) < l:
				exist = False
				for j in range(len(C)):
					if c2S[C[j]].get(s, 0) >= l:
						exist = True
				if not exist:
					return False
		for i in range(len(C)):
			s, l = p2S[p][i]
			if c2S[C[i]].get(s, 0) <= l:
				c2S[C[i]][s] = c2S[C[i]].get(s, 0) + 1
	return True


def score(contributors, c2S, projects, p2D, p2W, p2B, p2S, p_order, p2C_order):
	free_at = [0]*len(contributors)
	for p, C in zip(p_order, p2C_order):
		first = -1
		last_free = -1
		for i in range(len(C)):
			return 0


