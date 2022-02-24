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


def read_input(filename):
	file = open(filename, "r")
	C, P = [int(x) for x in file.readline().strip().split()]
	contributors, c2S = [], []
	for c in range(C):
		name, N = file.readline().strip().split()
		contributors += [name]
		N = int(N)
		c2S += [dict()]
		for i in range(N):
			s, l = file.readline().strip().split()
			c2S[-1][s] = int(l)

	projects, p2D, p2W, p2B, p2S = [], [], [], [], []
	for p in range(P):
		name, D, W, B, r = file.readline().strip().split()
		projects += [name]
		p2D += [int(D)]
		p2W += [int(W)]
		p2B += [int(B)]
		r = int(r)
		p2S += [[]]
		for i in range(r):
			s, l = file.readline().strip().split()
			p2S[-1] += [(s, int(l))]

	return (contributors, c2S, projects, p2D, p2W, p2B, p2S)


def read_output():
	P = int(input())
	name2i = dict()
	projects = []
	contributors = []
	projects_order = []
	p2C_order = []
	for i in range(P):
		projects_order += [len(projects)]
		projects += [input()]
		p2C_order += [[]]
		names = input().split()
		for n in names:
			if n not in name2i:
				name2i[n] = len(contributors)
				contributors += [n]
			p2C_order[-1] += [name2i[n]]
	return (projects, contributors, projects_order, p2C_order)


def read_output(filename):
	file = open(filename, "r")
	P = int(file.readline().strip())
	name2i = dict()
	projects = []
	contributors = []
	projects_order = []
	p2C_order = []
	for i in range(P):
		projects_order += [len(projects)]
		projects += [file.readline().strip()]
		p2C_order += [[]]
		names = file.readline().strip().split()
		for n in names:
			if n not in name2i:
				name2i[n] = len(contributors)
				contributors += [n]
			p2C_order[-1] += [name2i[n]]
	return (projects, contributors, projects_order, p2C_order)


def read_output(projects, contributors):
	p2i = dict()
	c2i = dict()
	for i in range(len(projects)):
		p2i[projects[i]] = i
	for i in range(len(contributors)):
		c2i[contributors[i]] = i

	P = int(input())
	projects_order = []
	p2C_order = []
	for i in range(P):
		projects_order += [p2i[input()]]
		p2C_order += [[]]
		names = input().split()
		for n in names:
			p2C_order[-1] += [c2i[n]]
	return projects_order, p2C_order


def read_output(filename, projects, contributors):
	file = open(filename, "r")
	p2i = dict()
	c2i = dict()
	for i in range(len(projects)):
		p2i[projects[i]] = i
	for i in range(len(contributors)):
		c2i[contributors[i]] = i

	P = int(file.readline().strip())
	projects_order = []
	p2C_order = []
	for i in range(P):
		projects_order += [p2i[file.readline().strip()]]
		p2C_order += [[]]
		names = file.readline().strip().split()
		for n in names:
			p2C_order[-1] += [c2i[n]]
	return projects_order, p2C_order



def print_output(projects, contributors, projects_order, p2C_order):
	print(len(projects_order))
	for p, C in zip(projects_order, p2C_order):
		print(projects[p])
		print(" ".join(contributors[c] for c in C))
