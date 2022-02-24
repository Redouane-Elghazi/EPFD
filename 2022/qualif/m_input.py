def read_input():
	C, P = [int(x) for x in input().split()]
	constributors, c2S = [], []
	for c in range(C):
		contributors += [input()]
		N = int(input())
		c2S += [dict()]
		for i in range(N):
			s, l = input().split()
			c2S[-1][s] = int(l)
	
	projects, p2D, p2W, p2B, p2S = [], [], [], [], []
	for p in range(P):
		projects += [input()]
		p2D += [int(input())]
		p2W += [int(input())]
		p2B += [int(input())]
		r = int(input())
		p2S += [dict()]
		for i in range(r):
			s, l = input().split()
			p2S[-1][s] = int(l)
		
	return (contributors, c2S, projects, p2D, p2W, p2B, p2S)