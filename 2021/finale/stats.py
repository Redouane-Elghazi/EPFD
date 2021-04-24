import matplotlib.pyplot as pl

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

def stats(L, G, S, B, F, N, services, features):
	print(filename)
	print("\tnb days", L)
	print("\tnb engineers", G)
	print("\tnb services", S)
	print("\tnb initial binaries", B)
	print("\tnb features", F)
	print("\tduration to create bin", N)
	
def features_per_services(NAME, L, G, S, B, F, N, services, features):
	data = {name : 0 for name, _ in services.items()}
	
	for nb_services, difficulty, nb_users, s in features.values():
		for name in s:
			data[name] += 1
			
	data = list(data.values())
	
	#plot
	nb_bins = 20
	fig, ax = pl.subplots(1, 1)
	fig.suptitle(f"{NAME} ({F} features and {S} services)")

	# We can set the number of bins with the `bins` kwarg
	ax.set_title("Features per services")
	ax.hist(data, bins=nb_bins, log=True)

	pl.savefig(NAME + "_fts_per_ser.png")
	
def features_per_binaries(NAME, L, G, S, B, F, N, services, features):
	data = [0] * B
	
	for nb_services, difficulty, nb_users, s in features.values():
		for name in s:
			b = services[name]
			data[b] += 1
	
	#plot
	nb_bins = 20
	fig, ax = pl.subplots(1, 1)
	fig.suptitle(f"{NAME} ({F} features and {S} services and {B} binaries)")

	# We can set the number of bins with the `bins` kwarg
	ax.set_title("Features per binaries")
	ax.hist(data, bins=nb_bins, log=True)

	pl.savefig(NAME + "_fts_per_bin.png")
	
def services_per_features(NAME, L, G, S, B, F, N, services, features):
	data = [nb_services for name, (nb_services, difficulty, nb_users, s) in features.items()]
	
	#plot
	nb_bins = 20
	fig, ax = pl.subplots(1, 1)
	fig.suptitle(f"{NAME} ({F} features and {S} services and {B} binaries)")

	# We can set the number of bins with the `bins` kwarg
	ax.set_title("Services per features")
	ax.hist(data, bins=nb_bins, log=True)

	pl.savefig(NAME + "_ser_per_ft.png")
	
def binaries_per_features(NAME, L, G, S, B, F, N, services, features):
	data = [len(set([services[name] for name in s])) for _, (nb_services, difficulty, nb_users, s) in features.items()]
	
	#plot
	nb_bins = 20
	fig, ax = pl.subplots(1, 1)
	fig.suptitle(f"{NAME} ({F} features and {S} services and {B} binaries)")

	# We can set the number of bins with the `bins` kwarg
	ax.set_title("Binaries per features")
	ax.hist(data, bins=nb_bins, log=True)

	pl.savefig(NAME + "_bin_per_ft.png")
	
def max_score(L, G, S, B, F, N, services, features):
	#max si on fait tout les features
	score = 0
	for name, (nb_services, difficulty, nb_users, s) in features.items():
		score += nb_users * max(0, L - difficulty)
		
	print("max score", score)
	
	
for k in "abcdef":
	filename = f"inputs/{k}.txt"
	L, G, S, B, F, N, services, features = parse(filename)
	stats(L, G, S, B, F, N, services, features)
	max_score(L, G, S, B, F, N, services, features)
	print("\n")