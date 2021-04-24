from heapq import *

def parse(filename):
	file = open(filename, "r")
	
	line = file.readline()
	temp = line.split(" ")
	L = int(temp[0])
	G = int(temp[1])
	S = int(temp[2])
	B = int(temp[3])
	F = int(temp[4])
	N = int(temp[5])
	
	#services
	services = {}
	for _ in range(S):
		line = file.readline()
		temp = line.split(" ")
		
		name = temp[0]
		binaries = int(temp[1])
		services[name] = binaries
		
	#features
	features = {}
	for _ in range(F):
		line = file.readline()
		temp = line.split(" ")
		
		name = temp[0]
		nb_services = int(temp[1])
		difficulty = int(temp[2])
		nb_users = int(temp[3])
		
		line = file.readline()
		temp = line.split(" ")
		
		s = [x.strip() for x in temp]
		features[name] = (nb_services, difficulty, nb_users, s)
		
	return L, G, S, B, F, N, services, features

def parse_solution(filename):
	file = open(filename, "r")
	
	line = file.readline()
	E = int(line)
	
	engineers = []
	for _ in range(E):
		line = file.readline()
		T = int(line)
		tasks = []
		for _ in range(T):
			line = file.readline()
			temp = line.split(" ")
			type = temp[0]
			if type == "impl":
				tasks.append((type, temp[1], int(temp[2])))
			elif type == "move":
				tasks.append((type, temp[1], int(temp[2])))
			elif type == "new":
				tasks.append((type, None, None))
			elif type == "move":
				tasks.append((type, int(temp[1]), None))
		engineers.append(tasks)
				
				
	return E, engineers

filename = "inputs/b.txt"
L, G, S, B, F, N, services, features = parse(filename)

filename = "outputs/b.txt"
E, engineers = parse_solution(filename)


events = []
for g in range(E):
	heappush(events, (0, g, None, None))

btog = [0]*B
btos = [[] for _ in range(B)]
for name, b in services.items():
	btos[b].append(name)
	
score = 0
while events:
	t, g, rb, f = heappop(events)
	if rb is not None:
		btog[rb] -= 1
		
	if f is not None:
		nb_services, difficulty, nb_users, s = features[f]
		for name, b in services.items():
			if b == rb and name in s:
				s.remove(name)
				nb_services -= 1
		features[f] = (nb_services, difficulty, nb_users, s)
		
		#test if the feature is complete
		if nb_services == 0:
			score += nb_users * max(0, L - t)
	
	if not engineers[g]:
		continue
	type, x, y = engineers[g].pop(0)
	if type == "impl":
		f = x
		b = y
		nt = t + features[f][1] + len(btos[b]) + btog[b]
		heappush(events, (nt, g, b, f))
		btog[b] += 1
	elif type == "move":
		s = x
		b1 = services[s]
		b2 = y
		btos[b1].remove(s)
		btos[b2].append(s)
	elif type == "new":
		btog.append(0)
	elif type == "wait":
		nt = t + x
		heappush(events, (nt, g, None, None))
	
print(score)	

# for score, f in SF:
# 	bins = set()
# 	for s in ftos[f]:
# 		b = stob[s]
# 		if b not in bins:
# 			bins |= {b}
# 			t, g, rb = heappop(events)
# 			if rb is not None:
# 				btog[rb] -= 1
# 			nt = t + D[f] + len(btos[b]) + btog[b]
# 			heappush(events, (nt, g, b))
# 			btog[b] += 1
# 			res[g] += ["impl {} {}".format(itof[f], b)]
# 
# res = [r for r in res if r!=[]]
# print(len(res))
# for r in res:
# 	print(len(r))
# 	print("\n".join(r))