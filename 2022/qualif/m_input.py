def read_input():
	C, P = [int(x) for x in input().split()]
	contributors, c2S = [], []
	for c in range(C):
		name, N = input().split()
		contributors += [name]
		N = int(N)
		c2S += [dict()]
		for i in range(N):
			s, l = input().split()
			c2S[-1][s] = int(l)
	
	projects, p2D, p2W, p2B, p2S = [], [], [], [], []
	for p in range(P):
		name, D, W, B, r = input().split()
		projects += [name]
		p2D += [int(D)]
		p2W += [int(W)]
		p2B += [int(B)]
		r = int(r)
		p2S += [[]]
		for i in range(r):
			s, l = input().split()
			p2S[-1] += [(s, int(l))]
		
	return (contributors, c2S, projects, p2D, p2W, p2B, p2S)